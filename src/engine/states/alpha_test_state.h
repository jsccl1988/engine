// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_ALPHA_TEST_STATE_H__
#define __VE_ALPHA_TEST_STATE_H__

namespace ve {

class AlphaTestState {
public:
  /**
      'true' if test is enabled and 'false' if not.
  */
  bool isEnabled;

  /**
      Comparison function that is used during alpha test.
  */
  Comparison func;

  /**
      Reference value for alpha test function.
  */
  float refValue;

  /**
      Default constructor. Alpha test is disabled.
  */
  AlphaTestState() {
    isEnabled = false;
    func = GREATER;
    refValue = 0;
  }

  /**
      Constructor that contains all the parameters of alpha testing stage.
      @param enabled - Defines if alpha testing is enabled.
      @param func - Comparison function for the alpha test.
      @param refValue - Reference value for the alpha test.
  */
  AlphaTestState(bool enabled, Comparison func, float refValue) {
    isEnabled = enabled;
    this->func = func;
    this->refValue = refValue;
  }
};

}

#endif // __VE_ALPHA_TEST_STATE_H__
