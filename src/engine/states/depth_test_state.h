// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_DEPTH_TEST_STATE_H__
#define __VE_DEPTH_TEST_STATE_H__

namespace ve {

class DepthTestState {
public:
  /**
      'true' if test is enabled and 'false' if not.
  */
  bool isEnabled;

  /**
      Comparison function that is used during depth test.
  */
  Comparison func;

  /**
      Mask that enables/disables writting into z-buffer.
  */
  bool depthMask;

  /**
    Default constructor. Depth test is disabled.
  */
  DepthTestState() {
    isEnabled = false;
    func = LEQUAL;
    depthMask = true;
  }

  /**
    Depth test is enabled and the given function will be used in depth comparison.
  */
  DepthTestState(Comparison func) {
    isEnabled = true;
    this->func = func;
    depthMask = true;
  }
};

}

#endif // __VE_DEPTH_TEST_STATE_H__
