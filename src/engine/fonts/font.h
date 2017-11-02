// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_FONT_H__
#define __VE_FONT_H__

#include "engine/common.h"

namespace ve {

class Engine;
class WindowSystem;
class FontCache;

/**
    Font class represents font registered in the window system.
    It can be used to obtain font characteristics, like a width
    of specific symbol or width of a string. It is commonly used
    to render text on a screen.

    Font objects contain FontCache object inside. Formally, it is
    a RGBA8 texture. It contains symbols which are used very more then
    other to speed up text rendering. There is no need to create, prepare
    or fill FontCache. All the stuff will be done automatically.

    Font class contains two functions to render text.
    <ul>
    <li>drawString() should be used everywhere and everytime, because it
    uses FontCache and it boosts render in several times.
    </li>
    <li>
    drawNonCachedSymbol() used only by cache to FontCache to render
    symbols using OpenGL call lists prepared by window system.
    <b>Note:</b>This function is very slow.
    </li>
    </ul>

    <b>Note:</b> Create instances of Font classes only through
    WindowSystem::createFont() function.
*/
class Font {
protected:
  /** Window system that produced this font */
  WindowSystem *windowSystem;

  /** Engine that used to render symbols */
  Engine *engine;

  /**
      FontCache object. Used to speed up drawString()
      function.
  */
  FontCache *cache;

public:
  /**
      Font constructor. Create Font objects only through call
      to WindowSystem::createFont().
      @param owner - WindowSystem which creates this font object.
      @param engine - engine which will be used for font rendering.
  */
  Font(WindowSystem *owner, Engine *engine);

  /**
      Font destructor. Calls WindowSystem::freeFont() function
      to free allocated resource. Dispose FontCache object.
  */
  virtual ~Font();

  /**
      FontCache initialization function.
      @param cacheSize - size of FontCache. Specifies width
      and height for texture which will be used inside FontCache
      object to store symbols.
      @return OK if initialization succeeded and FontCache object
      was created without exceptions.
      @return non-OK in case of problem.
  */
  virtual Outcome initialize(uint cacheSize);

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
  virtual Outcome drawString(float x, float y, float z, std::wstring str) = 0;

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
  virtual Outcome drawNonCachedSymbol(float x, float y, float z, wchar_t symbol) = 0;

  /**
      Returns length of the string written using this font.
      @return String length (in pixels).
  */
  virtual uint getTextWidth(std::string s);

  /**
      Returns length of the string written using this font.
      @return String length (in pixels).
  */
  virtual uint getTextWidth(std::wstring ws);

  /**
      Returns symbol width in pixels.
      @return Symbol width in pixels.
  */
  virtual uint getSymbolWidth(wchar_t symbol) = 0;

  /**
      Returns height of the highest symbol.
      @return Height of the highest symbol.
  */
  virtual uint getHeight() = 0;

  /**
      Returns width of the widest symbol.
      @return Width of the widest symbol.
  */
  virtual uint getWidth() = 0;

  /**
      Returns maximum value for 'LBearing' font property.
      @return Maximum value for 'LBearing' font property.
      @see 'man xfontstruct' for more info.
  */
  virtual uint getLBearing() = 0;

  /**
      Returns maximum value for 'Ascend' font property.
      @return Maximum value for 'Ascend' font property.
      @see 'man xfontstruct' for more info.
  */
  virtual uint getAscend() = 0;

  /**
      Returns FontCache object which is used by this Font.
      @return Pointer to FontCache object.
  */
  virtual FontCache* getCache();
};

}

#endif // __VE_FONT_H
