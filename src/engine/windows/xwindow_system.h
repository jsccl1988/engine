// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifdef VE_LINUX

#ifndef __VE_X_WINDOW_SYSTEM_H__
#define __VE_X_WINDOW_SYSTEM_H__

#include <vector>

#include <X11/X.h>
#include <X11/keysym.h>

#include "common.h"
#include "windows/window_system.h"
#include "fonts/font.h"

namespace ve {

/**
    WindowSystem class implementation for XSystem.
*/
class XWindowSystem : public WindowSystem {
private:

  /**
      Structure that contains system specific data associated with
      Window class pointer.
  */
  struct WindowInfo {
    Window* window;
    XID id;
  };

  Display *dpy;
  std::vector<WindowInfo> winInfo;
  Atom wnd_DestroyAtom;
  Atom wnd_Protocols;
  Atom wnd_Name;

  /**
      Returns XID by Window class.
  */
  XID getWindowXID(Window *window);

  /**
      Registers (Window*, XID) pair.
  */
  Outcome registerWindow(Window* window, XID id);

public:
  /**
      Default constructor. Creates memory manager.
  */
  XWindowSystem();

  /**
      Checks if OpenGL is supported on this system.
      @return 'true' is supported.
      @return 'false' if not supported.
  */
  bool isOpenGLSupported();

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
  virtual Window* createWindow(const std::wstring & windowName, int x, int y,
    int width, int height, bool fullScreen = false);

  /**
      Creates font registered in the window system.
      @param engine - Engine object that will be used to render font symbols.
      @param desc - Font description.
      @return Font object if creation succeeded.
      @return NULL if error occurred or font with specified description is
      not supported in this system.
  */
  virtual ve::Font* createFont(Engine *engine, FontDescriptor *desc);

  /**
    Returns std::vector structure filled within ScreenMode structures that
    define available screen resolution.
    @return List of pairs that define available screen resolution.
  */
  virtual std::vector<ScreenMode> getAvailableResolutions();

  /**
      Computes length in pixels for given Font and ASCII string.
      @param font - Font that is used to render string.
      @param str - ASCII string to compute length in pixels.
      @return Length of rendered string (in pixels).
      @return NULL_POINTER if font is NULL or if it was not created
      bu this WindowSystem.
  */
  virtual unsigned int getTextWidth(ve::Font *font, std::string str);

  /**
      Computes length in pixels for given Font and wide string.
      @param font - Font that is used to render string.
      @param wstr - wide string to compute length in pixels.
      @return Length of rendered string (in pixels).
      @return NULL_POINTER if font is NULL or if it was not created
      bu this WindowSystem.
  */
  virtual unsigned int getTextWidth(ve::Font *font, std::wstring wstr);

  /**
      Dispose all resources connected with Font object.
      This method does not do 'delete' operation for the given pointer.
      @param font - Font that should be disposed.
      @return OK if operation succeeded.
      @return NULL_POINTER if font is NULL pointer or was not created
      by this WindowSystem.
  */
  virtual Outcome freeFont(Font *font);

  /**
      Dispose all resources connected with Window object.
      This method does not do 'delete' operation for the given pointer.
      @param window - Window that should be disposed.
      @return OK if operation succeeded.
      @return NULL_POINTER if font is NULL pointer or was not created
      by this WindowSystem.
  */
  virtual Outcome freeWindow(Window *window);

  /**
      Swaps front and back buffers for a given window.
      @param window - Window to swap its buffers.
      @return OK if operation succeeded.
      @return NULL_POINTER if window is NULL pointer.
  */
  virtual Outcome swap(Window *window);

  /**
      Writes current screen resolution in width and height arguments.
      @return OK if width and height parameters were written correctly.
      @return non-OK if engine error occurred.
  */
  virtual Outcome getScreenResolution(int &width, int &height);

  /**
    Sets current screen resolution to a specified mode.
    @param mode - New screen resolution to set.
    @return OK if resolution was changed.
    @return non-OK if error occurred.
  */
  virtual Outcome setScreenResolution(ScreenMode mode);

  /**
      Returns the next window system event if there is any. If there are
      no events function blocks waits till next event happens.
@param window - Message queue of this window will be checked.
      @return Window system event.
      @return NULL is event is not supported.
  */
  virtual SystemEvent* getNextEvent(Window *window);

  /**
      Checks if there is an available event in the queue of window events.
@param window - Event queue of this window will be checked.
      @return 'true' if there is an event for the window from the window system.
@return 'false' if there are no available events for the window.
  */
  virtual bool hasAvailableEvent(Window *window);

  /**
      Sets window caption.
      @param window - Window to set caption for.
      @param newCaption - New caption string for the given window.
      @return OK if operation succeeded.
      @return NULL_POINTER if window pointer is NULL.
  */
  virtual Outcome setCaption(Window* window, std::wstring &newCaption);

  /**
      Sets window position (left-upper corner).
      @param window - Window to set position for.
      @param newX - New X coordinate for the given window.
      @param newY - New X coordinate for the given window.
      @return OK if operation succeeded.
      @return NULL_POINTER if window pointer is NULL.
  */
  virtual Outcome setPosition(Window* window, int newX, int newY);

  /**
      Sets window mode (windowed, full screen).
      @param window - Window to set mode for.
      @param newMode - new mode for the given window.
      @return OK if operation succeeded.
      @return NULL_POINTER if window pointer is NULL.
  */
  virtual Outcome setMode(Window *window, WindowMode newMode);

  /**
      Sets window state (shown, hidden, iconified).
      @param window - Window to set mode for.
      @param newState - new state for the given window.
      @return OK if operation succeeded.
      @return NULL_POINTER if window pointer is NULL.
  */
  virtual Outcome setState(Window *window, WindowState newState);

  /**
      Changes width of the given window.
      @param window - Window to change width for.
      @param newWidth - new width for the given window.
      @return OK if operation succeeded.
      @return NULL_POINTER if window pointer is NULL.
  */
  virtual Outcome setWidth(Window *window, int newWidth);

  /**
      Changes height of the given window.
      @param window - Window to change height for.
      @param newHeight - new height for the given window.
      @return OK if operation succeeded.
      @return NULL_POINTER if window pointer is NULL.
  */
  virtual Outcome setHeight(Window *window, int newHeight);

  /**
      Changes width and height for the given window.
      @param window - Window to change width and height for.
      @param newWidth - new width for the given window.
      @param newHeight - new height for the given window.
      @return OK if operation succeeded.
      @return NULL_POINTER if window pointer is NULL.
  */
  virtual Outcome setSize(Window *window, int newWidth, int newHeight);

  /**
      Shows window.
      @param window - Window to show on the screen.
      @return OK if operation succeeded.
      @return NULL_POINTER if window pointer is NULL.
  */
  virtual Outcome show(Window *window);

  /**
    Returns viewport of the window. Viewport contains whole area that is available
    for rendering.
    @return ViewportState object that contains bounds of client area.
  */
  virtual ViewportState getClientViewport(Window *window);
};

}

#endif // __VE_X_WINDOW_SYSTEM_H__

#endif // VE_LINUX
