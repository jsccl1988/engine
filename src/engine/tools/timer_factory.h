// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "engine/tools/timer.h"

namespace ve {

  /**
    Factory that instantiate correct version of Timer class for current OS.
  */
  class TimerFactory {
  public:

    /**
      Creates instance of Timer class.
      @return Timer object
    */
    static Timer* createTimer();
  };

}