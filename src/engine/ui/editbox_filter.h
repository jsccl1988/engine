// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_EDITBOX_FILTER_H__
#define __VE_EDITBOX_FILTER_H__

namespace ve {

/**
    Controls text string in editbox. Use only one abstract method accept().
    It is used by Editbox when a key is pressed. If accept() returns true
    key press will be proceeeded, if not, it will be rejected.
    Can be used to edit numbers, for example.
*/
class EditboxFilter {
public:
  /**
      Defines if key newChar will be proceeded for the editbox.
      @param text - Text that is already in editbox.
      @param newChar - key code that was pressed by user.
      @return true if the key should be proceeded.
      @return false if shouldn't.
  */
  virtual bool accept(std::wstring text, wchar_t newChar) = 0;
};

}

#endif // __VE_EDITBOX_FILTER_H__
