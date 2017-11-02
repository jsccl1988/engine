// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifdef VE_LINUX

#include "engine/fonts/x_font.h"
#include "engine/windows/xwindow_system.h"
#include "engine/engines/engine.h"

namespace ve {

XFont::XFont(XWindowSystem *windowSystem, Engine *engine, XFontStruct* fontInfo) :Font(windowSystem, engine) {
  info = fontInfo;
}

XFont::~XFont() {
  /// FIXME: Is there need to free <info> structure? I'm not sure.
  for (uint i = 0; i < callLists.size(); i++) {
    glDeleteLists(callLists[i], 1);
  }
}

Outcome XFont::drawString(float x, float y, float z, std::wstring str) {
  if (cache->needUpdate(str)) {
    cache->beginCaching();
    cache->processString(str);
    cache->endCaching();
  }

  ASSERT(engine->beginTransform());
  ASSERT(engine->translate(x, y, z));
  ASSERT(cache->drawString(str));
  ASSERT(engine->endTransform());

  return OK;
}

Outcome XFont::drawNonCachedSymbol(float x, float y, float z, wchar_t symbol) {
  GLuint callList = glGenLists(1);
  GL_CHECK(ERROR);

  GL_SAFE_CALL(glXUseXFont(info->fid, symbol, 1, callList), ERROR);

  callLists.push_back(callList);

  glColor4f(1.0, 1.0, 1.0, 1.0);
  GL_SAFE_CALL(glRasterPos3f(x, y, z), ERROR);
  glPushAttrib(GL_LIST_BASE);
  glListBase(callList);
  int t = 0;
  GL_SAFE_CALL(glCallLists(1, GL_INT, &t), ERROR);
  glPopAttrib();

  GL_SAFE_CALL(glDeleteLists(callList, 1), ERROR);
  return OK;
}

uint XFont::getSymbolWidth(wchar_t symbol) {
  return info->per_char[symbol].width;
}

XFontStruct* XFont::getInfo() {
  return info;
}

uint XFont::getHeight() {
  return info->max_bounds.ascent + info->max_bounds.descent;
}

uint XFont::getWidth() {
  return info->max_bounds.lbearing + info->max_bounds.rbearing;
}

uint XFont::getLBearing() {
  return info->max_bounds.lbearing;
}

uint XFont::getAscend() {
  return info->max_bounds.ascent;
}

}


#endif // VE_LINUX