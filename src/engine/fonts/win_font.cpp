// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifdef VE_WINDOWS

#include "fonts/win_font.h"
#include "fonts/font_cache.h"
#include "windows/windows_system.h"
#include "engines/engine.h"

namespace ve {

/**
    Font constructor. Create Font objects only through call
    to WindowSystem::createFont().
    @param owner - WindowSystem which creates this font object.
    @param engine - engine which will be used for font rendering.
@param hFont - handle of this font
*/
WinFont::WinFont(WindowSystem *owner, Engine *engine, HFONT hFont) :Font(owner, engine) {
  this->hFont = hFont;

  HWND handle = GetActiveWindow();
  SelectObject(GetDC(handle), hFont);
  LOG_IF(GetTextMetrics(GetDC(handle), &tm) == 0, L"GetTextMetrics() failed");
}

WinFont::~WinFont() {
  for (uint i = 0; i < callLists.size(); i++) {
    glDeleteLists(callLists[i], 1);
  }
}

/**
  Returns handle of this font.
  @return Handle of this font.
*/
HFONT WinFont::getHandle() {
  return hFont;
}

Outcome WinFont::drawString(float x, float y, float z, std::wstring str) {
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

Outcome WinFont::drawNonCachedSymbol(float x, float y, float z, wchar_t symbol) {
  GLuint callList = glGenLists(1);
  GL_CHECK(ERROR);

  HWND handle = GetActiveWindow();
  SelectObject(GetDC(handle), hFont);
  wglUseFontBitmaps(GetDC(handle), symbol, 1, callList);

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

uint WinFont::getSymbolWidth(wchar_t symbol) {
  HWND handle = GetActiveWindow();
  int width = 0;

  SelectObject(GetDC(handle), hFont);
  ERROR_IF(GetCharWidth32(GetDC(handle), symbol, symbol, &width) == 0, L"GetCharWidth32 failed", 0);

  return width;
}

uint WinFont::getHeight() {
  return tm.tmHeight;
}

uint WinFont::getWidth() {
  return tm.tmMaxCharWidth;
}

uint WinFont::getLBearing() {
  return tm.tmInternalLeading;
}

uint WinFont::getAscend() {
  return tm.tmAscent;
}

}


#endif // VE_WINDOWS