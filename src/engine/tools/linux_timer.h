// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifdef VE_LINUX

#ifndef __VE_LINUX_TIMER_H__
#define __VE_LINUX_TIMER_H__

#include "tools/timer.h"

namespace ve {

/**
    Class for to measure elapsed time.
*/
class LinuxTimer : public Timer {
private:
  /** Time when it was reset last time */
  timespec lastReset;

public:
  /**
      Default constructor.
  */
  LinuxTimer();

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

#endif // __VE_LINUX_TIMER_H__

#endif // VE_LINUX