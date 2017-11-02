// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifdef VE_WINDOWS

#include "windows/win_message_queue.h"

namespace ve {

/**
  Default constructor.
*/
WinMessageQueue::WinMessageQueue() {
}

/**
  Returns next message in this queue. Produces error into log file
  if no messages are available.
  @return Next message in the queue.
*/
WinMessageQueue::WinMessage WinMessageQueue::nextMessage() {
  if (messageQueue.empty()) {
    return WinMessage(0, 0, 0);
  }

  WinMessageQueue::WinMessage winMsg = messageQueue.front();
  messageQueue.pop();

  return winMsg;
}

/**
  Returns number of messages in this queue.
  @return Number of messages in this queue.
*/
uint WinMessageQueue::getMessagesCount() {
  return messageQueue.size();
}

}

#endif // VE_WINDOWS