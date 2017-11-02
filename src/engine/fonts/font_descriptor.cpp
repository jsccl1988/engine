// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "fonts/font_descriptor.h"
#include "tools/string_tool.h"

namespace ve {

FontDescriptor::FontDescriptor() {
  format = L"-*-courier-bold-r-normal--12-*-*-*-*-*-*-*";
}

FontDescriptor::FontDescriptor(std::wstring familyNameField, FontSlant slantField, FontSetWidth setWidthField,
  int pixelSize, FontSpacing spacingField, int resolutionX, int resolutionY) {
  const wchar_t* fontSlantMap[] = { L"R", L"I", L"O", L"RI", L"RO", L"OT", L"" };
  const wchar_t* fontSetWidthMap[] = { L"Norma", L"Condensed", L"Narrow", L"Double wide", L"" };
  const wchar_t* fontSpacingMap[] = { L"P", L"M", L"C", L"" };

  int slantIndex = static_cast<int>(slantField);
  int setWidthIndex = static_cast<int>(setWidthField);
  int spacingIndex = static_cast<int>(spacingField);

  size = pixelSize;
  bold = (setWidthField == SETWIDTH_DOUBLE_WIDE);
  italic = (slantField == SLANT_ITALIC) || (slantField == SLANT_REVERSE_ITALIC);
  strikeout = false;
  underlined = false;
  fontFamily = familyNameField;

  /* Check all parameters */
  ERROR_IF(slantIndex >= sizeof(fontSlantMap) / sizeof(wchar_t*), L"Unknown font slant", ;);
  ERROR_IF(setWidthIndex >= sizeof(fontSetWidthMap) / sizeof(wchar_t*), L"Unknown font \"SETWIDTH\" value", ;);
  ERROR_IF(spacingIndex >= sizeof(fontSpacingMap) / sizeof(wchar_t*), L"Unknown spacing", ;);

  format = L"-*-" + familyNameField + L"-*-";

  if (slantField != SLANT_ANY) {
    format = format + fontSlantMap[slantIndex] + L"-";
  } else {
    format += L"*-";
  }

  if (setWidthField != SETWIDTH_ANY) {
    format = format + fontSetWidthMap[setWidthIndex] + L"--";
  } else {
    format += L"*--";
  }

  if (pixelSize != 0) {
    format += StringTool::intToStr(pixelSize) + L"-*-";
  } else {
    format += L"*-*-";
  }

  if (resolutionX != 0) {
    format += StringTool::intToStr(resolutionX) + L"-";
  } else {
    format += L"*-";
  }

  if (resolutionY != 0) {
    format += StringTool::intToStr(resolutionY) + L"-";
  } else {
    format += L"*-";
  }

  if (spacingField != SPACING_ANY) {
    format += fontSpacingMap[spacingIndex];
  } else {
    format += L"*";
  }

  format += L"-*-*";
}

std::wstring FontDescriptor::getFormatString() {
  return format;
}

void FontDescriptor::setFormatString(std::wstring format) {
  this->format = format;
}

uint FontDescriptor::getSize() {
  return size;
}

/**
  Checks if font is bold.
    @returns 'true' if font is bold and 'false' otherwise.
*/
bool FontDescriptor::isBold() {
  return bold;
}

/**
  Checks if font is italic.
  @bug currently does not work
  @returns 'true' if font is bold and 'false' otherwise.
*/
bool FontDescriptor::isItalic() {
  return italic;
}

/**
  Checks if font is underlined.
  @bug currently does not work
  @returns 'true' if font is bold and 'false' otherwise.
*/
bool FontDescriptor::isUnderlined() {
  return underlined;
}

/**
  Checks if font is striked out.
  @bug currently does not work
  @returns 'true' if font is bold and 'false' otherwise.
*/
bool FontDescriptor::isStrikeout() {
  return strikeout;
}

/**
  Returns font family.
  @return font family string.
*/
std::wstring FontDescriptor::getFontFamily() {
  return fontFamily;
}

}
