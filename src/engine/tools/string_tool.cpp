// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include <cstdio>
#include <cstdlib>

#include <cmath>
#include "tools/string_tool.h"

namespace ve {

/**
    Translates integer value into wide string.
    @param value - value to translate.
    @return Wide string which contains this value as a text.
*/
std::wstring StringTool::intToStr(int value) {
  wchar_t buf[100];
  int digit = 0;
  bool negative = value < 0;

  value = abs(value);

  do {
    buf[digit++] = value % 10 + L'0';
    value /= 10;
  } while (value != 0);

  std::wstring result = L"";
  for (int i = 0; i < digit; i++) {
    result += buf[digit - i - 1];
  }

  if (negative) {
    result = L"-" + result;
  }

  return result;
}

/**
    Translates float value into wide string.
    @param value - value to translate.
    @param digits - number of digits to use after decimal point.
    @return Wide string which contains this value as a text.
*/
std::wstring StringTool::floatToStr(float value, int digits) {
  std::wstring result = intToStr(floor(value)) + L".";
  value = value - floor(value);

  for (int i = 0; i < digits; i++) {
    value = value * 10;
    result = result + (wchar_t)(floor(value) + L'0');
    value = value - floor(value);
  }

  return result;
}

/**
    Translates integer value into ASCII string.
    @param value - value to translate.
    @return ASCII string which contains this value as a text.
*/
std::string StringTool::intToStrA(int value) {
  char buf[100];
  int digit = 0;
  bool negative = value < 0;

  value = abs(value);

  do {
    buf[digit++] = value % 10 + '0';
    value /= 10;
  } while (value != 0);

  std::string result = "";
  for (int i = 0; i < digit; i++) {
    result += buf[digit - i - 1];
  }

  if (negative) {
    result = "-" + result;
  }

  return result;
}

/**
    Translates string to integer number. In case of non digit chars in the string
    (except minus sign at the first position) zero will be returned.
    @param value - String to convert to integer.
    @return integer value that is contained in this string.
    @return 0 if string contains not a number.
*/
int StringTool::strToInt(std::wstring value) {
  int result = 0;
  uint len = value.length();

  if (len == 0) {
    return 0;
  }

  for (uint i = 0; i < len; i++) {
    if (value[i] == L'-' && i == 0) {
      continue;
    }

    if (value[i] < L'0' || value[i] > L'9') {
      return 0;
    }

    result = result * 10 + value[i] - L'0';
  }

  if (value[0] == L'-') {
    result = -result;
  }

  return result;
}

/**
    Translates float value into ASCII string.
    @param value - value to translate.
    @param digits - number of digits to use after decimal point.
    @return ASCII string which contains this value as a text.
*/
std::string StringTool::floatToStrA(float value, int digits) {
  std::string result = intToStrA(floor(value)) + ".";
  value = value - floor(value);

  for (int i = 0; i < digits; i++) {
    value = value * 10;
    result = result + (char)(floor(value) + '0');
    value = value - floor(value);
  }

  return result;
}

bool StringTool::isPrintable(int code) {
  return (code >= 'a' && code <= 'z') || (code >= 'A' && code <= 'Z') || (code >= '0' && code <= '9')
    || code == ' ';
}

/**
    Translates ASCII string to wide string by extending char type to wchar_t using
    leading zero byte.
    @param str - ASCII string to translate.
    @return Wide string.
*/
std::wstring StringTool::AsciiToWide(std::string str) {
  std::wstring result = L"";
  int len = str.length();

  for (int i = 0; i < len; i++) {
    result = result + (wchar_t)str[i];
  }

  return result;
}

/**
    Translates Wide string to ASCII string by ignoring the first byte.
    @param str - ASCII string to translate.
    @return Wide string.
*/
std::string StringTool::WideToAscii(std::wstring wstr) {
  std::string result = "";
  ve::uint len = wstr.length();

  for (ve::uint i = 0; i < len; i++) {
    result = result + (char)wstr[i];
  }

  return result;
}

/**
    Remove all the space symbols in the beginning and at the end of the string.
    @param str - String to trim.
    @return Trimmed string.
*/
std::string StringTool::trim(std::string str) {
  uint start = 0;
  uint end = 0;
  ve::uint len = str.length();

  while (start < len && isspace(str[start])) start++;

  if (start == len) {
    // While string is a set of spaces.
    return "";
  }

  // Ok, there is at least one non-space symbol inside.
  end = len - 1;
  while (end > start && isspace(str[end])) end--;

  return str.substr(start, end - start + 1);
}

/**
    Remove all the space symbols in the beginning and at the end of the string.
    @param wstr - String to trim.
    @return Trimmed string.
*/
std::wstring StringTool::trim(std::wstring wstr) {
  uint start = 0;
  uint end = 0;
  ve::uint len = wstr.length();

  while (start < len && isspace(wstr[start])) start++;

  if (start == len) {
    // While string is a set of spaces.
    return L"";
  }

  // Ok, there is at least one non-space symbol inside.
  end = len - 1;
  while (end > start && isspace(wstr[end])) end--;

  return wstr.substr(start, end - start + 1);
}

/**
    Returns file extension from file name. Returns the part of the file name
    that is after the last point. If there is no point in the string empty
    string will be returned as a result.
    @param fileName - File name to extract extension.
    @return Extension of the file or empty string.
*/
std::string StringTool::getFileExtension(std::string fileName) {
  ve::uint len = fileName.size();
  std::string result = "";

  for (ve::uint i = len - 1; i >= 0; i--) {
    if (fileName[i] == '.') {
      return result;
    } else {
      result = fileName[i] + result;
    }
  }

  return "";
}

/**
    Converts all the letters in the string to lower case and returns the
    resulted string. No changes are made for non-letter symbols.
    @param s - String to convert to lower case.
    @return String with lower case letters only.
*/
std::string StringTool::toLowerCase(std::string s) {
  std::string result = "";
  ve::uint len = s.size();

  for (ve::uint i = 0; i < len; i++) {
    if (s[i] >= 'A' && s[i] <= 'Z') {
      result = result + char(s[i] - 'A' + 'a');
    } else {
      result = result + s[i];
    }
  }

  return result;
}

}
