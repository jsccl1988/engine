// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_FONT_DESCRIPTOR_H__
#define __VE_FONT_DESCRIPTOR_H__

#include <string>
#include "engine/common.h"

/** @file eeFontDescriptor.h */

namespace ve {

/* Predefined constant for several fonts families */
const std::wstring HELVETICA_FONT_FAMILY = L"Helvetica";
const std::wstring TIMES_FONT_FAMILY = L"Times";
const std::wstring TIMES_ROMAN_FONT_FAMILY = L"Times Roman";
const std::wstring COURIER_FONT_FAMILY = L"Courier";

enum FontSlant {
  SLANT_ROMAN = 0,
  SLANT_ITALIC,
  SLANT_OBLIQUE,
  SLANT_REVERSE_ITALIC,
  SLANT_REVERSE_OBLIQUE,
  SLANT_OTHER,
  SLANT_ANY
};

enum FontSetWidth {
  SETWIDTH_NORMAL = 0,
  SETWIDTH_CONDENSED,
  SETWIDTH_NARROW,
  SETWIDTH_DOUBLE_WIDE,
  SETWIDTH_ANY
};

enum FontSpacing {
  SPACING_PROPORTIONAL = 0,
  SPACING_MONOSPACED,
  SPACING_CHARCELL,
  SPACING_ANY
};

/**
    Class which describes font properites using
    X Logical Font Description Conventions.
    Holds only one string which represent all font properties at once.
    @see www.google.com
*/
class FontDescriptor {
private:
  /** String which specifies font */
  std::wstring format;
  uint size;
  bool bold;
  bool italic;
  bool strikeout;
  bool underlined;
  std::wstring fontFamily;

public:
  /**
      Simple constructor.
      Default format string value is: "-*-courier-bold-r-normal--12-*-*-*-*-*-*-*"
  */
  FontDescriptor();

  /**
      Constructor which generates font description string using
      standard font properties like family name, resolution, size, etc.
      @param familyNameField - "Helvetica", for example.
      @param slantField - Font slant.
      @param setWidthField - Font width.
      @param pixelSize - Font size.
      @param spacingField - Define if font is monospaced or not.
      @param resolutionX - dpi for X-axis (usually 75 or 100)
      @param resolutionY - dpi for Y-axis (usually the same as resolutionX)
      @see 'X Logical Font Description Conventions' documents for a lot of
      details.
  */
  FontDescriptor(std::wstring familyNameField, FontSlant slantField, FontSetWidth setWidthField,
    int pixelSize, FontSpacing spacingField, int resolutionX, int resolutionY);

  /**
      Returns format string which describes this font.
      @return Font description defined in X Logical Font Description Conventions.
  */
  std::wstring getFormatString();

  /**
      Sets format string. It should be correcly defined and
      convenient with X Logical Font Description Conventions.
      @param format - new font description string.
  */
  void setFormatString(std::wstring format);

  /**
    Returns size of the font.
    @return Size of the font in pixels.
  */
  uint getSize();

  /**
    Checks if font is bold.
    @bug currently does not work
    @returns 'true' if font is bold and 'false' otherwise.
  */
  bool isBold();

  /**
    Checks if font is italic.
    @bug currently does not work
    @returns 'true' if font is bold and 'false' otherwise.
  */
  bool isItalic();

  /**
    Checks if font is underlined.
    @bug currently does not work
    @returns 'true' if font is bold and 'false' otherwise.
  */
  bool isUnderlined();

  /**
    Checks if font is striked out.
    @bug currently does not work
    @returns 'true' if font is bold and 'false' otherwise.
  */
  bool isStrikeout();

  /**
    Returns font family.
    @return font family string.
  */
  std::wstring getFontFamily();
};

}

#endif // __VE_FONT_DESCRIPTOR_H__