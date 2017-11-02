// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifdef VE_WINDOWS

#ifndef __VE_WIN_MESSAGE_ROUTER__
#define __VE_WIN_MESSAGE_ROUTER__

#include <vector>

#include "common.h"
#include "windows/win_message_queue.h"

namespace ve {

/**
  Singleton class that distributes Windows OS messages to appropriate window queues.
  Each time this class get a message from Windows OS it looks for appropriate window queue
  to put message in.
*/
class WinMessageRouter {
private:
  /* The only one instance of this class */
  static WinMessageRouter *instance;

  /* Array of registered queues */
  static std::vector< std::pair<HWND, WinMessageQueue*> > queues;

  /**
    Default constructor.
  */
  WinMessageRouter();

  /**
    Copy constructor.
  */
  WinMessageRouter(WinMessageRouter &wmp);

  /**
    operator =
  */
  WinMessageRouter operator = (WinMessageRouter wmp);

public:
  /**
    Returns an instance of this class.
    @return An instance of this class.
  */
  static WinMessageRouter* getInstance();

  /**
    Registers (handle, message queue) pair. It will be used to resolve destination queue
    when a new message comes.
    @param hWnd - Handle of the window that is owner if the given queue.
    @param queue - Message queue for the given window.
  */
  static void registerQueue(HWND hWnd, WinMessageQueue *queue);

  /**
    Windows OS messages handler.
    @param message - Message that is coming.
    @param wparam - The first parameter of this message.
    @param lparam - The second parameter of this message.
  */
  static LRESULT messageRouter(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

};

}

#endif // __VE_WIN_MESSAGE_ROUTER__

#endif // VE_WINDOWS