// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "windows/xwindow_system.h"
#include "windows/windows_system.h"
#include "windows/window_system_factory.h"

namespace ve {

/**
  Returns appropriate implementation of the WindowSystem class.
  @return Implementation of the WindowSystem class.
*/
WindowSystem* WindowSystemFactory::createWindowSystem() {
#ifdef VE_LINUX
  return new XWindowSystem();
#else
#ifdef VE_WINDOWS
  return new WindowsSystem();
#else
  LOG_ERROR(L"Unsupported version of the window system");
  return NULL;
#endif // VE_WINDOWS
#endif // VE_LINUX
}

}