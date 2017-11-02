// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_KEY_EVENT_H__
#define __VE_KEY_EVENT_H__

#include "engine/events/system_event.h"

namespace ve {

/**
    It is a keyboard event class. This kind of events is initially produced
    by WindowSystem class that handles mouse and keyboard messages.
    Contains Unicode code of pressed or releaed button.
    It holds following messages:
    <ul>
    <li>KEY_PRESS - This message is generated when keyboard button pressed. </li>
    <li>KEY_RELEASE - This message is generated when keyboard button released. </li>
    </ul>
*/
class KeyEvent : public SystemEvent {
private:
  /** Key code of pressed/released button */
  int keyCode;

public:
  /**
      KeyEvent constructor that specifies only message type.
      @param type - key event type. Must be one of the following:
      KEY_PRESS, KEY_RELEASE.
  */
  KeyEvent(SystemEventType type);

  /**
      KeyEvent constructor that specifies both message type and key code.
      @param type - key event type. Must be one of the following:
      KEY_PRESS, KEY_RELEASE.
      @param theKeyCode - Unicode code of key which was pressed.
  */
  KeyEvent(SystemEventType type, int theKeyCode);

  /**
      Returns key code for this message.
      @return key code.
  */
  int getKeyCode();

  /**
      Sets key code for this message.
      @param newKeyCode - key code which will be set.
  */
  void setKeyCode(int newKeyCode);
};

}

#endif // __VE_KEY_EVENT_H__
