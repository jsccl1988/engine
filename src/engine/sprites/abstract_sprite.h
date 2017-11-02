// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_ABSTRACT_SPRITE_H__
#define __VE_ABSTRACT_SPRITE_H__

#include "engine/common.h"
#include "engine/visible_object.h"
#include "engine/math/vector3f.h"
#include "engine/events/mouse_listener.h"
#include "engine/events/key_listener.h"
#include "engine/states/blend_state.h"
#include "engine/states/alpha_test_state.h"

namespace ve {

class Engine;

/**
    AbstractSprite is a base class for every sprite on a screen
    which is represented like a quad area on a screen. Usually
    it lies in XOY screen-plane like all GUI components in any window system.
    All interface components, for example based on AbstractSprite class.

    It contains only very basic properties that every sprite should have.
    They are:
    <ul>
    <li>position - Defines left-upper corner of sprite</li>
    <li>width - Width of rectangular area which this sprite holds</li>
    <li>height - Height of rectangular area which this sprite holds</li>
    <li>visible - boolean flag which keeps sprite visible/invisible on a screen</li>
    </ul>

    AbstractSprite is always in rectangular area of the screen. But it does not
    mean, for example, that it should be also rectangular. Use Sprite class
    to make sprite in any shape (using alpha channel or key-colors).
*/
class AbstractSprite : public VisibleObject, public MouseListener, public KeyListener {
private:
  /** Defines if sprite is covered by the mouse */
  bool covered;

  /** Left-upper corner position on the screen */
  Vector3f position;

  /** Width of rectanglular boundaty */
  float width;

  /** Height of rectangular boundary */
  float height;

protected:
  /** Engine which created this sprite */
  Engine *engine;

  /**
      Sets 'covered' flag to specified value.
      @param value - New value for 'covered' flag.
  */
  void setCovered(bool value);

public:
  /**
      AbstractSprite constructor. Registers sprite in the memory manager.
      @param Engine - engine class which creates this sprite.
  */
  AbstractSprite(Engine *engine);

  /**
    AbstractSprite destructor. Removes pointer from the memory manager.
  */
  virtual ~AbstractSprite();

  /**
      Renders sprite.
      @return OK if rendering succeeded.
      @return non-OK if error occurred.
  */
  virtual Outcome render() = 0;

  /**
      Handles MOUSE_ENTER and MOUSE_LEAVE messages to
      update 'covered' flag properly.
      @return OK if event was processed successfully.
      @return NULL_POINTER in case of NULL pointer.
@return non-OK if error occurred.
  */
  virtual Outcome processMouseEvent(MouseEvent *event);

  /**
      Process key events. This function only checks
      that event pointer is not-NULL and returns OK.
      This function is used to handle key events.
      @return OK if event is not a NULL pointer.
      @return NULL_POINTER in case of NULL pointer.
  */
  virtual Outcome processKeyEvent(KeyEvent *event);

  /**
      Sets new position for sprite object.
      @param newPosition - new position for sprite.
  */
  void setPosition(const Vector3f &newPosition);

  /**
      Sets new position for sprite object.
      @param x - new X coordinate of the sprite.
      @param y - new Y coordinate of the sprite.
      @param z - new Z coordinate of the sprite.
  */
  void setPosition(float x, float y, float z);

  /**
      Changes X and Y components of the sprite's position.
      @param x - new X coordinate of the sprite.
      @param y - new Y coordinate of the sprite.
  */
  void setPosition(float x, float y);

  /**
      Sets sprite dimensions.
      @param newWidth - a new width value for this sprite.
      @param newHeight - a new height value for this sprite.
  */
  void setSize(float newWidth, float newHeight);

  /**
      Changes width of this sprite.
      @param newWidth - a new width for this sprite.
  */
  void setWidth(float newWidth);

  /**
      Changes height of this sprite.
      @param newHeight - a new height for this sprite.
  */
  void setHeight(float newHeight);

  /**
      Returns sprite position.
      @return Sprite current position.
  */
  Vector3f getPosition();

  /**
      Returns X-coordinate of this sprite.
      @return X-coordinate of this sprite.
  */
  float getX();

  /**
      Returns Y-coordinate of this sprite.
      @return Y-coordinate of this sprite.
  */
  float getY();

  /**
      Returns Z-coordinate of this sprite.
      @return Z-coordinate of this sprite.
  */
  float getZ();

  /**
      Returns width of this sprite.
      @return Sprite's width.
  */
  float getWidth();

  /**
      Returns height of this sprite.
      @return Sprite's height.
  */
  float getHeight();

  /**
      Sets alpha test option for this sprite. Use this state to avoid rendering
      transparent pixels.
      @param newAlphaTestState - Alpha test state for the rendering.
  */
  virtual void setAlphaTestState(AlphaTestState newAlphaTestState) {}

  /**
      Sets blend state which should be applied before
      rendering.
      @param newBlendState - pointer to a blend state or
      NULL if there is no need in blending. NULL is default
      value for any sprite.
  */
  virtual void setBlendState(BlendState newBlendState) {}

  /**
          Checks if component is covered by mouse.
          @return 'true' if mouse is above this component and 'false' otherwise.
      */
  bool isCovered();
};

}

#endif // __VE_ABSTRACT_SPRITE_H__
