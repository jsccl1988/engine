// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#if defined(VE_WINDOWS) || defined(DOXYGEN)

#ifndef __VE_WIN_FONT_H__
#define __VE_WIN_FONT_H__

#include "fonts/font.h"

namespace ve {

class Engine;
class WindowSystem;
class FontCache;

/**
    Implementation for abstract class Font for Windows OS.
    <b>Note:</b>Never create it by yourself. Use
    WindowSystem::createFont() function to create correct
    instance of font.
*/
class WinFont : public Font {
private:
  /* Handle of this font */
  HFONT hFont;

  /* List of allocated call lists */
  std::vector<GLuint> callLists;

  /* Font data structure */
  TEXTMETRIC tm;

public:
  /**
      Font constructor. Create Font objects only through call
      to WindowSystem::createFont().
      @param owner - WindowSystem which creates this font object.
      @param engine - engine which will be used for font rendering.
@param hFont - handle of this font
  */
  WinFont(WindowSystem *owner, Engine *engine, HFONT hFont);

  /**
    Returns handle of this font.
    @return Handle of this font.
  */
  HFONT getHandle();

  /**
      Font destructor. Calls WindowSystem::freeFont() function
      to free allocated resource. Dispose FontCache object.
  */
  virtual ~WinFont();

  /**
      Renders string like series of quads (each letter corresponds
      to a quad). It means that all tranformations which are
      applicable for quads rendering may be applied for string
      rendering. Rotation, scaling, shaders, etc..
      Only this function uses FontCache to render symbols.
      String position is specified by coordinates of left-upper corner
      of the first letter's quad. String is rendered in XOY plane
      with a constant z-coord.
      @param x - X coordinate of left-upper corner.
      @param y - Y coordinate of left-upper corner.
      @param z - Z coordinate of left-upper corner.
      @param str - Unicode string to render.
      @return OK if rendering succeeded.
      @return non-OK if engine's error occurred.
  */
  virtual Outcome drawString(float x, float y, float z, std::wstring str);

  /**
      Renders symbol using OpenGL call list prepared by WindowSystem.
      No tranformations may be applied.
      This function is used by FontCache to fill cache-texture.
      Do not use it for string rendering.
      Symbol position is specified by coordinates of left-upper corner
      Sumbol is rendered in XOY plane with a constant z-coord.
      @param x - X coordinate of left-upper corner.
      @param y - Y coordinate of left-upper corner.
      @param z - Z coordinate of left-upper corner.
      @param symbol - Unicode symbol to render.
      @return OK if rendering succeeded.
      @return non-OK if engine's error occurred.
  */
  virtual Outcome drawNonCachedSymbol(float x, float y, float z, wchar_t symbol);

  /**
      Returns symbol width in pixels.
      @return Symbol width in pixels.
  */
  virtual uint getSymbolWidth(wchar_t symbol);

  /**
      Returns height of the highest symbol.
      @return Height of the highest symbol.
  */
  virtual uint getHeight();

  /**
      Returns width of the widest symbol.
      @return Width of the widest symbol.
  */
  virtual uint getWidth();

  /**
      Returns maximum value for 'LBearing' font property.
      @return Maximum value for 'LBearing' font property.
      @see 'man xfontstruct' for more info.
  */
  virtual uint getLBearing();

  /**
      Returns maximum value for 'Ascend' font property.
      @return Maximum value for 'Ascend' font property.
      @see 'man xfontstruct' for more info.
  */
  virtual uint getAscend();
};

}

#endif // __VE_WIN_FONT_H

#endif // VE_WINDOWS
