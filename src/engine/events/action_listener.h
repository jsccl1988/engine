// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_ACTION_LISTENER_H__
#define __VE_ACTION_LISTENER_H__

#include "engine/common.h"
#include "engine/events/action_event.h"

namespace ve {

/**
    ActionListener is an interface for handling ActionEvents.
    It means that if some class wants to handle, for example,
    button messages it should be based on this class to
    implement processActionEvent function.
    Then it should be registered via ActionEventSource::registerActionListener()
    function to get events from this source.
*/
class ActionListener {
public:

  /**
      Callback functions which will be invoked when a new ActionEvent
      occurred.
      @return It should return OK if event was successfully processed.
      @return non-OK result if some error occurred.
  */
  virtual Outcome processActionEvent(ActionEvent *event) = 0;
};

}

#endif // __VE_ACTION_LISTENER_H__
