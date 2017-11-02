// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifdef VE_WINDOWS

#include "windows/win_message_router.h"

namespace ve {
/* Static variables */
WinMessageRouter* WinMessageRouter::instance = 0;

std::vector< std::pair<HWND, WinMessageQueue*> > WinMessageRouter::queues;

/**
  Default constructor.
*/
WinMessageRouter::WinMessageRouter() {
}

/**
  Returns an instance of this class.
  @return An instance of this class.
*/
WinMessageRouter* WinMessageRouter::getInstance() {
  if (instance == 0) {
    instance = new WinMessageRouter();
  }

  return instance;
}

/**
  Registers (handle, message queue) pair. It will be used to resolve destination queue
  when a new message comes.
  @param hWnd - Handle of the window that is owner if the given queue.
  @param queue - Message queue for the given window.
*/
void WinMessageRouter::registerQueue(HWND hWnd, WinMessageQueue *queue) {
  queues.push_back(std::make_pair(hWnd, queue));
}

/**
  Windows OS messages handler.
  @param message - Message that is coming.
  @param wparam - The first parameter of this message.
  @param lparam - The second parameter of this message.
*/
LRESULT WinMessageRouter::messageRouter(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {
  if (message == WM_DESTROY) {
    PostQuitMessage(0);
  }

  return DefWindowProc(hwnd, message, wparam, lparam);
}

}

#endif // VE_WINDOWS