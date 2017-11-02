// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "io/file_output_stream.h"

namespace ve {

FileOutputStream::FileOutputStream(std::string fileName) {
  file = fopen(fileName.c_str(), "wb");
}

FileOutputStream::FileOutputStream(FILE *file) {
  this->file = file;
}

FileOutputStream::~FileOutputStream() {
  close();
}

int FileOutputStream::write(char byte) {
  if (file) {
    return fwrite(&byte, 1, 1, file);
  }

  return 0;
}

int FileOutputStream::write(char* data, int offset, int count) {
  if (file) {
    return fwrite(&data[offset], 1, count, file);
  }

  return 0;
}

void FileOutputStream::flush() {
  if (file) {
    fflush(file);
  }
}

void FileOutputStream::close() {
  if (file) {
    fclose(file);
    file = NULL;
  }
}

}
