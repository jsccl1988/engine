// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "events/system_event.h"

namespace ve {

SystemEvent::SystemEvent() {
}

SystemEvent::~SystemEvent() {
}

SystemEventType SystemEvent::getType() {
  return type;
}

}
