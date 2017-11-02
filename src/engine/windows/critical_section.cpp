// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "windows/critical_section.h"

namespace ve {

CriticalSection::CriticalSection() {
#ifdef VE_WINDOWS
  InitializeCriticalSection(&criticalSection);
#endif // VE_WINDOWS
#ifdef VE_LINUX
  mutex = PTHREAD_MUTEX_INITIALIZER;
#endif // VE_LINUX
}

CriticalSection::~CriticalSection() {
#ifdef VE_WINDOWS
  DeleteCriticalSection(&criticalSection);
#endif // VE_WINDOWS
}

void CriticalSection::lock() {
#ifdef VE_WINDOWS
  EnterCriticalSection(&criticalSection);
#endif // VE_WINDOWS
#ifdef VE_LINUX
  pthread_mutex_lock(&mutex);
#endif // VE_LINUX
}

void CriticalSection::unlock() {
#ifdef VE_WINDOWS
  LeaveCriticalSection(&criticalSection);
#endif // VE_WINDOWS
#ifdef VE_LINUX
  pthread_mutex_unlock(&mutex);
#endif // VE_LINUX
}

}
