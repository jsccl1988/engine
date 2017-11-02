// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "tools/linux_timer.h"
#include "tools/win_timer.h"
#include "tools/timer_factory.h"

namespace ve {

/**
  Creates instance of Timer class.
  @return Timer object
*/
Timer* TimerFactory::createTimer() {
#ifdef VE_LINUX
  return new LinuxTimer();
#else  
#ifdef VE_WINDOWS
  return new WinTimer();
#else
  return NULL;
#endif	// VE_WINDOWS
#endif // VE_LINUX
}

}