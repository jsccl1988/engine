// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_FONT_CACHE_H__
#define __VE_FONT_CACHE_H__

#include <string>
#include <map>

#include "engine/common.h"
#include "engine/buffers/frame_buffer.h"
#include "engine/fonts/font.h"
#include "engine/cameras/ortho_camera.h"
#include "engine/states/buffer_state.h"
#include "engine/states/alpha_test_state.h"

namespace ve {

class Engine;
struct ViewportState;

/**
    Structure which is used inside FontCache objects to identify
    symbols position in a cache-texture and texture coorinates.

    It is easy to note, that (u, v) can be easyly computed from
    (curX, curY) and vice versa. But I store both pairs to
    avoid overhead in computations during string rendering.
*/
struct SymbolInfo {
  /** U-coordiant of the symbol's left-bottom corner */
  float u;

  /** V-coordiant of the symbol's left-bottom corner */
  float v;

  /** X-position of the symbol's (lbearing, descend) point */
  float curX;

  /** Y-position of the symbol's (lbearing, descend) point */
  float curY;

  /** Symbol width */
  uint symbolWidth;

  /**
      Simple constructor.
  */
  SymbolInfo() {
    u = 0;
    v = 0;
    curX = 0;
    curY = 0;
    symbolWidth = 0;
  }

  /**
      Constructor with values to set as initial values.
  */
  SymbolInfo(float u, float v, float curX, float curY, uint symbolWidth) {
    this->u = u;
    this->v = v;
    this->curX = curX;
    this->curY = curY;
    this->symbolWidth = symbolWidth;
  }
};

/** Default cache size */
static const int CACHE_SIZE = 512;

/**
    FontCache is used to speed up text rendering by
    using a texture as a cache for often-used symbols.
    It is created for all Font classes to boost text rendering
    functions. It also allows to render text like a series of
    quads which transformations & shaders applied to them.
*/
class FontCache {
private:
  /** Engine which is used for symbol's rendering */
  Engine *engine;

  /** Owner of this cache */
  ve::Font *font;

  /**
      Frame buffer object which is used to render
      to texture.
  */
  FrameBuffer *fb;

  /**
      Camera object which is used to set up coordinate
      system before rendering to texture.
  */
  OrthoCamera *camera;

  /**
      Texture which is used as cache.
  */
  Texture *cache;

  /**
      Cache size.
  */
  int cacheSize;

  /**
      Map which calculates symbol's usage.
      usage['a'] defines how many times letter 'a' was
      rendered after it was placed into cache.
  */
  map<wchar_t, uint> usage;

  /**
      Map which contains positions for symbols used in a cache.
      data['a'] defines SymbolInfo structure associated with this letter.
      If no entry with 'a' key exists then there is no 'a' letter in the cache.
      Note: data['a'] == NULL and 'not exists' different suggestions.
  */
  map<wchar_t, SymbolInfo*> data;

  /**
      Current position in a cache. It is used when cache is not full.
  */
  uint curX;
  uint curY;

  /**
      Viewport which was set before frame buffer change.
      We need to store this before caching to restore it
      after caching.
  */
  ViewportState oldViewport;

  /**
    Buffers state for rendering.
  */
  BuffersState buffersState;

  /**
    Alpha test state to render strings.
  */
  AlphaTestState alphaTestState;

  /**
    Buffer of vertices to render.
  */
  std::vector<float> vertices;

  /**
    Buffer of texture coordinates.
  */
  std::vector<float> texCoords;

public:
  /**
      FontCache constructor. Nothing special ;)
  */
  FontCache();

  /**
      Font cache destructor.
  */
  ~FontCache();

  /**
      Initialize %FontCache objects. Creates FrameBuffer and RGBA8 texture.
      Texture size defined as cacheSize parameter.
      @param engine - Engine which will be used to create graphic objects.
      @param font - font which creates this cache.
      @param cacheSize - Size of a texture which will contain symbols.
      @return OK if all objects were created successfully.
      @return non-OK if some of the engine functions fails.
  */
  Outcome initialize(Engine *engine, ve::Font *font, uint cacheSize = CACHE_SIZE);

  /**
      Checks if there is a need to update cache before rendering.
      @param str - String to check if there is a need to update cache for it.
      @return true if update is needed.
      @return false if all symbols from specified string already in a cache.
  */
  bool needUpdate(std::wstring str);

  /**
      Prepare pipeline state for text rendering. It sets up
      frame buffer and viewport.
      @return OK if all changes succeeded.
      @return non-OK if engine error occurred.
      @bug I suppose that there is a need to store more states, but I do not
      know how to make it in a good way. glPushSomething()?
  */
  Outcome beginCaching();

  /**
      Cache specified symbol if it is not already in a cache.
      <b>Note:</b> May be called strictly only between beginCaching() and
      endCaching() functions.
      @param symbol - symbol to put in a cache.
      @return OK if caching succeeded.
      @return non-OK if engine error occurred.
  */
  Outcome processSymbol(wchar_t symbol);

  /**
      Cache all symbols from specified string.
      May be used to warm up cache.
      <b>Note:</b> May be called strictly only between beginCaching() and
      endCaching() functions.
      @param str - string to cache symbols from.
      @return OK if caching succeeded for all symbols from the string.
      @return non-OK if engine error occurred at least for one symbol.
  */
  Outcome processString(std::wstring str);

  /**
      Restore pipeline state which was before beginCaching() call.
      @return OK if function succeeded.
      @return non-OK if function fails.
  */
  Outcome endCaching();

  /**
      Draws string as quads at (0, 0, 0) point.
      Any transformation applicable.
      <b>Note:</b> String need to be cached before rendering.
      @param str - String to render.
      @return OK if rendering succeeded.
      @return non-OK is engine error occurred.
  */
  Outcome drawString(std::wstring str);

  /**
      Returns texture object which is used to cache symbols.
      @return Cache-texture.
  */
  Texture *getTexture();
};

}

#endif // __VE_FONT_CACHE_H__
