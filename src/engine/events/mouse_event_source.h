// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_MOUSE_EVENTS_SOURCE_H__
#define __VE_MOUSE_EVENTS_SOURCE_H__

#include <vector>

#include "engine/types.h"
#include "engine/sprites/abstract_sprite.h"
#include "engine/events/mouse_event.h"
#include "engine/events/mouse_listener.h"

namespace ve {

/**
    Base class for objects that can produce/transfer mouse events.
    It is used to add to object ability to register MouseListener objects,
    clear list of MouseListener objects and send messages across of them.

    <b>Note:</b>Only objects which are derived from AbstractSprite classes
    could be set as MouseListener, because to handle mouse events they should
    have at least area where they are defined to correct handling of all the messages.
*/
class MouseEventsSource {
private:
  /** List of registered AbstractSprites */
  std::vector<AbstractSprite*> mouseListener;

public:
  /**
      Adds AbstractSprite object to object's 'mail-list'
      @param newListener - new message listener to register.
@return OK if listener was successfully added.
@return NULL_POINTER if NULL pointer was passed.
@return ERROR if listener already in the list of subscribers.
  */
  Outcome addMouseListener(AbstractSprite *newListener);

  /**
    Unsubscribe given sprite object.
    @return listener - AbstractSprite to unsubscribe.
  */
  void removeMouseListener(AbstractSprite *listener);

  /**
          Clears list of message listeners.
      */
  void clearMouseListeners();

  /**
      Calls MouseListener::processMouseEvent() function for every sprite
      from list of registered listeners and pass them event parameter.
      @param mouseEvent - event which should be passed for processing to
      all registered sprites.
      @return OK if every sprite returns OK status after processing.
      @return not-OK status if some of the registered objects produces non-OK
      result code. It is the code that would be returned by this function.
  */
  Outcome sendMouseEvent(MouseEvent *mouseEvent);

  /**
      Get registered sprite by its index.
      @param index of registered sprite.
      @return pointer to an abstract sprite if index is correct.
      @return NULL if index is out of bounds.
  */
  AbstractSprite* getListener(uint index);

  /**
      Returns number of registered sprites.
      @return number of registered sprites.
  */
  uint count();
};

}

#endif // __VE_MOUSE_EVENTS_SOURCE_H__
