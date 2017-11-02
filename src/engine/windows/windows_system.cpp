// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifdef VE_WINDOWS

#include "common.h"
#include "windows/windows_system.h"
#include "windows/win_message_router.h"
#include "windows/win_message_pump.h"
#include "fonts/font.h"
#include "fonts/win_font.h"
#include "events/key_event.h"
#include "events/mouse_event.h"
#include "events/window_event.h"
#include "tools/string_tool.h"
#include "tools/keys_codec.h"

namespace ve {

WindowsSystem::WindowsSystem() {
}

/**
    Destructor. All the windows and fonts that were not disposed manually
    will be destroyed here in memory manager destructor.
*/
WindowsSystem::~WindowsSystem() {
}

Handle WindowsSystem::registerWindow(Window* window, HWND hWnd, HDC hDC, HGLRC hGLRC) {
  windowsData.push_back(WindowInfo(window, hWnd, hDC, hGLRC));
  return windowsData.size() - 1;
}

HWND WindowsSystem::getWindowHWND(Window* window) {
  for (uint i = 0; i < windowsData.size(); i++) {
    if (windowsData[i].window == window) {
      return windowsData[i].hWnd;
    }
  }
  return 0;
}

WindowsSystem::WindowInfo* WindowsSystem::getWindowInfo(Window* window) {
  for (uint i = 0; i < windowsData.size(); i++) {
    if (windowsData[i].window == window) {
      return &windowsData[i];
    }
  }

  return NULL;
}

Window* WindowsSystem::createWindow(const std::wstring & windowName, int x, int y,
  int width, int height, bool fullScreen) {
  WNDCLASS wndclass;
  memset(&wndclass, 0, sizeof(WNDCLASS));

  wndclass.style = 0;
  wndclass.lpfnWndProc = (WNDPROC)WinMessageRouter::messageRouter;
  wndclass.cbClsExtra = 0;
  wndclass.cbWndExtra = 0;
  wndclass.hInstance = (HINSTANCE)GetWindowLong(0, GWL_HINSTANCE);
  wndclass.hIcon = LoadIcon(wndclass.hInstance, L"WinAPI");
  wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
  wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW);
  wndclass.lpszMenuName = NULL;
  wndclass.lpszClassName = L"DEnfent_Engine";

  ERROR_IF(RegisterClass(&wndclass) == false, L"RegisterClass failed", NULL);

  DWORD dwStyle = 0;
  if (fullScreen) {
    dwStyle = WS_POPUP | WS_MAXIMIZE;
  } else {
    dwStyle = WS_OVERLAPPED | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_SYSMENU | WS_MINIMIZEBOX;
  }

  HWND hWnd = CreateWindow(L"DEnfent_Engine", windowName.c_str()
    , dwStyle, x, y, width, height, 0, 0, wndclass.hInstance, NULL);
  ERROR_IF(hWnd == 0, L"Failed to create window", NULL);

  HDC hDC = GetDC(hWnd);
  ERROR_IF(hDC == 0, L"Device context = 0", NULL);

  PIXELFORMATDESCRIPTOR pfd;

  memset(&pfd, 0, sizeof(pfd));
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;
  pfd.cAlphaBits = 8;
  pfd.iLayerType = PFD_MAIN_PLANE;

  int nPixelFormat = ChoosePixelFormat(hDC, &pfd);
  ERROR_IF(nPixelFormat == 0, L"nPixelFormat = 0", NULL);

  DescribePixelFormat(hDC, nPixelFormat, sizeof(pfd), &pfd);
  ERROR_IF(SetPixelFormat(hDC, nPixelFormat, &pfd) == false, L"SetPixelFormat returned false", NULL);

  HGLRC hGLRC = wglCreateContext(hDC);
  ERROR_IF(hGLRC == 0, L"Render context = 0", NULL);
  wglMakeCurrent(hDC, hGLRC);

  Window *window = new Window(this);
  registerWindow(window, hWnd, hDC, hGLRC);

  REGISTER_POINTER(window);

  ERROR_IF(WinMessagePump::getInstance()->start(hWnd) != OK, L"Failed to create message pump", NULL);

  return window;
}

Font* WindowsSystem::createFont(Engine *engine, FontDescriptor *desc) {
  uint bold = 0;
  HWND handle = NULL;

  if (desc->isBold()) {
    bold = FW_BOLD;
  } else {
    bold = FW_NORMAL;
  }

  HFONT hFont = CreateFont(-((int)desc->getSize()), 0, 0, 0, bold, desc->isItalic(), desc->isUnderlined(), desc->isStrikeout(),
    ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE | DEFAULT_PITCH, desc->getFontFamily().c_str());
  if (hFont == 0) {
    return NULL;
  }

  WinFont *newWinFont = new WinFont(this, engine, hFont);
  REGISTER_POINTER(newWinFont);

  return newWinFont;
}

std::vector<ScreenMode> WindowsSystem::getAvailableResolutions() {
  DEVMODE devMode;
  int i = 0;
  std::vector< std::pair <int, int> > tmpResult;
  std::vector<ScreenMode> result;

  memset(&devMode, 0, sizeof(devMode));
  devMode.dmSize = sizeof(DEVMODE);
  while (EnumDisplaySettings(NULL, i, &devMode)) {
    tmpResult.push_back(std::make_pair(devMode.dmPelsWidth, devMode.dmPelsHeight));
    i++;
  }

  std::sort(tmpResult.begin(), tmpResult.end());

  if (tmpResult.size() > 0) {
    result.push_back(ScreenMode(tmpResult[0].first, tmpResult[0].second));

    for (uint i = 1; i < tmpResult.size(); i++) {
      if (tmpResult[i].first != tmpResult[i - 1].first ||
        tmpResult[i].second != tmpResult[i - 1].second) {
        result.push_back(ScreenMode(tmpResult[i].first, tmpResult[i].second));
      }
    }
  }

  return result;
}

Outcome WindowsSystem::freeFont(Font *font) {
  WinFont *winFont = static_cast<WinFont*>(font);
  CHECK_POINTER(winFont);

  DeleteObject(winFont->getHandle());

  return OK;
}

uint WindowsSystem::getTextWidth(ve::Font *font, std::string str) {
  CHECK_POINTER_EX(font, 0);

  int strLen = str.length();
  if (strLen == 0) {
    return 0;
  }

  wchar_t *wstr = new wchar_t[strLen + 1];
  memset(wstr, 0, sizeof(wchar_t) * (strLen + 1));
  ERROR_IF(MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, wstr, strLen + 1) != strLen, L"Conversion failed", 0);
  uint result = getTextWidth(font, std::wstring(wstr));
  delete[] wstr;

  return result;
}

uint WindowsSystem::getTextWidth(ve::Font *font, std::wstring wstr) {
  CHECK_POINTER_EX(font, 0);

  WinFont *winFont = static_cast<WinFont*>(font);
  CHECK_POINTER(winFont);

  uint strLen = wstr.length();
  if (strLen == 0) {
    return 0;
  }

  int* length = new int[strLen];

  HWND hWnd = GetActiveWindow();
  ERROR_IF(hWnd == 0, L"GetActiveWindow() failed", 0);
  HDC hDC = GetDC(hWnd);
  ERROR_IF(hDC == 0, L"GetDC() failed", 0);
  ERROR_IF(GetCharWidthI(hDC, 0, strLen, (LPWORD)wstr.c_str(), length) == 0, L"GetCharWidthI() failed", 0);

  int retVal = 0;
  for (uint i = 0; i < strLen; i++) {
    retVal += length[i];
  }

  delete[] length;

  return retVal;
}

Outcome WindowsSystem::show(Window *window) {
  CHECK_POINTER(window);
  HWND hWnd = getWindowHWND(window);
  ERROR_IF(hWnd == 0, L"Incorrect window", ERROR);
  ShowWindow(hWnd, SW_SHOW);
  return OK;
}

Outcome WindowsSystem::freeWindow(Window *window) {
  CHECK_POINTER(window);

  WindowInfo *info = getWindowInfo(window);
  ERROR_IF(info == NULL, L"Wrong window class [Created by other WindowSystem class]", ERROR);

  wglMakeCurrent(NULL, NULL);
  if (info->hGLRC != 0) {
    wglDeleteContext(info->hGLRC);
  }
  return OK;
}

Outcome WindowsSystem::swap(Window *window) {
  CHECK_POINTER(window);

  WindowInfo *info = getWindowInfo(window);
  SwapBuffers(info->hDC);
  return OK;
}

Outcome WindowsSystem::getScreenResolution(int &width, int &height) {
  RECT rc = { 0 };
  ERROR_IF(!GetWindowRect(GetDesktopWindow(), &rc), L"GetWindowRect failed", ERROR);

  width = rc.right;
  height = rc.bottom;

  return OK;
}

Outcome WindowsSystem::setScreenResolution(ScreenMode mode) {
  DEVMODE dm;
  memset(&dm, 0, sizeof(DEVMODE));

  dm.dmSize = sizeof(DEVMODE);
  dm.dmPelsWidth = mode.width;
  dm.dmPelsHeight = mode.height;
  dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;

  LONG result = ChangeDisplaySettings(&dm, CDS_UPDATEREGISTRY);
  ERROR_IF(result != DISP_CHANGE_SUCCESSFUL, L"ChangeDisplaySettings failed, error: " + StringTool::intToStr(result), ERROR);

  return OK;
}

/**
    Returns the next window system event if there is any. If there are
    no events function blocks waits till next event happens.
@param window - Message queue of this window will be checked.
    @return Window system event.
    @return NULL is event is not supported.
*/
SystemEvent* WindowsSystem::getNextEvent(Window *window) {
  CHECK_POINTER_EX(window, false);

  WindowInfo *info = getWindowInfo(window);
  MSG msg = { 0 };

  bool quit = (::GetMessage(&msg, info->hWnd, 0, 0) == 0);
  ::TranslateMessage(&msg);
  ::DispatchMessage(&msg);

  if (quit == true) {
    return new WindowEvent(WINDOW_CLOSE, 0, 0);
  }

  DWORD lParam = msg.lParam;
  DWORD wParam = msg.wParam;

  switch (msg.message) {
  case WM_DESTROY:
    return new WindowEvent(WINDOW_CLOSE, 0, 0);
  case WM_KEYDOWN:
    return new KeyEvent(KEY_PRESS, KeysCodec::WinToEE(msg.wParam));
  case WM_KEYUP:
    return new KeyEvent(KEY_RELEASE, KeysCodec::WinToEE(msg.wParam));
  case WM_LBUTTONDOWN:
    return new MouseEvent(MOUSE_PRESS, LEFT_BUTTON, LOWORD(lParam), HIWORD(lParam), LOWORD(lParam), HIWORD(lParam));
  case WM_LBUTTONUP:
    return new MouseEvent(MOUSE_RELEASE, LEFT_BUTTON, LOWORD(lParam), HIWORD(lParam), LOWORD(lParam), HIWORD(lParam));
  case WM_RBUTTONDOWN:
    return new MouseEvent(MOUSE_PRESS, RIGHT_BUTTON, LOWORD(lParam), HIWORD(lParam), LOWORD(lParam), HIWORD(lParam));
  case WM_RBUTTONUP:
    return new MouseEvent(MOUSE_RELEASE, RIGHT_BUTTON, LOWORD(lParam), HIWORD(lParam), LOWORD(lParam), HIWORD(lParam));
  case WM_MOUSEMOVE:
    return new MouseEvent(MOUSE_MOTION, LEFT_BUTTON, LOWORD(lParam), HIWORD(lParam), LOWORD(lParam), HIWORD(lParam));
  case WM_MOUSEWHEEL:
    if (((short)HIWORD(wParam)) > 0) {
      return new MouseEvent(MOUSE_PRESS, WHEEL_UP, LOWORD(lParam), HIWORD(lParam), LOWORD(lParam), HIWORD(lParam));
    } else {
      return new MouseEvent(MOUSE_PRESS, WHEEL_DOWN, LOWORD(lParam), HIWORD(lParam), LOWORD(lParam), HIWORD(lParam));
    }
  case WM_SIZE:
    return new WindowEvent(WINDOW_RESIZE, LOWORD(lParam), HIWORD(lParam));
  }

  return NULL;
}

/**
    Checks if there is an available event in the queue of window events.
@param window - Event queue of this window will be checked.
    @return 'true' if there is an event for the window from the window system.
@return 'false' if there are no available events for the window.
*/
bool WindowsSystem::hasAvailableEvent(Window *window) {
  CHECK_POINTER_EX(window, false);

  WindowInfo *info = getWindowInfo(window);
  MSG msg = { 0 };
  if (PeekMessage(&msg, info->hWnd, 0, 0, PM_NOREMOVE)) {
    return true;
  }
  return false;
}

/* set functions */
Outcome WindowsSystem::setCaption(Window* window, std::wstring &newCaption) {
  CHECK_POINTER(window);

  WindowInfo *info = getWindowInfo(window);
  ERROR_IF(!SetWindowText(info->hWnd, newCaption.c_str()), L"SetWindowText failed", WINAPI_ERROR);

  return OK;
}

Outcome WindowsSystem::setPosition(Window* window, int newX, int newY) {
  CHECK_POINTER(window);

  WindowInfo *info = getWindowInfo(window);
  ERROR_IF(!SetWindowPos(info->hWnd, HWND_TOP, newX, newY, 0, 0, SWP_NOSIZE), L"SetWindowPos failed", WINAPI_ERROR);

  return OK;
}

Outcome WindowsSystem::setMode(Window *window, WindowMode newMode) {
  CHECK_POINTER(window);

  WindowInfo *info = getWindowInfo(window);
  UNIMPLEMENTED();
  return OK;
}

Outcome WindowsSystem::setState(Window *window, WindowState newState) {
  CHECK_POINTER(window);

  WindowInfo *info = getWindowInfo(window);

  switch (newState) {
  case WS_SHOWN:
    return show(window);

  case WS_HIDDEN:
    ERROR_IF(!ShowWindow(info->hWnd, SW_HIDE), L"ShowWindow failed", WINAPI_ERROR);
    break;

  case WS_ICONIFIED:
    ERROR_IF(!ShowWindow(info->hWnd, SW_MINIMIZE), L"ShowWindow failed", WINAPI_ERROR);
    break;

  default:
    LOG_ERROR(L"Unsupported state");
  }

  return OK;
}

Outcome WindowsSystem::setWidth(Window *window, int newWidth) {
  CHECK_POINTER(window);

  RECT rect = { 0 };
  WindowInfo *info = getWindowInfo(window);
  ERROR_IF(!GetWindowRect(info->hWnd, &rect), L"GetWindowRect failed", WINAPI_ERROR);
  ERROR_IF(!SetWindowPos(info->hWnd, HWND_TOP, 0, 0, newWidth, rect.bottom, SWP_NOMOVE), L"GetWindowRect failed", WINAPI_ERROR);

  return OK;
}

Outcome WindowsSystem::setHeight(Window *window, int newHeight) {
  CHECK_POINTER(window);

  RECT rect = { 0 };
  WindowInfo *info = getWindowInfo(window);
  ERROR_IF(!GetWindowRect(info->hWnd, &rect), L"GetWindowRect failed", WINAPI_ERROR);
  ERROR_IF(!SetWindowPos(info->hWnd, HWND_TOP, 0, 0, rect.right, newHeight, SWP_NOMOVE), L"SetWindowPos failed", WINAPI_ERROR);

  return OK;
}

Outcome WindowsSystem::setSize(Window *window, int newWidth, int newHeight) {
  CHECK_POINTER(window);

  RECT rect = { 0 };
  WindowInfo *info = getWindowInfo(window);
  ERROR_IF(!SetWindowPos(info->hWnd, HWND_TOP, 0, 0, newWidth, newHeight, SWP_NOMOVE), L"SetWindowPos failed", WINAPI_ERROR);

  return OK;
}

/**
  Returns viewport of the window. Viewport contains whole area that is available
  for rendering.
  @return ViewportState object that contains bounds of client area.
*/
ViewportState WindowsSystem::getClientViewport(Window *window) {
  RECT rect = { 0 };
  HWND winHWND = getWindowHWND(window);

  GetClientRect(winHWND, &rect);
  return ViewportState(0, 0, rect.right, rect.bottom);
}

}

#endif
