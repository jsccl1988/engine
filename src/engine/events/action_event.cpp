// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "events/action_event.h"

namespace ve {

ActionEvent::ActionEvent(SystemEventType type, UIControl* sender) {
  this->type = type;
  this->sender = sender;
}

ActionEvent::~ActionEvent() {
}

UIControl* ActionEvent::getSender() {
  return sender;
}

}
