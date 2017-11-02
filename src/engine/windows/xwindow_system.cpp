// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifdef VE_LINUX

#include "engine/common.h"

#include <X11/X.h>
#include <X11/keysym.h>
#include <X11/extensions/xf86vmode.h>

#include "windows/xwindow_system.h"
#include "engine/fonts/font.h"
#include "engine/fonts/x_font.h"
#include "engine/events/key_event.h"
#include "engine/events/mouse_event.h"
#include "engine/events/window_event.h"
#include "engine/tools/string_tool.h"
#include "engine/tools/keys_codec.h"

namespace ve {

XWindowSystem::XWindowSystem() {
  /* Open a connection to the X server */
  dpy = XOpenDisplay(NULL);
  LOG_IF(dpy == NULL, L"Could not open display");
}

bool XWindowSystem::isOpenGLSupported() {
  int dummy = 0;
  CHECK_POINTER_EX(dpy, false);

  return glXQueryExtension(dpy, &dummy, &dummy) != 0;
}

Outcome XWindowSystem::registerWindow(Window* window, XID id) {
  WindowInfo wi;

  wi.window = window;
  wi.id = id;

  winInfo.push_back(wi);
  return OK;
}

XID XWindowSystem::getWindowXID(Window *window) {
  CHECK_POINTER_EX(window, 0);

  uint len = winInfo.size();
  for (uint i = 0; i < len; i++) {
    if (winInfo[i].window == window) {
      return winInfo[i].id;
    }
  }

  return 0;
}

Window* XWindowSystem::createWindow(const std::wstring & windowName, int x, int y,
  int width, int height, bool fullScreen) {
  int dblBuf[] = { GLX_RGBA, GLX_DEPTH_SIZE, 16, GLX_DOUBLEBUFFER, None };
  XVisualInfo         *vi;
  Colormap             cmap;
  XSetWindowAttributes swa;
  GLXContext           cx;

  /* Make sure OpenGL's GLX extension supported */
  ERROR_IF(isOpenGLSupported() == false, L"X server has no OpenGL GLX extension", NULL);

  /* Find an OpenGL-capable RGB visual with depth buffer */
  vi = glXChooseVisual(dpy, DefaultScreen(dpy), dblBuf);
  ERROR_IF(vi == NULL, L"Unsupported depth buffer", NULL);
  ERROR_IF(vi->c_class != TrueColor, L"TrueColor visual required for this program", NULL);

  /* Create an OpenGL rendering context */
  cx = glXCreateContext(dpy, vi, NULL, GL_TRUE);
  ERROR_IF(cx == NULL, L"Could not create rendering context", NULL);

  /* Create an X window with the selected visual */

  /* create an X colormap since probably not using default visual */
  cmap = XCreateColormap(dpy, RootWindow(dpy, DefaultScreen(dpy)), vi->visual, AllocNone);
  swa.colormap = cmap;
  swa.border_pixel = 0;
  swa.background_pixel = 0;
  swa.event_mask = KeyPressMask | ExposureMask | ButtonPressMask | StructureNotifyMask | PointerMotionMask
    | KeyReleaseMask | ButtonReleaseMask;

  unsigned long mask = CWBorderPixel | CWColormap | CWEventMask;

  if (fullScreen) {
    swa.override_redirect = true;
    mask |= CWOverrideRedirect;
    getScreenResolution(width, height);
  }

  XID winId = XCreateWindow(dpy, RootWindow(dpy, DefaultScreen(dpy)), x, y,
    width, height, 0, vi->depth, InputOutput, vi->visual, mask, &swa);

  if (fullScreen) {
    XWarpPointer(dpy, None, winId, 0, 0, 0, 0, 0, 0);
    XMapRaised(dpy, winId);
    XGrabKeyboard(dpy, winId, True, GrabModeAsync, GrabModeAsync, CurrentTime);
    XGrabPointer(dpy, winId, True, ButtonPressMask, GrabModeAsync, GrabModeAsync, winId, None, CurrentTime);
  }

  XSizeHints sizehints;
  sizehints.x = x;
  sizehints.y = y;
  sizehints.width = width;
  sizehints.height = height;
  sizehints.flags = USSize | USPosition;
  XSetNormalHints(dpy, winId, &sizehints);
  XSetStandardProperties(dpy, winId, StringTool::WideToAscii(windowName).c_str(),
    StringTool::WideToAscii(windowName).c_str(), None, NULL, 0, &sizehints);

  /* Bind the rendering context to the window */
  XMapWindow(dpy, winId);
  glXMakeCurrent(dpy, winId, cx);

  XFree(vi);

  Window *window = new Window(this);
  ERROR_IF(registerWindow(window, winId) != OK, L"Failed to register window", NULL);

  /* Register destroy message */
  wnd_DestroyAtom = XInternAtom(dpy, "WM_DELETE_WINDOW", False);
  ERROR_IF(wnd_DestroyAtom == None, L"Atom is None", NULL);
  wnd_Protocols = XInternAtom(dpy, "WM_PROTOCOLS", False);
  ERROR_IF(wnd_Protocols == None, L"Atom is None", NULL);
  wnd_Name = XInternAtom(dpy, "XA_WM_NAME", False);
  ERROR_IF(wnd_Name == None, L"Atom is None", NULL);
  XSetWMProtocols(dpy, winId, &wnd_DestroyAtom, 1);

  REGISTER_POINTER(window);
  return window;
}

Font* XWindowSystem::createFont(Engine *engine, FontDescriptor *desc) {
  XFontStruct* font = XLoadQueryFont(dpy, StringTool::WideToAscii(desc->getFormatString()).c_str());

  if (font == NULL) {
    FAIL(L"XLoadQueryFont Failed", NULL);
    return NULL;
  }

  XFont* newXFont = new XFont(this, engine, font);
  CHECK_ALLOC_EX(newXFont, NULL);
  REGISTER_POINTER(newXFont);
  return newXFont;
}

std::vector<ScreenMode> XWindowSystem::getAvailableResolutions() {
  int count = 0;
  XF86VidModeModeInfo **modes = NULL;
  std::vector<ScreenMode> result;
  return result;

  // XF86VidModeGetAllModeLines(dpy, DefaultScreen(dpy), &count, &modes);
  for (int i = 0; i < count; i++) {
    Screen *screen = XScreenOfDisplay(dpy, i);
    result.push_back(ScreenMode(modes[i]->hdisplay, modes[i]->vdisplay));
  }

  XFree(modes);

  return result;
}

Outcome XWindowSystem::freeFont(Font *font) {
  CHECK_POINTER(font);
  XFont *xFont = dynamic_cast<XFont*>(font);
  ERROR_IF(font == NULL, L"Not an XFont class", ERROR);
  XUnloadFont(dpy, xFont->getInfo()->fid);
  return OK;
}

uint XWindowSystem::getTextWidth(ve::Font *font, std::string str) {
  CHECK_POINTER(font);
  XFont *xFont = dynamic_cast<XFont*>(font);
  ERROR_IF(font == NULL, L"Not an XFont class", ERROR);
  return XTextWidth(xFont->getInfo(), str.c_str(), str.length());
}

uint XWindowSystem::getTextWidth(ve::Font *font, std::wstring wstr) {
  CHECK_POINTER(font);
  XFont *xFont = dynamic_cast<XFont*>(font);
  ERROR_IF(font == NULL, L"Not an XFont class", ERROR);
  return XTextWidth16(xFont->getInfo(), (XChar2b*)wstr.c_str(), wstr.length());
}

Outcome XWindowSystem::show(Window *window) {
  CHECK_POINTER(window);
  XID win = getWindowXID(window);

  /* Request the X window to be displayed on the screen */
  //XMapWindow(dpy, win);
  return OK;
}

Outcome XWindowSystem::freeWindow(Window *window) {
  CHECK_POINTER(window);
  return OK;
}

Outcome XWindowSystem::swap(Window *window) {
  CHECK_POINTER(window);
  XID win = getWindowXID(window);

  glXSwapBuffers(dpy, win);
  return OK;
}

Outcome XWindowSystem::getScreenResolution(int &width, int &height) {
  int count = 0;
  XF86VidModeModeInfo **modes = NULL;
  return OK;

  // XF86VidModeGetAllModeLines(dpy, DefaultScreen(dpy), &count, &modes);
  width = modes[0]->hdisplay;
  height = modes[0]->vdisplay;
  XFree(modes);

  return OK;
}

Outcome XWindowSystem::setScreenResolution(ScreenMode mode) {
  int count = 0;
  Outcome result = OK;
  XF86VidModeModeInfo *needed = NULL;
  XF86VidModeModeInfo **modes = NULL;
  return OK;

  // XF86VidModeGetAllModeLines(dpy, DefaultScreen(dpy), &count, &modes);
  for (int i = 0; i < count; i++) {
    if (modes[i]->hdisplay == mode.width && modes[i]->vdisplay == mode.height) {
      needed = modes[i];
      break;
    }
  }

  if (needed) {
    // XF86VidModeSwitchToMode(dpy, DefaultScreen(dpy), needed);
    // XF86VidModeSetViewPort(dpy, DefaultScreen(dpy), 0, 0);
    XFlush(dpy);
  } else {
    result = ERROR;
  }

  XFree(modes);

  return result;
}

/**
    Returns the next window system event if there is any. If there are
    no events function blocks waits till next event happens.
@param window - Message queue of this window will be checked.
    @return Window system event.
    @return NULL is event is not supported.
*/
SystemEvent* XWindowSystem::getNextEvent(Window *window) {
  XEvent event;
  KeySym     keySym;
  const int BUFFER_SIZE = 10;
  char       buffer[BUFFER_SIZE];

  XNextEvent(dpy, &event);
  switch (event.type) {
  case DestroyNotify:
    return new WindowEvent(WINDOW_CLOSE, 0, 0);
    break;

  case ClientMessage:
    if (event.xclient.message_type == wnd_Protocols &&
      event.xclient.data.l[0] == wnd_DestroyAtom) {
      XDestroyWindow(dpy, event.xany.window);
      return new WindowEvent(WINDOW_CLOSE, 0, 0);
    }
    break;

  case KeyPress:
    XLookupString((XKeyPressedEvent *)&event, buffer, BUFFER_SIZE, &keySym, NULL);
    return new KeyEvent(KEY_PRESS, KeysCodec::LinuxToEE(keySym));

  case KeyRelease:
    XLookupString((XKeyReleasedEvent *)&event, buffer, BUFFER_SIZE, &keySym, NULL);
    return new KeyEvent(KEY_RELEASE, KeysCodec::LinuxToEE(keySym));

  case MotionNotify:
    return new MouseEvent(MOUSE_MOTION, LEFT_BUTTON, event.xmotion.x, event.xmotion.y, event.xmotion.x, event.xmotion.y);

  case ButtonPress:
    return new MouseEvent(MOUSE_PRESS, (MouseButton)event.xbutton.button, event.xmotion.x, event.xmotion.y, event.xmotion.x, event.xmotion.y);

  case ButtonRelease:
    return new MouseEvent(MOUSE_RELEASE, (MouseButton)event.xbutton.button, event.xmotion.x, event.xmotion.y, event.xmotion.x, event.xmotion.y);

  case Expose:
    return new WindowEvent(WINDOW_RESIZE, event.xexpose.width, event.xexpose.height);
  }

  return NULL;
}

/**
    Checks if there is an available event in the queue of window events.
@param window - Event queue of this window will be checked.
    @return 'true' if there is an event for the window from the window system.
@return 'false' if there are no available events for the window.
*/
bool XWindowSystem::hasAvailableEvent(Window *window) {
  return XPending(dpy) > 0;
}

/* set functions */
Outcome XWindowSystem::setCaption(Window* window, std::wstring &newCaption) {
  CHECK_POINTER(window);
  XID winId = getWindowXID(window);
  XTextProperty tp;

  tp.encoding = wnd_Name;
  tp.format = 8;
  tp.value = (unsigned char *)newCaption.c_str();
  tp.nitems = newCaption.length();

  XSetWMName(dpy, winId, &tp);
  return OK;
}

Outcome XWindowSystem::setPosition(Window* window, int newX, int newY) {
  CHECK_POINTER(window);
  XID winId = getWindowXID(window);
  XMoveWindow(dpy, winId, newX, newY);
  return OK;
}

Outcome XWindowSystem::setMode(Window *window, WindowMode newMode) {
  CHECK_POINTER(window);
  UNIMPLEMENTED();
  return OK;
}

Outcome XWindowSystem::setState(Window *window, WindowState newState) {
  CHECK_POINTER(window);
  UNIMPLEMENTED();
  return OK;
}

Outcome XWindowSystem::setWidth(Window *window, int newWidth) {
  CHECK_POINTER(window);
  XID winId = getWindowXID(window);
  XWindowAttributes wa;
  XGetWindowAttributes(dpy, winId, &wa);
  setSize(window, newWidth, wa.height);
  return OK;
}

Outcome XWindowSystem::setHeight(Window *window, int newHeight) {
  CHECK_POINTER(window);
  XID winId = getWindowXID(window);
  XWindowAttributes wa;
  XGetWindowAttributes(dpy, winId, &wa);
  setSize(window, wa.width, newHeight);
  return OK;
}

Outcome XWindowSystem::setSize(Window *window, int newWidth, int newHeight) {
  CHECK_POINTER(window);
  XID winId = getWindowXID(window);
  XResizeWindow(dpy, winId, newWidth, newHeight);
  return OK;
}

/**
  Returns viewport of the window. Viewport contains whole area that is available
  for rendering.
  @return ViewportState object that contains bounds of client area.
*/
ViewportState XWindowSystem::getClientViewport(Window *window) {
  ERROR_IF(window == NULL, L"NULL Pointer", ViewportState(0, 0, 0, 0));
  XWindowAttributes xwinAttr = { 0 };
  XID winId = getWindowXID(window);

  XGetWindowAttributes(dpy, winId, &xwinAttr);
  return ViewportState(0, 0, xwinAttr.width, xwinAttr.height);
}


}

#endif
