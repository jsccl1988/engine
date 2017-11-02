// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_WINDOW_EVENT_H__
#define __VE_WINDOW_EVENT_H__

#include "engine/events/system_event.h"

namespace ve {

/**
    It is a kind of events that are produced by WindowSystem class to
    notify about changes in windows size or that window are closing.
    Contains width and height of the window. Their values are applicable
    only for WINDOW_RESIZE message.

    This class holds following messages:
    <ul>
    <li>WINDOW_RESIZE - It is generated when window gets new size. </li>
    <li>WINDOW_CLOSE - It is generated before closing to inform that
    allocated resources should be disposed. </li>
    </ul>
*/
class WindowEvent : public SystemEvent {
private:
  /** Window width */
  int width;
  /** Window height */
  int height;

public:
  /**
      %WindowEvent constructor.
      @param type - message type. Must be one of the following:
      WINDOW_RESIZE, WINDOW_CLOSE.
  */
  WindowEvent(SystemEventType type);

  /**
      %WindowEvent constructor for WINDOW_RESIZE event.
      @param type - must be WINDOW_RESIZE.
      @param theWidth - new width of the window.
      @param theHeight - new height if the window.
  */
  WindowEvent(SystemEventType type, int theWidth, int theHeight);

  /**
      Return window's width.
      @return New width of the window.
  */
  int getWidth();

  /**
      Sets 'width' parameter of the message.
      It is used only in WINDOW_RESIZE messages.
      @param newWidth - New value of 'width' paramter to set.
  */
  void setWidth(int newWidth);

  /**
      Return window's height.
      @return New height of the window.
  */
  int getHeight();

  /**
      Sets 'height' parameter of the message.
      It is used only in WINDOW_RESIZE messages.
      @param newHeight - New value of 'height' paramter to set.
  */
  void setHeight(int newHeight);
};

}

#endif // __VE_WINDOW_EVENT_H__
