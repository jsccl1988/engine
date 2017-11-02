// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "common.h"
#include "engines/device_caps.h"

namespace ve {

DeviceCaps::DeviceCaps(Engine *engine) {
  LOG_IF(engine == NULL, L"NULL Pointer");

  this->engine = engine;
}

}
