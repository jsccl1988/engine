// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_STRING_TOOL_H__
#define __VE_STRING_TOOL_H__

#include <string>

#include "engine/common.h"

namespace ve {

/**
    Contains useful static functions to work with std::string objects.
*/
class StringTool {
public:
  /**
      Translates integer value into wide string.
      @param value - value to translate.
      @return Wide string which contains this value as a text.
  */
  static std::wstring intToStr(int value);

  /**
      Translates float value into wide string.
      @param value - value to translate.
      @param digits - number of digits to use after decimal point.
      @return Wide string which contains this value as a text.
  */
  static std::wstring floatToStr(float value, int digits);

  /**
      Translates integer value into ASCII string.
      @param value - value to translate.
      @return ASCII string which contains this value as a text.
  */
  static std::string intToStrA(int value);

  /**
      Translates string to integer number. In case of non digit chars in the string
      (except minus sign at the first position) zero will be returned.
      @param value - String to convert to integer.
      @return integer value that is contained in this string.
      @return 0 if string contains not a number.
  */
  static int strToInt(std::wstring value);

  /**
      Translates float value into ASCII string.
      @param value - value to translate.
      @param digits - number of digits to use after decimal point.
      @return ASCII string which contains this value as a text.
  */
  static std::string floatToStrA(float value, int digits);

  /**
      Translates ASCII string to wide string by extending char type to wchar_t using
      leading zero byte.
      @param str - ASCII string to translate.
      @return Wide string.
  */
  static std::wstring AsciiToWide(std::string str);

  /**
      Translates Wide string to ASCII string by ignoring the first byte.
      @param wstr - Wide string to transcode.
      @return Ascii string.
  */
  static std::string WideToAscii(std::wstring wstr);

  /**
      Not a good function at all. Need to rewise logic.
  */
  static bool isPrintable(int code);

  /**
      Remove all the space symbols in the beginning and at the end of the string.
      @param str - String to trim.
      @return Trimmed string.
  */
  static std::string trim(std::string str);

  /**
      Remove all the space symbols in the beginning and at the end of the string.
      @param wstr - String to trim.
      @return Trimmed string.
  */
  static std::wstring trim(std::wstring wstr);

  /**
      Returns file extension from file name. Returns the part of the file name
      that is after the last point. If there is no point in the string empty
      string will be returned as a result.
      @param fileName - File name to extract extension.
      @return Extension of the file or empty string.
  */
  static std::string getFileExtension(std::string fileName);

  /**
      Converts all the letters in the string to lower case and returns the
      resulted string. No changes are made for non-letter symbols.
      @param s - String to convert to lower case.
      @return String with lower case letters only.
  */
  static std::string toLowerCase(std::string s);
};

}

#endif // __VE_STRING_TOOL_H__
