// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "tools/keys_codec.h"

namespace ve {

#ifdef VE_WINDOWS

/**
  Translates windows virtual key code into KeyCode. It is used to
  translate WinOS messages into KeyEvent messages.
  @param virtualKey - virtual key code (Win OS).
  @return Corresponding KeyCode or the same virtual code if it
  does not match any KeyCode.
*/
KeyCode KeysCodec::WinToEE(DWORD virtualKey) {
  switch (virtualKey) {
  case VK_LEFT:
    return KEY_LEFT;
  case VK_RIGHT:
    return KEY_RIGHT;
  case VK_UP:
    return KEY_UP;
  case VK_DOWN:
    return KEY_DOWN;
  default:
    return (KeyCode)virtualKey;
  }
}

#endif // VE_WINDOWS

#ifdef VE_LINUX

/**
  Translates XSystem key code into KeyCode. It is used to
  translate XSystem messages into KeyEvent messages.
  @param XKey - XSystem key code (Win OS).
  @return Corresponding KeyCode or the same XKey code if it
  does not match any KeyCode.
*/
KeyCode KeysCodec::LinuxToEE(int XKey) {
  switch (XKey) {
  case XK_Left:
    return KEY_LEFT;
  case XK_Right:
    return KEY_RIGHT;
  case XK_Up:
    return KEY_UP;
  case XK_Down:
    return KEY_DOWN;
  default:
    return (KeyCode)XKey;
  }
}

#endif // VE_LINUX

}
