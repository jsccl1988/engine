// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_WINDOW_SYSTEM_FACTORY_H__
#define __VE_WINDOW_SYSTEM_FACTORY_H__

#include "engine/common.h"
#include "engine/windows/window_system.h"

namespace ve {

/**
  Class that is used to instanciate correct version of the WindowSystem class.
*/
class WindowSystemFactory {
public:
  /**
    Returns appropriate implementation of the WindowSystem class.
    @return Implementation of the WindowSystem class.
  */
  static WindowSystem* createWindowSystem();
};

}

#endif // __VE_WINDOW_SYSTEM_FACTORY_H__