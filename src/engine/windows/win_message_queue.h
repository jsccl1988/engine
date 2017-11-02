// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifdef VE_WINDOWS

#include <queue>

#include "common.h"

namespace ve {

/**
  Queue that contains messages retrieved by WndProc function (It is used only
  in Windows version of the library). It used by window system to store incoming
  messages.
*/
class WinMessageQueue {

  struct WinMessage {
    UINT message;
    WPARAM wparam;
    LPARAM lparam;

    WinMessage(UINT message, WPARAM wparam, LPARAM lparam) {
      this->message = message;
      this->wparam = wparam;
      this->lparam = lparam;
    }
  };

private:
  std::queue<WinMessage> messageQueue;

public:
  /**
    Default constructor.
  */
  WinMessageQueue();

  /**
    Returns next message in this queue. Produces error into log file
    if no messages are available.
    @return Next message in the queue.
  */
  WinMessage nextMessage();

  /**
    Returns number of messages in this queue.
    @return Number of messages in this queue.
  */
  uint getMessagesCount();

};

}

#endif // VE_WINDOWS