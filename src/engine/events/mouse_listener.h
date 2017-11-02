// Copyright (c) 2017 The Smart Authors.
// All rights reserved.
#ifndef __VE_MOUSE_LISTENER_H__
#define __VE_MOUSE_LISTENER_H__

#include "engine/common.h"
#include "engine/math/vector3f.h"
#include "engine/events/mouse_event.h"

namespace ve {

/**
    MouseListener is an interface for handling MouseEvents.
    It means that if some class wants to handle mouse events
    it should be based on this class to implement processMouseEvent function.
    Then it should be registered via MouseEventSource::registerMouseListener()
    function to get events from this source.
*/
class MouseListener {
public:
  /**
      Callback functions that will be invoked when a new MouseEvent
      occurred.
      @return It should return OK if event was successfully processed.
      @return non-OK result if some error occurred.
  */
  virtual Outcome processMouseEvent(MouseEvent *event) = 0;
};

}

#endif // __VE_MOUSE_LISTENER_H__
