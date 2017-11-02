// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include <limits>

#include "ui/editbox_numbers_filter.h"
#include "tools/string_tool.h"

namespace ve {

/**
    Default constructor.
    Sets possible numbers range to the 0 and to the maximum value of
    int type.
*/
EditboxNumbersFilter::EditboxNumbersFilter() {
  minValue = 0;
  maxValue = std::numeric_limits<int>::max();
}

/**
    Constructor that specifies the range of possible numbers in editbox.
*/
EditboxNumbersFilter::EditboxNumbersFilter(int minValue, int maxValue) {
  this->minValue = minValue;
  this->maxValue = maxValue;
}

/**
    Defines if key newChar will be proceeded for the editbox.
    @param text - Text that is already in editbox.
    @param newChar - key code that was pressed by user.
    @return true if the key pressed is digit and new number (that is formed with this new key)
    is is range of this filter.
    @return false in other cases.
*/
bool EditboxNumbersFilter::accept(std::wstring text, wchar_t newChar) {
  if (newChar < L'0' || newChar > L'9') {
    return false;
  }

  text = text + newChar;

  int number = StringTool::strToInt(text);
  return number >= minValue && number <= maxValue;
}

}
