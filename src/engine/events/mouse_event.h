// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_MOUSE_EVENT_H__
#define __VE_MOUSE_EVENT_H__

#include "engine/events/system_event.h"

/** @file eeMouseEvent.h */

namespace ve {

/**
    Enumeration which defines mouse button constants.
*/
enum MouseButton {
  LEFT_BUTTON = 1,
  MIDDLE_BUTTON = 2,
  RIGHT_BUTTON = 3,
  WHEEL_UP = 4,
  WHEEL_DOWN = 5
};

/**
    It is a mouse event class. This kind of events is initially produced
    by WindowSystem class that handles mouse and keyboard messages.

    It holds following messages:
    <ul>
    <li>MOUSE_PRESS - Generated when mouse button pressed. </li>
    <li>MOUSE_RELEASE - Generated when mouse button released. </li>
    <li>MOUSE_MOTION - Generated during mouse movements. </li>
    <li>MOUSE_ENTER - Not a native message. Used to inform interface component
    that mouse enters to its window region.</li>
    <li>MOUSE_LEAVE - Not a native message. Used to inform interface component
    that mouse leaves its window region.</li>
    </ul>

    It contains followings data:
    <ul>
    <li> Mouse button associated with this event. ('button' variable). </li>
    <li> Absolute mouse coordinates (pair of 'mouseX', 'mouseY' variables). </li>
    <li> Component-relative mouse coordinates (pair of 'x', 'y' variables) </li>
    </ul>

    Relative coordinates is very useful for interface components, because using them
    they known relative mouse position and can decides, for example, if mouse pointer
    inside their region or not. Recalculation of relative coordinates is done
    implicitly inside MouseEventSource class during message transmition.
*/
class MouseEvent : public SystemEvent {
private:
  MouseButton button;
  int x;
  int y;
  int mouseX;
  int mouseY;

public:
  /**
      %MouseEvent construstor.
      @param type - type of the message. Should be one of the
      following: MOUSE_PRESS, MOUSE_RELEASE, MOUSE_MOTION, MOUSE_ENTER, MOUSE_LEAVE.
  */
  MouseEvent(SystemEventType type);

  /**
      %MouseEvent constructor with a lot of parameters.
      @param type - type of the message. Should be one of the
      following: MOUSE_PRESS, MOUSE_RELEASE, MOUSE_MOTION, MOUSE_ENTER, MOUSE_LEAVE.
      @param button - mouse button that is associated with this message.
      Applicable only for MOUSE_PRESS and MOUSE_RELEASE events.
      @param x - relative X-coordinate of mouse pointer.
      @param y - relative Y-coordinate of mouse pointer.
      @param mouseX - absolute X-coordiante of mouse pointer.
      @param mouseY - absolute Y-coordiante of mouse pointer.
  */
  MouseEvent(SystemEventType type, MouseButton button, int x, int y, int mouseX, int mouseY);

  /**
      Returns relative X-coordinate of mouse pointer.
      @return relative X-coordinate of mouse pointer.
  */
  int getX();

  /**
      Returns relative Y-coordinate of mouse pointer.
      @return relative Y-coordinate of mouse pointer.
  */
  int getY();

  /**
      Returns absolute X-coordinate of mouse pointer.
      @return absolute X-coordinate of mouse pointer.
  */
  int getMouseX();

  /**
      Returns absolute Y-coordinate of mouse pointer.
      @return absolute Y-coordinate of mouse pointer.
  */
  int getMouseY();

  /**
      Returns button associated with this message.
      This function is applicable only for MOUSE_PRESS/MOUSE_RELEASE events.
      @return button pressed/release
  */
  MouseButton getButton();

  /**
      Sets relative X-coordinate of mouse pointer.
      @return newX - new X coordiante.
  */
  void setX(int newX);

  /**
      Sets relative Y-coordinate of mouse pointer.
      @return newY - new Y coordiante.
  */
  void setY(int newY);

  /**
      Sets mouse button associated with this message.
      @return newButton - new value for 'button' member.
  */
  void setButton(MouseButton newButton);
};

}

#endif // __VE_MOUSE_EVENT_H__
