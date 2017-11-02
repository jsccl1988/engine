// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_FILE_OUTPUT_STREAM_H__
#define __VE_FILE_OUTPUT_STREAM_H__

#include <cstdio>
#include <string>

#include "engine/io/output_stream.h"

namespace ve {

/**
    Stream class that outputs all the data into the file.
*/
class FileOutputStream : public OutputStream {
protected:
  FILE *file;

public:
  /**
      Creates output stream to a file. It will be created if it does not exist or rewritten
      if exists.
      @param fileName - Path to the file to create or recreate if it is already exists.
  */
  FileOutputStream(std::string fileName);

  /**
      Creates output stream to a file that is specified as FILE* structure. Use this constructor
      to associate output stream with console.
      @param file - File to create output stream for.
  */
  FileOutputStream(FILE *file);

  /**
    Closes stream.
  */
  virtual ~FileOutputStream();

  /**
      Writes exactly one byte into the file.
      @param byte - Byte value to write into file.
      @return Number of written bytes (thus, one or zero)
  */
  virtual int write(char byte);

  /**
      Writes array of bytes into the file.
      @param data - Array pointer to read data from.
      @param offset - Offset in bytes to start reading from array.
      @param count - Number of bytes to write into the file.
      @return Number of written bytes (value from 0 to count).
  */
  virtual int write(char* data, int offset, int count);

  /**
      Flushes file buffer into the disk.
  */
  virtual void flush();

  /**
      Closes the file. Any attempt to write data into this file stream will have no
      success and all the write() functions will return 0.
  */
  virtual void close();
};

}

#endif // __VE_FILE_OUTPUT_STREAM_H__
