// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_ACTION_EVENT_H__
#define __VE_ACTION_EVENT_H__

#include "engine/events/system_event.h"

namespace ve {

class UIControl;

/**
    It is a kind of events that are produced by Button objects.
    Contains pointer to control generated this event.
    It holds following messages:
    <ul>
    <li>BUTTON_PRESS - This message is generated when button is pressed. </li>
    <li>BUTTON_RELEASE - This message is generated when button is released. </li>
    </ul>
*/
class ActionEvent : public SystemEvent {
protected:
  /** Event type */
  SystemEventType type;

  /** Button */
  UIControl* sender;

public:
  /**
      ActionEvent constructor.
      @param type - event type. Can be one from the following:
      BUTTON_PRESS, BUTTON_RELEASE.
      @param sender - GUI control generated this event.
  */
  ActionEvent(SystemEventType type, UIControl* sender);

  /**
      ActionEvent destructor.
  */
  virtual ~ActionEvent();

  /**
      Returns pointer to GUI control generated this event.
      @return Pointer to GUI control.
  */
  UIControl* getSender();
};

}

#endif // __VE_ACTION_EVENT_H__
