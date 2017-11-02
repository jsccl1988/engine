// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "events/key_event.h"
#include <cstdio>

namespace ve {

KeyEvent::KeyEvent(SystemEventType type) {
  this->type = type;
  keyCode = 0;
}

KeyEvent::KeyEvent(SystemEventType type, int theKeyCode) {
  this->type = type;
  keyCode = theKeyCode;
}

int KeyEvent::getKeyCode() {
  return keyCode;
}

void KeyEvent::setKeyCode(int newKeyCode) {
  keyCode = newKeyCode;
}

}
