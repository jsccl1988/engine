// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include <algorithm>

#include "ui/desktop.h"
#include "ui/ui_control.h"

namespace ve {

Desktop::Desktop(UI *gui) :UIContainer(NULL) {
}

Desktop::~Desktop() {
}

Outcome Desktop::init() {
  return OK;
}

Outcome Desktop::render() {
  uint size = getObjectsCount();
  for (uint i = 0; i < size; i++) {
    ASSERT(getObject(i)->render());
  }
  return OK;
}

}