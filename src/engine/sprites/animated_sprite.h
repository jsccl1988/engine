// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_ANIMATED_SPRITE_H__
#define __VE_ANIMATED_SPRITE_H__

#include "engine/common.h"
#include "engine/sprites/sprite.h"
#include "engine/math/maths.h"

namespace ve {

/**
    Animated sprite for 2D games. Changes sprite image with a specified FPS.
    All it does: changes texture coordinates for sprites. So, to animate
    the sprite you should set texture coordinates for all the frames of your
    animation. They should be placed at one texture. To make it easier to
    generate texture coordinates genQuadFrames() function may be used.
    To stop animation use zero FPS value.
*/
class AnimatedSprite : public Sprite {
private:

  /**
      It is used to store texture coordinates
      for animation frame with following mapping to a screen:

      /------------------------ X
      |
      |   (p1)----(p4)
      |    |       |
      |    |       |
      |   (p2)----(p3)
      Y

  */
  struct FrameData {
    Vector2f p1;
    Vector2f p2;
    Vector2f p3;
    Vector2f p4;

    FrameData(Vector2f p1, Vector2f p2, Vector2f p3, Vector2f p4) {
      this->p1 = p1;
      this->p2 = p2;
      this->p3 = p3;
      this->p4 = p4;
    }

    FrameData(Vector2f upperLeft, Vector2f size) {
      p1 = upperLeft;

      p2[0] = upperLeft[0] + size[0];
      p2[1] = upperLeft[1];

      p3 = upperLeft + size;

      p4[0] = upperLeft[0];
      p4[1] = upperLeft[1] + size[1];
    }
  };

  /** Current animation */
  uint currentAnimation;

  /** Current frame */
  uint currentFrame;

  /** Texture coordinates for frames for several animations */
  vector< vector<FrameData> > frames;

  /** Animation FPS */
  float FPS;

  /** Time in mseconds remained to next frame */
  float timeRemained;

public:
  /**
      Default constructor.
      No frames are set for animation.
      @param engine - Engine object that creates this sprite.
  */
  AnimatedSprite(Engine *engine);

  /**
      Extended constructor.
      No frames are set for animation.
      @param engine - Engine object that creates this sprite.
      @param animationListsCount - Number of animations supported by
      this sprite.
  */
  AnimatedSprite(Engine *engine, uint animationListsCount);

  /**
      Changes number of animations supported by
      this sprite.
      @param count - New number of animations supported by
      this sprite.
  */
  void setAnimationListsCount(uint count);

  /**
      Changes animation for this sprite. Changes nothing if animation
      number is out of bounds.
      @param animation - Animation list to use.
  */
  void setAnimation(uint animation);

  /**
      Returns current animation number.
      @return Current animation number.
  */
  uint getAnimation();

  /**
      Returns current frame of animation.
      @return Current frame of animation.
      @return 0 if no frames were set.
  */
  uint getCurrentFrame();

  /**
      Changes current frame of animation. if frame
      number is out of bounds it will not be changed.
      @param frame - Frame number to set as current.
  */
  void setCurrentFrame(uint frame);

  /**
      Returns animation's FPS.
      @return Animation's FPS.
  */
  float getFPS();

  /**
      Changes FPS parameter for this animation.
      @param newFPS - new FPS value for this animation.
  */
  void setFPS(float newFPS);

  /**
      Generates texture coordinates for frames which are located
      at the texture in form of rectangles with constant distance
      between successive frames.

      The following algorithm is applied to generate texture coordinates:
      <ul>
      <li>Use leftBottomCorner and Size to generate texture coordinates for
      the first frame</li>
      <li>If it was not last frame then shift leftBottomCorner on shift vector and
      go to the first step</li>
      </ul>

      @param animation - Animation number to generate frames for.
      @param leftBottomCorner - Texture coordinates of the left-upper
      corner of the first frame.
      @param size - Size of frame in texture coordinates.
      @param shift - Shift in texture coordinates between successive frames.
      @param count - Number of frame to generate texture coordinates for.
      @return OK if operation succeeded.
      @return INVALID_VALUE if animation number is out of bound.
  */
  Outcome genQuadFrames(uint animation, Vector2f leftBottomCorner, Vector2f size, Vector2f shift, uint count);

  /**
      Changes current frame assuming that 'msec' milliseconds passed.
      @param msec - Time in milliseconds between successive move() calls.
  */
  virtual void move(uint msec);
};

}

#endif // __VE_ANIMATED_SPRITE_H__
