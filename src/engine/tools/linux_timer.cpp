// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifdef VE_LINUX

#include "tools/linux_timer.h"

namespace ve {

/**
    Default constructor.
*/
LinuxTimer::LinuxTimer() {
  clock_gettime(CLOCK_REALTIME, &lastReset);
}

/**
    Resets timer.
*/
void LinuxTimer::reset() {
  clock_gettime(CLOCK_REALTIME, &lastReset);
}

/**
    Returns milliseconds elapsed since last reset.
    @return Milliseconds elapsed since last reset.
*/
uint LinuxTimer::getElapsedTime() {
  const unsigned long NANO_TO_MILI = 1000000;
  timespec now;
  clock_gettime(CLOCK_REALTIME, &now);
  return (now.tv_sec - lastReset.tv_sec) * 1000 + (double)(now.tv_nsec - lastReset.tv_nsec) / (double)NANO_TO_MILI;
}

}

#endif // VE_LINUX