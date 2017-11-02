// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_INPUT_STREAM_H__
#define __VE_INPUT_STREAM_H__

#include "common.h"

namespace ve {

/**
    Abstract class for input data stream. Provides only two functions that are
    used to read binary data from this stream.
*/
class InputStream {
public:
  /**
      Reads exactly one byte from this input stream.
      @return byte that was read from the stream.
  */
  virtual char read() = 0;

  /**
      Reads array of bytes from this stream.
      @param data - Buffer pointer to write data.
      @param offset - Offset in bytes to write array.
      @param count - Number of bytes to read from the stream.
      @return Number of read bytes (value from 0 to count).
  */
  virtual int read(char* data, int offset, int count) = 0;

  /**
    Checks if at least one more byte is available at this stream.
    @return true if there is at least one byte to read.
    @return false if there is no data to read.
  */
  virtual bool available() = 0;

  /**
      Closes this stream.
  */
  virtual void close() = 0;
};

}

#endif // __VE_INPUT_STREAM_H__
