// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_TIMER_H__
#define __VE_TIMER_H__

#include <ctime>

#include "engine/common.h"

namespace ve {

/**
    Abstract class to measure elapsed time.
*/
class Timer {
public:
  /**
      Resets timer.
  */
  virtual void reset() = 0;

  /**
      Returns milliseconds elapsed since last reset.
      @return Milliseconds elapsed since last reset.
  */
  virtual uint getElapsedTime() = 0;
};

}

#endif // __VE_TIMER_H__
