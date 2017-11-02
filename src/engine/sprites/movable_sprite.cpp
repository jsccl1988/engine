// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "sprites/movable_sprite.h"

namespace ve {

/**
    Default constructor. Speed is set to 1 unit/sec.
*/
MovableSprite::MovableSprite(Engine *engine) : AnimatedSprite(engine) {
  speed = 1.0;
}

/**
    Extended constructor. Creates sprite with specified speed.
    @param theSpeed - speed of this sprite.
*/
MovableSprite::MovableSprite(Engine *engine, float theSpeed) :AnimatedSprite(engine) {
  speed = theSpeed;
}

/**
    Changes speed of this sprite.
    @param newSpeed - new speed of this sprite.
*/
void MovableSprite::setSpeed(float newSpeed) {
  speed = newSpeed;
}

/**
    Returns current speed of this sprite.
    @return Speed of this sprite.
*/
float MovableSprite::getSpeed() {
  return speed;
}

/**
    Moves sprite along specified direction, computing shift from a given
    time and assuming that sprite moves during this time with a constant speed.
    @param msec - time in milliseconds to compute sprite movement.
    @param direction - vector that defines direction of the movement.
*/
void MovableSprite::move(uint msec, Vector3f direction) {
  /* Perform animation */
  AnimatedSprite::move(msec);

  /* Compute shift distance */
  float shiftValue = speed * msec / 1000.0;

  /* Normalize direction vector */
  direction.norm();

  setPosition(getPosition() + direction * shiftValue);
}

}
