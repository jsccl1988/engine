// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifdef VE_WINDOWS

#include "tools/win_timer.h"

namespace ve {

/**
    Default constructor.
*/
WinTimer::WinTimer() {
  ticks = GetTickCount();
}

/**
    Resets timer.
*/
void WinTimer::reset() {
  ticks = GetTickCount();
}

/**
    Returns milliseconds elapsed since last reset.
    @return Milliseconds elapsed since last reset.
*/
uint WinTimer::getElapsedTime() {
  return GetTickCount() - ticks;
}

}

#endif // VE_WINDOWS