// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_WINDOW_SYSTEM_H__
#define __VE_WINDOW_SYSTEM_H__

#include <string>
#include "engine/common.h"
#include "engine/events/system_event.h"
#include "engine/events/mouse_event_source.h"
#include "engine/events/key_event_source.h"
#include "engine/windows/window.h"
#include "engine/fonts/font.h"
#include "engine/fonts/font_descriptor.h"
#include "engine/tools/memory_manager.h"
#include "engine/states/viewport_state.h"

namespace ve {

class Engine;

/**
  Defines screen mode that may be set at the current display
*/
struct ScreenMode {
  uint width;
  uint height;

  ScreenMode() {
    width = height = 0;
  }

  ScreenMode(uint theWidth, uint theHeight) {
    width = theWidth;
    height = theHeight;
  }
};

/**
    Abstract class to work with windows system. It allows to create windows and change
    their properties like position, size, caption, etc. It is a source of
    system, keyboard and mouse events. %WindowSystem class is also used to
    create fonts registered in the system.
*/
class WindowSystem : public MouseEventsSource, public KeyEventsSource {
public:
  /**
      Default constructor. Creates memory manager.
  */
  WindowSystem();

  /**
      Destructor. All the windows and fonts that were not disposed manually
      will be destroyed here in memory manager destructor.
  */
  virtual ~WindowSystem();

  /**
      Creates window.
      @param windowName - At this moment, this parameter is not used.
      @param x - X position of the created window.
      @param y - Y position of the created window.
      @param width - Width of the created window.
      @param height - Height of the created window.
      @param fullScreen - If this flag is set to true then full screen window will be created
and width, height parameters will be ignored.
      @return Created window if operation succeeded.
      @return NULL if error occurred.
  */
  virtual Window* createWindow(const std::wstring &windowName, int x, int y,
    int width, int height, bool fullScreen = false) = 0;

  /**
      Creates font registered in the window system.
      @param engine - Engine object that will be used to render font symbols.
      @param desc - Font description.
      @return Font object if creation succeeded.
      @return NULL if error occurred or font with specified description is
      not supported in this system.
  */
  virtual ve::Font* createFont(Engine *engine, FontDescriptor *desc) = 0;

  /**
    Returns std::vector structure filled within ScreenMode structures that
    define available screen resolution.
    @return List of pairs that define available screen resolution.
  */
  virtual std::vector<ScreenMode> getAvailableResolutions() = 0;

  /**
      Computes length in pixels for given Font and ASCII string.
      @param font - Font that is used to render string.
      @param str - ASCII string to compute length in pixels.
      @return Length of rendered string (in pixels).
      @return NULL_POINTER if font is NULL or if it was not created
      bu this WindowSystem.
  */
  virtual uint getTextWidth(ve::Font *font, std::string str) = 0;

  /**
      Computes length in pixels for given Font and wide string.
      @param font - Font that is used to render string.
      @param wstr - wide string to compute length in pixels.
      @return Length of rendered string (in pixels).
      @return NULL_POINTER if font is NULL or if it was not created
      bu this WindowSystem.
  */
  virtual uint getTextWidth(ve::Font *font, std::wstring wstr) = 0;

  /**
      Dispose all resources connected with Font object.
      This method does not do 'delete' operation for the given pointer.
      @param font - Font that should be disposed.
      @return OK if operation succeeded.
      @return NULL_POINTER if font is NULL pointer or was not created
      by this WindowSystem.
  */
  virtual Outcome freeFont(Font *font) = 0;

  /**
      Dispose all resources connected with Window object.
      This method does not do 'delete' operation for the given pointer.
      @param window - Window that should be disposed.
      @return OK if operation succeeded.
      @return NULL_POINTER if font is NULL pointer or was not created
      by this WindowSystem.
  */
  virtual Outcome freeWindow(Window *window) = 0;

  /**
      Swaps front and back buffers for a given window.
      @param window - Window to swap its buffers.
      @return OK if operation succeeded.
      @return NULL_POINTER if window is NULL pointer.
  */
  virtual Outcome swap(Window *window) = 0;

  /**
      Writes current screen resolution in width and height arguments.
      @return OK if width and height parameters were written correctly.
      @return non-OK if engine error occurred.
  */
  virtual Outcome getScreenResolution(int &width, int &height) = 0;

  /**
    Sets current screen resolution to a specified mode.
    @param mode - New screen resolution to set.
    @return OK if resolution was changed.
    @return non-OK if error occurred.
  */
  virtual Outcome setScreenResolution(ScreenMode mode) = 0;

  /**
      Returns the next window system event if there is any. If there are
      no events function blocks waits till next event happens.
@param window - Message queue of this window will be checked.
      @return Window system event.
      @return NULL is event is not supported.
  */
  virtual SystemEvent* getNextEvent(Window *window) = 0;

  /**
      Checks if there is an available event in the queue of window events.
@param window - Event queue of this window will be checked.
      @return 'true' if there is an event for the window from the window system.
@return 'false' if there are no available events for the window.
  */
  virtual bool hasAvailableEvent(Window *window) = 0;

  /**
      Sets window caption.
      @param window - Window to set caption for.
      @param newCaption - New caption string for the given window.
      @return OK if operation succeeded.
      @return NULL_POINTER if window pointer is NULL.
  */
  virtual Outcome setCaption(Window* window, std::wstring &newCaption) = 0;

  /**
      Sets window position (left-upper corner).
      @param window - Window to set position for.
      @param newX - New X coordinate for the given window.
      @param newY - New X coordinate for the given window.
      @return OK if operation succeeded.
      @return NULL_POINTER if window pointer is NULL.
  */
  virtual Outcome setPosition(Window* window, int newX, int newY) = 0;

  /**
      Sets window mode (windowed, full screen).
      @param window - Window to set mode for.
      @param newMode - new mode for the given window.
      @return OK if operation succeeded.
      @return NULL_POINTER if window pointer is NULL.
  */
  virtual Outcome setMode(Window *window, WindowMode newMode) = 0;

  /**
      Sets window state (shown, hidden, iconified).
      @param window - Window to set mode for.
      @param newState - new state for the given window.
      @return OK if operation succeeded.
      @return NULL_POINTER if window pointer is NULL.
  */
  virtual Outcome setState(Window *window, WindowState newState) = 0;

  /**
      Changes width of the given window.
      @param window - Window to change width for.
      @param newWidth - new width for the given window.
      @return OK if operation succeeded.
      @return NULL_POINTER if window pointer is NULL.
  */
  virtual Outcome setWidth(Window *window, int newWidth) = 0;

  /**
      Changes height of the given window.
      @param window - Window to change height for.
      @param newHeight - new height for the given window.
      @return OK if operation succeeded.
      @return NULL_POINTER if window pointer is NULL.
  */
  virtual Outcome setHeight(Window *window, int newHeight) = 0;

  /**
      Changes width and height for the given window.
      @param window - Window to change width and height for.
      @param newWidth - new width for the given window.
      @param newHeight - new height for the given window.
      @return OK if operation succeeded.
      @return NULL_POINTER if window pointer is NULL.
  */
  virtual Outcome setSize(Window *window, int newWidth, int newHeight) = 0;

  /**
      Shows window.
      @param window - Window to show on the screen.
      @return OK if operation succeeded.
      @return NULL_POINTER if window pointer is NULL.
  */
  virtual Outcome show(Window *window) = 0;

  /**
    Returns viewport of the window. Viewport contains whole area that is available
    for rendering.
    @return ViewportState object that contains bounds of client area.
  */
  virtual ViewportState getClientViewport(Window *window) = 0;


};

}

#endif // __VE_WINDOW_SYSTEM_H__
