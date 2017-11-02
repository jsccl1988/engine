// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_ACTION_EVENTS_SOURCE_H__
#define __VE_ACTION_EVENTS_SOURCE_H__

#include <vector>

#include "engine/types.h"
#include "engine/events/action_listener.h"
#include "engine/events/action_event.h"

namespace ve {

/**
    Base class for objects that can produce/transfer action events.
    It is used to add to an object ability to register ActionListener objects,
    clear list of ActionListener objects and send messages across them.
*/
class ActionEventsSource {
private:
  /** List of registered ActionListeners */
  std::vector<ActionListener*> actionListener;

public:
  /**
      Adds ActionListener object to object's 'mail-list'
      @param newListener - new message listener to register.
  */
  void addActionListener(ActionListener *newListener);

  /**
      Clears list of message listeners.
  */
  void clearActionListeners();

  /**
      Calls ActionListener::processActionEvent() function for every listener
      from list of registered listeners and pass them event parameter.
      @param event - event which should be passed for processing to
      all registered ActionListeners.
      @return OK if every ActionListener returns OK status after processing.
      @return not-OK status if some of the registered objects produces non-OK
      result code. It is the code that would be returned by this function.
  */
  Outcome sendActionEvent(ActionEvent *event);
};

}

#endif // __VE_ACTION_EVENTS_SOURCE_H__
