// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_FILE_INPUT_STREAM_H__
#define __VE_FILE_INPUT_STREAM_H__

#include <cstdio>
#include <string>

#include "io/input_stream.h"

namespace ve {

/**
    Abstract class for input data stream. Provides only two functions that are
    used to read binary data from this stream.
*/
class FileInputStream : public InputStream {
private:
  FILE *file;

public:
  /**
    Creates input stream associated with file specified by its name.
    @param path - Path to the file to read data from.
  */
  FileInputStream(std::string path);

  /**
    Creates input stream from a file specified by FILE structure.
    @param f - FILE structure to read data from.
  */
  FileInputStream(FILE* file);

  /**
    Closes stream.
  */
  virtual ~FileInputStream();

  /**
      Reads exactly one byte from this input stream.
      @return byte that was read from the stream.
  */
  virtual char read();

  /**
      Reads array of bytes from this stream.
      @param data - Buffer pointer to write data.
      @param offset - Offset in bytes to write array.
      @param count - Number of bytes to read from the stream.
      @return Number of read bytes (value from 0 to count).
  */
  virtual int read(char* data, int offset, int count);

  /**
    Checks if at least one more byte is available at this stream.
    @return true if there is at least one byte to read.
    @return false if there is no data to read.
  */
  virtual bool available();

  /**
      Closes this stream.
  */
  virtual void close();
};

}

#endif // __VE_FILE_INPUT_STREAM_H__
