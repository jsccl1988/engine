// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_KEYS_CODEC_H__
#define __VE_KEYS_CODEC_H__

#include "common.h"

namespace ve {

/*
  Class that contains useful functions to translate key codes from native
  system codes to abstract key type: KeyCode.
*/
class KeysCodec {
public:
#ifdef VE_WINDOWS

  /**
    Translates windows virtual key code into KeyCode. It is used to
    translate WinOS messages into KeyEvent messages.
    @param virtualKey - virtual key code (Win OS).
    @return Corresponding KeyCode or the same virtual code if it
    does not match any KeyCode.
  */
  static KeyCode WinToEE(DWORD virtualKey);

#endif // VE_WINDOWS

#ifdef VE_LINUX

  /**
    Translates XSystem key code into KeyCode. It is used to
    translate XSystem messages into KeyEvent messages.
    @param XKey - XSystem key code (Win OS).
    @return Corresponding KeyCode or the same XKey code if it
    does not match any KeyCode.
  */
  static KeyCode LinuxToEE(int XKey);

#endif // VE_LINUX
};

}

#endif // __VE_KEYS_CODEC_H__
