// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifdef VE_WINDOWS

#include "windows/win_message_pump.h"

namespace ve {

/* Static members */
WinMessagePump* WinMessagePump::instance = 0;

/**
  Default constructor.
*/
WinMessagePump::WinMessagePump() {
  running = true;
}

/**
  Destructors. Stops all the threads.
*/
WinMessagePump::~WinMessagePump() {
  running = false;

  for (ve::uint i = 0; i < threads.size(); i++) {
    WaitForSingleObject(threads[i], INFINITE);
  }
}

/**
  Static thread function to delegate thread execution to the Pump() fucntion
  of this class.
*/
DWORD WinMessagePump::GlobalPump(void *context) {
  ThreadParams *params = (ThreadParams*)context;
  HWND hWnd = params->hWnd;
  WinMessagePump *pump = params->pump;
  delete params;
  return pump->Pump(hWnd);
}

/**
  Thread function.
  @param handle - Handle of the window that should be supplied by this pump.
*/
DWORD WinMessagePump::Pump(HWND handle) {
  MSG msg = { 0 };

  while (running && ::GetMessage(&msg, handle, 0, 0)) {
    ::TranslateMessage(&msg);
    ::DispatchMessage(&msg);
  }

  return 0;
}

/**
  Returns an instance of this class.
*/
WinMessagePump* WinMessagePump::getInstance() {
  if (instance == 0) {
    instance = new WinMessagePump();
  }

  return instance;
}

/**
  Starts new thread that handles message for the window
  specified by the given handle.
  @param hWnd - handle of the window to start message thread for.
  @return OK if thread was started successfully.
  @return ERROR if there was an error during thread creation.
*/
Outcome WinMessagePump::start(HWND hWnd) {
  ThreadParams* params = new ThreadParams(hWnd, this);
  DWORD threadID = 0;
  HANDLE handle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)GlobalPump, (PVOID)params, 0, &threadID);
  ERROR_IF(handle == 0, L"Unable to start thread", ERROR);
  threads.push_back(handle);
  return OK;
}

}

#endif // VE_WINDOWS