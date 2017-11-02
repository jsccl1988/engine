// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifdef VE_WINDOWS

#ifndef __VE_WIN_MESSAGE_PUMP_H__
#define __VE_WIN_MESSAGE_PUMP_H__

#include <vector>

#include "common.h"

namespace ve {

/*
  Class that is used to create a new thread with a message loop inside.
  WindowsSystem class uses WinMessagePump in WindowsSystem::CreateWindow function
  to start message handling. It is designed as a singleton class to keep control over
  all the threads in one object.
*/
class WinMessagePump {
private:

  struct ThreadParams {
    HWND hWnd;
    WinMessagePump* pump;

    ThreadParams(HWND hWnd, WinMessagePump* pump) {
      this->hWnd = hWnd;
      this->pump = pump;
    }
  };

  /* The only one instance of this class */
  static WinMessagePump* instance;

  /* Handles of created threads */
  std::vector<HANDLE> threads;

  /* Flag that defines if threads are able to process messaging */
  bool running;

  /**
    Thread function.
    @param handle - Handle of the window that should be supplied by this pump.
  */
  DWORD Pump(HWND handle);

  /**
    Static thread function to delegate thread execution to the Pump() fucntion
    of this class.
  */
  static DWORD GlobalPump(void *context);

  /**
    Default constructor.
  */
  WinMessagePump();

  /**
    Copy constructor.
  */
  WinMessagePump(WinMessagePump &wmp);

  /**
    operator =
  */
  WinMessagePump operator = (WinMessagePump wmp);

public:
  /**
    Destructors. Stops all the threads.
  */
  ~WinMessagePump();

  /**
    Returns an instance of this class.
  */
  static WinMessagePump* getInstance();

  /**
    Starts new thread that handles message for the window
    specified by the given handle.
    @param hWnd - handle of the window to start message thread for.
    @return OK if thread was started successfully.
    @return non-OK code if there was an error during thread creation.
  */
  Outcome start(HWND hWnd);
};

}

#endif // __VE_WIN_MESSAGE_PUMP_H__

#endif // VE_WINDOWS