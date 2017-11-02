// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "events/window_event.h"

namespace ve {

WindowEvent::WindowEvent(SystemEventType type) {
  this->type = type;
}

WindowEvent::WindowEvent(SystemEventType type, int theWidth, int theHeight) {
  this->type = type;
  width = theWidth;
  height = theHeight;
}

int WindowEvent::getWidth() {
  return width;
}

void WindowEvent::setWidth(int newWidth) {
  width = newWidth;
}

int WindowEvent::getHeight() {
  return height;
}

void WindowEvent::setHeight(int newHeight) {
  height = newHeight;
}

}
