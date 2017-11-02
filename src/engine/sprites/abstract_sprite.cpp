// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "sprites/abstract_sprite.h"

namespace ve {

AbstractSprite::AbstractSprite(Engine *engine) {
  this->engine = engine;
  position = Vector3f(0, 0, 0);
  width = 0;
  height = 0;
  covered = false;

  // Register pointer in the memory manager
  REGISTER_POINTER(this);
}

AbstractSprite::~AbstractSprite() {
  // Unregister pointer in the memory manager
  UNREGISTER_POINTER(this);
}

void AbstractSprite::setCovered(bool value) {
  covered = value;
}

Outcome AbstractSprite::processMouseEvent(MouseEvent *event) {
  CHECK_POINTER(event);

  if (event->getType() == MOUSE_ENTER) {
    covered = true;
  }

  if (event->getType() == MOUSE_LEAVE) {
    covered = false;
  }

  return OK;
}

Outcome AbstractSprite::processKeyEvent(KeyEvent *event) {
  CHECK_POINTER(event);
  return OK;
}

/* set functions */
void AbstractSprite::setPosition(const Vector3f &newPosition) {
  position = newPosition;
}

void AbstractSprite::setPosition(float x, float y, float z) {
  position.set(x, y, z);
}

void AbstractSprite::setPosition(float x, float y) {
  position.set(x, y, position[2]);
}

void AbstractSprite::setSize(float newWidth, float newHeight) {
  width = newWidth;
  height = newHeight;
}

void AbstractSprite::setWidth(float newWidth) {
  width = newWidth;
}

void AbstractSprite::setHeight(float newHeight) {
  height = newHeight;
}

/* get functions */
Vector3f AbstractSprite::getPosition() {
  return position;
}

float AbstractSprite::getX() {
  return position[0];
}

float AbstractSprite::getY() {
  return position[1];
}

float AbstractSprite::getZ() {
  return position[2];
}

float AbstractSprite::getWidth() {
  return width;
}

float AbstractSprite::getHeight() {
  return height;
}

bool AbstractSprite::isCovered() {
  return covered;
}

}
