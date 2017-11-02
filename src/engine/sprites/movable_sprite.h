// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_MOVABLE_SPRITE_H__
#define __VE_MOVABLE_SPRITE_H__

#include "engine/sprites/animated_sprite.h"

namespace ve {

/**
    Class to represent movable animated units in 2D games. It is based on
    AnimatedSprite, but move() functions works in a bit different way.
    It changes animation frames as before and moves sprite along a given direction.
    Only movement speed should be set for this sprite to make it works.
    Speed unit: (coordinate units) / sec.
*/
class MovableSprite : public AnimatedSprite {
private:
  float speed;

public:
  /**
      Default constructor. Speed is set to 1 unit/sec.
      @param engine - Engine object that creates this sprite.
  */
  MovableSprite(Engine *engine);

  /**
      Extended constructor. Creates sprite with specified speed.
      @param engine - Engine object that creates this sprite.
      @param theSpeed - speed of this sprite.
  */
  MovableSprite(Engine *engine, float theSpeed);

  /**
      Changes speed of this sprite.
      @param newSpeed - new speed of this sprite.
  */
  void setSpeed(float newSpeed);

  /**
      Returns current speed of this sprite.
      @return Speed of this sprite.
  */
  float getSpeed();

  /**
      Moves sprite along specified direction, computing shift from a given
      time and assuming that sprite moves during this time with a constant speed.
      @param msec - time in milliseconds to compute sprite movement.
      @param direction - vector that defines direction of the movement.
  */
  virtual void move(uint msec, Vector3f direction);
};

}

#endif // __VE_MOVABLE_SPRITE_H__
