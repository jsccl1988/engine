// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_KEY_LISTENER_H__
#define __VE_KEY_LISTENER_H__

#include "engine/common.h"
#include "engine/events/key_event.h"

namespace ve {

/**
    KeyListener is an interface for handling KeyEvents.
    It means that if some class wants to handle keyboards messages
    it should be based on this class to implement processKeyEvent() function.
    Then it should be registered via KeyEventSource::registerKeyListener()
    function to get events from this source.
*/
class KeyListener {
public:
  /**
      Callback functions that will be invoked when new KeyEvent
      occurred.
      @return It should return OK if event was successfully processed.
      @return non-OK result if some error occurred.
  */
  virtual Outcome processKeyEvent(KeyEvent *event) = 0;
};

}

#endif // __VE_KEY_LISTENER_H__
