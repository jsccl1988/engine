// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_WINDOW_H__
#define __VE_WINDOW_H__

#include <string>

#ifdef LINUX
#include <X11/X.h>
#include <X11/keysym.h>
#endif

#include "engine/types.h"
#include "engine/visible_object.h"
#include "engine/states/viewport_state.h"
#include "engine/events/system_event.h"

namespace ve {

class WindowSystem;

/* Window modes */
enum WindowMode {
  WM_WINDOW = 0,
  WM_FULLSCREEN = 1
};

/* Window states */
enum WindowState {
  WS_NONE = -1,
  WS_SHOWN = 0,
  WS_HIDDEN = 1,
  WS_ICONIFIED = 2
};

/**
    Platform-independent class to manage window in window system.

    <b>Note:</b> Window objects must be created only through WindowSystem::createWindow() function.
*/
class Window {
private:
  /** Window system that created this window object. */
  WindowSystem *engine;

  /** Variables for FPS computing. */
  time_t lastMoment;
  int framesCount;
  float fps;

public:
  /**
      Constructor.
      <b>Note:</b> Window objects must be created only through
      WindowSystem::createWindow() function.
      @param windowSystem - WindowSystem object that creates this window.
  */
  Window(WindowSystem *windowSystem);

  /**
      Destructor. Frees allocated resource by calling WindowSystem::freeWindow() function.
  */
  virtual ~Window();

  /**
      Shows this window on a screen.
      @return OK if operation succeeded.
      @return non-OK if window system error occurred.
  */
  virtual Outcome show();

  /**
      Swaps back & front buffers for this window.
      Increases count of frames that is used to compute FPS rate.
      @return OK if operation succeeded.
      @return non-OK if window system error occurred.
  */
  virtual Outcome swap();

  /**
      Returns FPS which is computed in swap() function.
      @return FPS rate.
  */
  float getFPS();

  /**
      Sets window caption.
      @param newCaption - caption string to set.
      @return OK if operation succeeded.
      @return non-OK if window system error occurred.
  */
  virtual Outcome setCaption(std::wstring &newCaption);

  /**
      Sets window position on the screen (left-upper corner position).
      @param newX - X position on the screen.
      @param newY - Y position on the screen.
      @return OK if operation succeeded.
      @return non-OK if window system error occurred.
  */
  virtual Outcome setPosition(double newX, double newY);

  /**
      Sets window mode.
      @param newMode - mode to set up for this window.
      @return OK if operation succeeded.
      @return non-OK if window system error occurred.
  */
  virtual Outcome setWindowMode(const WindowMode newMode);

  /**
      Sets window state.
      @param newState - state to set up for this window.
      @return OK if operation succeeded.
      @return non-OK if window system error occurred.
  */
  virtual Outcome setWindowState(const WindowState newState);

  /**
      Sets window width.
      @param newWidth - width to set up for this window.
      @return OK if operation succeeded.
      @return non-OK if window system error occurred.
  */
  virtual Outcome setWidth(double newWidth);

  /**
      Sets window height.
      @param newHeight - height to set up for this window.
      @return OK if operation succeeded.
      @return non-OK if window system error occurred.
  */
  virtual Outcome setHeight(double newHeight);

  /**
      Sets window width and height.
      @param newWidth - width to set up for this window.
      @param newHeight - height to set up for this window.
      @return OK if operation succeeded.
      @return non-OK if window system error occurred.
  */
  virtual Outcome setSize(double newWidth, double newHeight);

  /**
      Returns window width.
      @return Window width.
  */
  virtual int getWidth();

  /**
      Returns window height.
      @return Window height.
  */
  virtual int getHeight();

  /**
    Returns viewport of the window. Viewport contains whole area that is available
    for rendering.
    @return ViewportState object that contains bounds of client area.
  */
  virtual ViewportState getClientViewport();

  /**
      Returns the next window system event if there is any in the queue. If there are
      no events function blocks waits till next event happens.
      @return Window system event.
      @return NULL if event is not supported.
  */
  virtual SystemEvent* getNextEvent();

  /**
      Checks if there is an available event for this window.
      @return 'true' if there is an event for this window from the window system.
@return 'false' if there are no available events for this window.
  */
  virtual bool hasAvailableEvent();
};

}

#endif // __VE_WINDOW_H__
