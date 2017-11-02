// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_CRITICAL_SECTION_H__
#define __VE_CRITICAL_SECTION_H__

#include "common.h"

namespace ve {

/**
  Critical section that could be used to synchronize access
  for several threads.
*/
class CriticalSection {
private:
#ifdef VE_WINDOWS
  CRITICAL_SECTION criticalSection;
#endif // VE_WINDOWS
#ifdef VE_LINUX
  pthread_mutex_t mutex;
#endif // VE_LINUX
public:
  /**
    Constructor. Initializes OS critical section.
  */
  CriticalSection();

  /**
    Destructor. Releases crititical section.
  */
  ~CriticalSection();

  /**
    Locks critical section.
  */
  void lock();

  /**
    Unlocks critical section.
  */
  void unlock();
};

}

#endif // __VE_CRITICAL_SECTION_H__
