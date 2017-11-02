// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_INTERFACE_CONTAINER_H__
#define __VE_INTERFACE_CONTAINER_H__

#include <vector>

#include "engine/sprites/abstract_sprite.h"
#include "engine/ui/ui_control.h"
#include "engine/events/mouse_event_source.h"
#include "engine/events/key_event_source.h"

namespace ve {

/**
    Vector-based class-container for interface components.
*/
class UIContainer : public UIControl, public MouseEventsSource, public KeyEventsSource {
private:
  std::vector<AbstractSprite*> objects;

public:
  /**
      UIContainer constructor.
      @param parent - UI object that will be the owner of this container.
  */
  UIContainer(UIContainer *parent);

  /**
      Adds interface control to this container.
      @param newControl - Control to add to this container.
      @return OK if pointer is not NULL.
@return NULL_POINTER if pointer is NULL.
  */
  virtual Outcome addObject(AbstractSprite *newControl);

  /**
    Removes object from this container.
    @param object - Object to remove.
  */
  virtual void removeObject(AbstractSprite *object);

  /**
      Returns control by its index.
      @return Pointer to interface control or NULL
      if index is out of bounds.
  */
  virtual AbstractSprite* getObject(uint index);

  /**
      Returns count of interface components in this container.
      @return Count of interface components.
  */
  virtual uint getObjectsCount();

  /**
      Removes all interface components from this container.
      @return OK everytime.
  */
  virtual Outcome clearObjects();

  /**
      Handles MOUSE_MOVE events to produce MOUSE_ENTER and MOUSE_LEAVE message to
all sub-components. Sends the given event across all the objects.
      @return OK if event was processed successfully.
      @return NULL_POINTER if NULL pointer was passed as a pointer.
@return non-OK if error occurred.
  */
  virtual Outcome processMouseEvent(MouseEvent *event);

  /**
Sends the given key event across all the object of this container.
      @return OK if event was processed successfully.
      @return NULL_POINTER if NULL pointer was passed as a pointer.
@return non-OK if error occurred.
  */
  virtual Outcome processKeyEvent(KeyEvent *event);
};

}

#endif // __VE_INTERFACE_CONTAINER_H__
