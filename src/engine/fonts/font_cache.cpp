// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include <memory.h>

#include "fonts/font_cache.h"
#include "engines/engine.h"
#include "tools/string_tool.h"
#include "states/viewport_state.h"

namespace ve {

FontCache::FontCache() {
  engine = NULL;
  fb = NULL;
  cache = NULL;
  cacheSize = 0;
  curX = 0;
  curY = 0;
  camera = NULL;

  buffersState.vertices = BufferDesc(3, FLOAT, 0, 0, false);
  buffersState.texCoords = BufferDesc(2, FLOAT, 0, 0, false);
  alphaTestState = AlphaTestState(true, GREATER, 0);
}

FontCache::~FontCache() {
  if (fb != NULL) {
    delete fb;
  }

  if (cache != NULL) {
    delete cache;
  }

  for (map<wchar_t, SymbolInfo*>::iterator it = data.begin(); it != data.end(); ++it) {
    delete it->second;
  }
}

Outcome FontCache::initialize(Engine *engine, ve::Font *font, uint cacheSize) {
  CHECK_POINTER(engine);
  CHECK_POINTER(font);

  this->engine = engine;
  this->cacheSize = cacheSize;
  this->font = font;
  curX = font->getLBearing();
  curY = font->getAscend();

  /* Prepare camera */
  camera = new OrthoCamera(engine, ViewportState(0, 0, cacheSize, cacheSize), false, true);

  /* Prepare off-screen frame buffer */
  fb = engine->createFrameBuffer();
  CHECK_POINTER(fb);

  /* Create initialy black texture for symbols caching */
  uint *data = new uint[cacheSize * cacheSize];
  CHECK_ALLOC(data);
  memset(data, 0, cacheSize * cacheSize * sizeof(uint));
  cache = engine->createTexture(RGBA8, cacheSize, cacheSize, RGBA8, data);
  delete[] data;
  CHECK_POINTER(cache);

  /* Attach texture to frame buffer and check status to be sure that */
  /* everything is ok.                                               */
  ASSERT(fb->bind());
  ASSERT(fb->attachTexture2D(cache, COLOR_ATTACHMENT0));
  FrameBufferStatus status = engine->checkFrameBufferStatus();
  ASSERT(fb->unbind());
  ERROR_IF(status != FRAMEBUFFER_COMPLETE
    , L"Frame buffer status: " + StringTool::intToStr((int)status)
    , ERROR);
  return OK;
}

bool FontCache::needUpdate(std::wstring str) {
  int len = str.length();

  for (int i = 0; i < len; i++) {
    if (data.find(str[i]) == data.end()) {
      return true;
    }
  }

  return false;
}

Outcome FontCache::beginCaching() {
  GPUStateManager *stateManager = engine->getStateManager();
  /* Save previous viewport state */
  oldViewport = stateManager->getViewportState();

  ASSERT(fb->bind());

  /* Store all matrices */
  ASSERT(engine->enableMatrix(PROJECTION));
  ASSERT(engine->beginTransform());
  ASSERT(engine->enableMatrix(MODELVIEW));
  ASSERT(engine->beginTransform());

  /* Reset new coordinate system for cache texture */
  ASSERT(camera->apply());
  return OK;
}

Outcome FontCache::processSymbol(wchar_t symbol) {
  GPUStateManager *stateManager = engine->getStateManager();

  /* Check if there is need to cache this symbol */
  if (data.find(symbol) == data.end()) {
    int fontHeight = font->getHeight();
    int fontWidth = font->getWidth();
    int fontLBearing = font->getLBearing();
    int fontDescend = fontHeight - font->getAscend();
    SymbolInfo *si = NULL;

    stateManager->pushStates(COLOR_STATE);

    /* Check if cache already run out */
    if (curX + fontWidth >= (uint)cacheSize
      && curY + fontHeight + fontDescend >= (uint)cacheSize) {
      /* Cache is over. Try to find useless symbol. */
      map<wchar_t, uint>::iterator useless = usage.begin();
      ERROR_IF(useless == usage.end(), L"Unpredictable situation", ERROR);
      wchar_t symbolToDelete = useless->first;

      /* Retrieve position in a texture */
      si = data[symbolToDelete];

      /* Remove all info about this symbol */
      usage.erase(symbolToDelete);
      data.erase(symbolToDelete);

      /* Erase old symbol and draw new symbol on cache texture */
      ASSERT(stateManager->setColorState(ColorState(BLACK)));
      ASSERT(font->drawNonCachedSymbol(si->curX, si->curY, 0, symbolToDelete));
      ASSERT(stateManager->setColorState(ColorState(WHITE)));
      ASSERT(font->drawNonCachedSymbol(si->curX, si->curY, 0, symbol));

      si->symbolWidth = font->getSymbolWidth(symbol);
      data[symbol] = si;
    } else {
      /* Allocate memory for new symbol data */
      si = new SymbolInfo();

      /* Check if it is not enough space in the current row */
      /* If not, set current pointer to the next row.       */

      if (curX + fontWidth >= (uint)cacheSize) {
        curX = font->getLBearing();
        curY = curY + fontHeight;
      }

      si->u = (float)(curX - fontLBearing) / cacheSize;
      si->v = 1.0f - (float)(curY + fontDescend) / cacheSize;
      si->curX = curX;
      si->curY = curY;
      si->symbolWidth = font->getSymbolWidth(symbol);

      /* Draw this symbol on cache texture */
      ASSERT(stateManager->setColorState(ColorState(WHITE)));
      ASSERT(font->drawNonCachedSymbol(curX, curY, 0, symbol));

      /* Shift X position */
      curX = curX + fontWidth;
    }

    data[symbol] = si;
    usage[symbol] = 0;

    stateManager->popStates(COLOR_STATE);
  }

  return OK;
}

Outcome FontCache::processString(std::wstring str) {
  /* Check which symbols from the string we already have */
  int len = str.length();
  int i = 0;

  for (i = 0; i < len; i++) {
    CHECK_RESULT(processSymbol(str[i]), L"Processing of symbol " + StringTool::intToStr(str[i]) + L" failed");
  }

  return OK;
}

Outcome FontCache::endCaching() {
  GPUStateManager *stateManager = engine->getStateManager();
  ASSERT(fb->unbind());

  /* Restore viewport */
  ASSERT(stateManager->setViewportState(oldViewport));

  /* Restore all matrices */
  ASSERT(engine->enableMatrix(PROJECTION));
  ASSERT(engine->endTransform());
  ASSERT(engine->enableMatrix(MODELVIEW));
  ASSERT(engine->endTransform());
  return OK;
}

Outcome FontCache::drawString(std::wstring str) {
  GPUStateManager *stateManager = engine->getStateManager();
  int len = str.length();

  if (len == 0) {
    return OK;
  }

  /*                                                               */
  /* We will draw string as a set of 'quad' primitives.            */
  /* In this case, for <len> quads there are (4 * len) verices     */
  /* Each of them contains three coordinates. Thus, we get that    */
  /* (4 * len * 3) float values are needed.                        */
  /* The same computation for texture coordinates:                 */
  /* (4 * len * 2) float values, because of two-components         */
  /* coords.                                                       */
  /*                                                               */

  vertices.resize(12 * len);
  texCoords.resize(8 * len);

  /*                                                               */
  /* Fill coordinates in the following order                       */
  /*  (1)--(3)(5)--(7)(9)-- ...                                    */
  /*   |    |  |    |  |                                           */
  /*   |    |  |    |  |                                           */
  /*   |    |  |    |  |                                           */
  /*  (0)--(2)(4)--(6)(8)-- ...                                    */
  /*                                                               */

  uint xOffset = 0;
  uint fontHeight = font->getHeight();
  uint fontWidth = font->getWidth();

  /* Constant texture size for all symbols */
  float du = (float)(fontWidth) / cacheSize;
  float dv = (float)(fontHeight) / cacheSize;

  /* Iteration through quads */
  for (int i = 0; i < len; i++) {
    usage[str[i]]++;
    SymbolInfo *symInfo = data[str[i]];
    float u = symInfo->u;
    float v = symInfo->v;
    uint symbolWidth = symInfo->symbolWidth;

    /* Fill vertex coordinates for vertices 0, 4, 8, ...  */
    vertices[12 * i + 0] = xOffset;
    vertices[12 * i + 1] = fontHeight;
    vertices[12 * i + 2] = 0;

    /* Fill vertex coordinates for vertices 1, 5, 9, ...  */
    vertices[12 * i + 3] = xOffset;
    vertices[12 * i + 4] = 0;
    vertices[12 * i + 5] = 0;

    /* Fill vertex coordinates for vertices 3, 7, 11, ... */
    vertices[12 * i + 6] = xOffset + fontWidth;
    vertices[12 * i + 7] = 0;
    vertices[12 * i + 8] = 0;

    /* Fill vertex coordinates for vertices 2, 6, 10, ... */
    vertices[12 * i + 9] = xOffset + fontWidth;
    vertices[12 * i + 10] = fontHeight;
    vertices[12 * i + 11] = 0;

    /* Fill texture coordiantes for vertices 0, 4, 8, ... */
    texCoords[8 * i + 0] = u;
    texCoords[8 * i + 1] = v;

    /* Fill texture coordiantes for vertices 1, 5, 9, ... */
    texCoords[8 * i + 2] = u;
    texCoords[8 * i + 3] = v + dv;

    /* Fill texture coordiantes for vertices 2, 6, 10, ... */
    texCoords[8 * i + 4] = u + du;
    texCoords[8 * i + 5] = v + dv;

    /* Fill texture coordiantes for vertices 3, 7, 11, ... */
    texCoords[8 * i + 6] = u + du;
    texCoords[8 * i + 7] = v;

    xOffset = xOffset + symbolWidth;
  }

  stateManager->pushStates(ALPHA_TEST_STATE | TEXTURES_STATE | BUFFERS_STATE);
  TexturesState texturesState(cache, TextureEnvMode(MODULATE));

  buffersState.vertices.data = &vertices[0];
  buffersState.texCoords.data = &texCoords[0];

  ASSERT(stateManager->setBuffersState(buffersState));
  ASSERT(stateManager->setTexturesState(texturesState));
  ASSERT(stateManager->setAlphaTestState(alphaTestState));
  ASSERT(engine->drawPrimitives(QUADS, 0, len * 4));

  stateManager->popStates(ALPHA_TEST_STATE | TEXTURES_STATE | BUFFERS_STATE);

  return OK;
}

Texture* FontCache::getTexture() {
  return cache;
}

}
