// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "sprites/animated_sprite.h"

namespace ve {

/**
    Default constructor.
    No frames are set for animation.
*/
AnimatedSprite::AnimatedSprite(Engine *engine) :Sprite(engine) {
  setCurrentFrame(0);
  setFPS(1.0);
  setAnimation(0);
}

/**
    Extended constructor.
    No frames are set for animation.
    @param engine - Engine object that creates this sprite.
    @param animationListsCount - Number of animations supported by
    this sprite.
*/
AnimatedSprite::AnimatedSprite(Engine *engine, uint animationListsCount) :Sprite(engine) {
  setCurrentFrame(0);
  setFPS(1.0);
  setAnimation(0);
  frames.resize(animationListsCount);
}

/**
    Changes number of animations supported by
    this sprite.
    @param count - New number of animations supported by
    this sprite.
*/
void AnimatedSprite::setAnimationListsCount(uint count) {
  frames.resize(count);
}

/**
    Changes animation for this sprite. Changes nothing if animation
    number is out of bounds.
    @param animation - Animation list to use.
*/
void AnimatedSprite::setAnimation(uint animation) {
  if (animation < frames.size()) {
    currentAnimation = animation;
    setCurrentFrame(0);
  }
}

/**
    Returns current animation number.
    @return Current animation number.
*/
uint AnimatedSprite::getAnimation() {
  return currentAnimation;
}

/**
    Returns current frame of animation.
    @return Current frame of animation.
    @return 0 if no frames were set.
*/
uint AnimatedSprite::getCurrentFrame() {
  return currentFrame;
}

/**
    Changes current frame of animation. if frame
    number is out of bounds it will not be changed.
    @param frame - Frame number to set as current.
*/
void AnimatedSprite::setCurrentFrame(uint frame) {
  if (currentAnimation < frames.size() && frame < frames[currentAnimation].size()) {
    currentFrame = frame;
    timeRemained = 1000 / FPS;

    FrameData fd = frames[currentAnimation][currentFrame];
    setTexCoords(0, fd.p1);
    setTexCoords(1, fd.p2);
    setTexCoords(2, fd.p3);
    setTexCoords(3, fd.p4);
  }
}

/**
    Returns animation's FPS.
    @return Animation's FPS.
*/
float AnimatedSprite::getFPS() {
  return FPS;
}

/**
    Changes FPS parameter for this animation.
    @param newFPS - new FPS value for this animation.
*/
void AnimatedSprite::setFPS(float newFPS) {
  if (newFPS < 0) {
    LOG_ERROR(L"Negative FPS value");
  } else {
    FPS = newFPS;
    timeRemained = 1000 / FPS;
  }
}

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
Outcome AnimatedSprite::genQuadFrames(uint animation, Vector2f leftBottomCorner, Vector2f size, Vector2f shift, uint count) {
  ERROR_IF(animation >= frames.size(), L"Animation number is out of bounds", INVALID_VALUE);

  frames[animation].clear();
  for (uint i = 0; i < count; i++) {
    frames[animation].push_back(FrameData(leftBottomCorner, size));
    leftBottomCorner = leftBottomCorner + shift;
  }

  return OK;
}

/**
    Changes current frame assuming that 'msec' milliseconds passed.
    @param msec - Time in milliseconds between successive move() calls.
*/
void AnimatedSprite::move(uint msec) {
  bool needChange = false;

  timeRemained = timeRemained - msec;
  /* Check if next frame or several frames occurred */
  while (timeRemained <= 0) {
    timeRemained = timeRemained + 1000 / FPS;
    currentFrame++;
    needChange = true;
  }

  ERROR_IF(currentAnimation >= frames.size(), L"Incorrect animation index: " +
    StringTool::intToStr(currentAnimation), ;);

  ERROR_IF(frames[currentAnimation].size() == 0, L"No frames were set for animation: " +
    StringTool::intToStr(currentAnimation), ;);

  if (needChange) {
    currentFrame = currentFrame % frames[currentAnimation].size();

    FrameData fd = frames[currentAnimation][currentFrame];
    setTexCoords(0, fd.p1);
    setTexCoords(1, fd.p2);
    setTexCoords(2, fd.p3);
    setTexCoords(3, fd.p4);
  }
}

}
