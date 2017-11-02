// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include <stdio.h>

#include "common.h"
#include "loaders/loader.h"

namespace ve {

Loader::Loader() {
}

Outcome Loader::loadFromFile(std::string fileName) {
  FILE *source;
  Outcome result;

  source = fopen(fileName.c_str(), "rb");
  ERROR_IF(source == 0, L"File not found - File name: " + StringTool::AsciiToWide(fileName), IO_ERROR);
  result = load(source, 0);
  fclose(source);
  return result;
}

Outcome Loader::load(FILE* source, size_t offset) {
  return OK;
}

}
