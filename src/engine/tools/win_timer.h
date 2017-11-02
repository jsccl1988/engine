// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifdef VE_WINDOWS

#ifndef __VE_WIN_TIMER_H__
#define __VE_WIN_TIMER_H__

#include "tools/timer.h"

namespace ve {

/**
    Class for to measure elapsed time.
*/
class WinTimer : public Timer {
private:
  /** Time when it was reset last time */
  DWORD ticks;

public:
  /**
      Default constructor.
  */
  WinTimer();

  /**
      Resets timer.
  */
  virtual void reset();

  /**
      Returns milliseconds elapsed since last reset.
      @return Milliseconds elapsed since last reset.
  */
  virtual uint getElapsedTime();
};

}

#endif // __VE_WIN_TIMER_H__

#endif