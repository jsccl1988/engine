// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "io/file_input_stream.h"

namespace ve {

FileInputStream::FileInputStream(std::string path) {
  file = fopen(path.c_str(), "r");
}

FileInputStream::FileInputStream(FILE* file) {
  this->file = file;
}

FileInputStream::~FileInputStream() {
  close();
}

char FileInputStream::read() {
  if (file) {
    char result = 0;
    fread(&result, sizeof(char), 1, file);
    return result;
  }

  return 0;
}

int FileInputStream::read(char* data, int offset, int count) {
  if (file) {
    return (int)fread(data, count, 1, file);
  }

  return 0;
}

bool FileInputStream::available() {
  if (file) {
    return (!feof(file));
  }

  return true;
}

void FileInputStream::close() {
  if (file) {
    fclose(file);
    file = NULL;
  }
}

}