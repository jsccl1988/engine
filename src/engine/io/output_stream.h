// Copyright (c) 2017 The Smart Authors.
// All rights reserved.
#ifndef __VE_OUTPUT_STREAM_H__
#define __VE_OUTPUT_STREAM_H__

namespace ve {

/**
    Abstract class for output data stream. Provides only two functions that are
    used to write byte data into this stream.
*/
class OutputStream {
public:
  /**
      Writes exactly one byte into this output stream.
      @param byte - Byte value to write into this stream.
      @return Number of written bytes (thus, one or zero)
  */
  virtual int write(char byte) = 0;

  /**
      Writes array of bytes into this stream.
      @param data - Array pointer to read data from.
      @param offset - Offset in bytes to start reading from array.
      @param count - Number of bytes to write into this stream.
      @return Number of written bytes (value from 0 to count).
  */
  virtual int write(char* data, int offset, int count) = 0;

  /**
      Flushes stream.
  */
  virtual void flush() = 0;

  /**
      Closes this stream.
  */
  virtual void close() = 0;
};

}

#endif // __VE_OUTPUT_STREAM_H__
