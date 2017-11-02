// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_FILE_H__
#define __VE_FILE_H__

#include <string>

#include "common.h"

namespace ve {

/**
  Contains basic file operations.
*/
class File {
private:
  std::string path;

public:
  /**
    @param path - path to the file
  */
  File(std::string path);

  /**
    Returns size of the file in bytes.
    @return Size of the file in bytes.
  */
  uint getSize();

  /**
    Computes CRC32 for this file if it exists and
    if not returns 0 (note: 0 is a correct CRC32 value).
    @return CRC32 for this file if it exists.
  */
  int getCRC32();

  /**
    Check if this file exists.
    @return true if file exists.
    @return file if file does not exist.
  */
  bool exists();
};

}

#endif // __VE_FILE_H__