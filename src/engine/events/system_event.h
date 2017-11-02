// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_SYSTEM_EVENT_H__
#define __VE_SYSTEM_EVENT_H__

/** @file eeSystemEvent.h */

namespace ve {

/**
    Enumeration for all event types.
*/
enum SystemEventType {
  /* Mouse events */
  MOUSE_MOTION,
  MOUSE_PRESS,
  MOUSE_RELEASE,
  MOUSE_ENTER,
  MOUSE_LEAVE,

  /* Key events */
  KEY_PRESS,
  KEY_RELEASE,

  /* Window events */
  WINDOW_CLOSE,
  WINDOW_RESIZE,

  /* Action events */
  BUTTON_PRESS,
  BUTTON_RELEASE
};

/**
    It is the base class for all events inside
    <b>VR Engine</b> library. It contains only event
    type that is available through getType() function.

    To access data specific to a particular event a pointer to this
    class should be casted to pointer to an appropriate event class:

    MouseEvent class holds:
    <ul>
    <li>MOUSE_MOTION</li>
    <li>MOUSE_PRESS</li>
    <li>MOUSE_RELEASE</li>
    <li>MOUSE_ENTER</li>
    <li>MOUSE_LEAVE</li>
    </ul>

    KeyEvent class holds:
    <ul>
    <li>KEY_PRESS</li>
    <li>KEY_RELEASE</li>
    </ul>

    WindowEvent class holds:
    <ul>
    <li>WINDOW_CLOSE</li>
    <li>WINDOW_RESIZE</li>
    </ul>

    ActionEvent class holds:
    <ul>
    <li>BUTTON_PRESS</li>
    <li>BUTTON_RELEASE</li>
    </ul>
*/
class SystemEvent {
protected:
  /** Event type */
  SystemEventType type;

public:
  /**
      %SystemEvent constructor.
  */
  SystemEvent();

  /**
      %SystemEvent destructor.
  */

  virtual ~SystemEvent();

  /**
      Returns message type.
      @return message type.
  */
  SystemEventType getType();
};

}

#endif // __VE_SYSTEM_EVENT_H__
