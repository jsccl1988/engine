// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_LOADER_H__
#define __VE_LOADER_H__

#include <stdio.h>
#include <stdlib.h>

#include <string>

#include "engine/common.h"

namespace ve {

/**
    Base class for classes which are used to load data from
    different files like textures, models, etc.
*/
class Loader {
public:
  /**
      Simple constructor.
  */
  Loader();

  /**
      Loads data from specified file.
      @return OK if loading succeeded.
      @return non-OK if engine error occurred or in case
      of corrupted file.
  */
  Outcome loadFromFile(std::string fileName);

  /**
      Loads data from specified file starting from specified offset in bytes.
      For files which are contained in some archive-style file it may be useful
      to use offset param.
      @param source - File to read data from.
      @param offset - Offset in bytes where data starts.
      @return OK if BMP image was read successfully.
      @return non-OK in case of engine error.
  */
  virtual Outcome load(FILE* source, size_t offset);
};

}

#endif // __VE_LOADER_H__
