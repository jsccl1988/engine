// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include <cstdio>

#include "io/text_writer.h"

namespace ve {

/**
    Default constructor.
    @param fileName - Path to the file to create or recreate if it is already exists.
*/
TextWriter::TextWriter(OutputStream *stream) {
  this->stream = stream;
}

/**
    Prints formatted string into the text file.
    @param format - format string.
    @return Number of printed charaters.
*/
int TextWriter::printf(char *format, ...) {
  /// FIXME: This code sucks.. Any ideas how to fix?
  char buffer[1000];
  int written = 0;

  va_list args;
  va_start(args, format);
  written = vsprintf(buffer, format, args);
  va_end(args);

  return stream->write(buffer, 0, written);
}

/**
    Flushes stream.
*/
void TextWriter::flush() {
  stream->flush();
}

/**
    Closes this stream.
*/
void TextWriter::close() {
  stream->close();
}

}
