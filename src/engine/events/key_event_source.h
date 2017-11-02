// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_KEY_EVENTS_SOURCE_H__
#define __VE_KEY_EVENTS_SOURCE_H__

#include <vector>

#include "engine/types.h"
#include "engine/events/key_event.h"
#include "engine/events/key_listener.h"

namespace ve {

/**
    A base class for objects that can produce/transfer keyboard events.
    It is used to add to object ability to register KeyListener objects,
    clear list of KeyListener objects and send messages across of them.
*/
class KeyEventsSource {
private:
  /** List of registered KeyListeners */
  std::vector<KeyListener*> keyListener;

public:
  /**
      Adds KeyListener object to object's 'mail-list'.
      @param newListener - a new message listener to register.
@return OK if listener was successfully added.
@return NULL_POINTER if NULL pointer was passed.
@return ERROR if listener already in the list of subscribers.
  */
  Outcome addKeyListener(KeyListener *newListener);

  /**
    Unsubscribe given KeyListener object.
    @return listener - KeyListener to unsubscribe.
  */
  void removeKeyListener(KeyListener *listener);

  /**
      Clears list of message listeners.
  */
  void clearKeyListeners();

  /**
      Calls KeyListener::processKeyEvent() function for every listener
      from list of registered listeners and pass them event parameter.
      @param keyEvent - event that should be passed for processing to
      all registered KeyListeners.
      @return OK if every KeyListener returns OK status after processing.
      @return not-OK status if some of the registered objects produces non-OK
      result code. It is the code that would be returned by this function.
  */
  Outcome sendKeyEvent(KeyEvent *keyEvent);
};

}

#endif // __VE_KEY_EVENTS_SOURCE_H__
