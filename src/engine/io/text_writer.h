// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_TEXT_WRITER_H__
#define __VE_TEXT_WRITER_H__

#include <cstdarg>

#include "engine/io/output_stream.h"

namespace ve {

/**
    Stream class that prints text data and sends it to an abstract output stream.
*/
class TextWriter {
private:
  OutputStream *stream;

public:
  /**
      Default constructor.
      @param stream - An abstract output stream to send printed data to.
  */
  TextWriter(OutputStream *stream);

  /**
      Prints formatted string and send the data into the output stream.
      @param bufferSize - buffer size to store this string.
      @param format - format string.
      @return Number of printed charaters.
  */
  int printf(char *format, ...);

  /**
      Flushes stream.
  */
  void flush();

  /**
      Closes this stream.
  */
  void close();
};

}

#endif // __VE_TEXT_WRITER_H__
