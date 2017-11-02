// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_EDITBOX_NUMBERS_FILTER_H__
#define __VE_EDITBOX_NUMBERS_FILTER_H__

#include <string>

#include "ui/editbox_filter.h"

namespace ve {

/**
    Controls text string in editbox to edit only positive numbers in predefined range.
*/
class EditboxNumbersFilter : public EditboxFilter {
private:
  int minValue;
  int maxValue;

public:
  /**
      Default constructor.
      Sets possible numbers range to the 0 and to the maximum value of
      int type.
  */
  EditboxNumbersFilter();

  /**
      Constructor that specifies the range of possible numbers in editbox.
  */
  EditboxNumbersFilter(int minValue, int maxValue);

  /**
      Defines if key newChar will be proceeded for the editbox.
      @param text - Text that is already in editbox.
      @param newChar - key code that was pressed by user.
      @return true if the key pressed is digit and new number (that is formed with this new key)
      is is range of this filter.
      @return false in other cases.
  */
  virtual bool accept(std::wstring text, wchar_t newChar);
};

}

#endif // __VE_EDITBOX_NUMBERS_FILTER_H__
