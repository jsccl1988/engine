// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_THREAD_FACTORY_H__
#define __VE_THREAD_FACTORY_H__

#include "common.h"

namespace ve {

#ifdef VE_WINDOWS
typedef unsigned long(*ThreadEntry) (void* lpParameter);
#endif // VE_WINDOWS

#ifdef VE_LINUX
typedef unsigned long(*ThreadEntry) (void* lpParameter);
#endif // VE_LINUX

/**
  Factory to instantiate platform-dependent threads.
*/
class ThreadFactory {
private:
  static ThreadFactory* instance;

  /**
    Private constuctor.
  */
  ThreadFactory();

  /**
    Private copy constructor.
  */
  ThreadFactory(ThreadFactory&);

  /**
    Private opeartor =.
  */
  void operator =(ThreadFactory&);

public:

  /**
    Get the single instance of ThreadFactory class.
    @return Instance of ThreadFactory class.
  */
  static ThreadFactory *getInstance();

  /**
    Creates thread with a given entry point.
    @param entry - Entry point for th thread.
    @param parameter - Parameter of the thread function.
    @return OK if thread was successfully started.
    @return ERROR if OS error occurred.
  */
  Outcome spawn(ThreadEntry entry, void* parameter);
};

}

#endif // __VE_THREAD_FACTORY_H__
