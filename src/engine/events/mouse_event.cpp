// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "events/mouse_event.h"

namespace ve {

MouseEvent::MouseEvent(SystemEventType type) {
  this->type = type;
}

MouseEvent::MouseEvent(SystemEventType type, MouseButton button, int x, int y, int mouseX, int mouseY) {
  this->type = type;
  this->x = x;
  this->y = y;
  this->mouseX = mouseX;
  this->mouseY = mouseY;
  this->button = button;
}

int MouseEvent::getX() {
  return x;
}

int MouseEvent::getY() {
  return y;
}

int MouseEvent::getMouseX() {
  return mouseX;
}

int MouseEvent::getMouseY() {
  return mouseY;
}

MouseButton MouseEvent::getButton() {
  return button;
}

void MouseEvent::setX(int newX) {
  x = newX;
}

void MouseEvent::setY(int newY) {
  y = newY;
}

void MouseEvent::setButton(MouseButton newButton) {
  button = newButton;
}

}
