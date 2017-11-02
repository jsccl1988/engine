// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include <stdio.h>

#include "common.h"
#include "loaders/bmp_loader.h"
#include "textures/texture.h"

namespace ve {

BMPLoader::BMPLoader() {
}

Outcome BMPLoader::load(FILE* source, size_t offset) {
  BMPHeader header;
  BMPInfo info;
  size_t dataOffSet;
  int i, k;
  char color[4];

  CHECK_POINTER(source);
  fseek(source, offset, SEEK_SET);
  fread(&header, 1, sizeof(BMPHeader), source);

  ERROR_IF(header.type[0] != 'B' || header.type[1] != 'M', L"There isn't BM signature in BMP file header", ERROR);

  dataOffSet = header.offset;
  fread(&info, 1, sizeof(BMPInfo), source);

  ERROR_IF(info.size != sizeof(BMPInfo), L"BMP file is corrupted", ERROR);
  ERROR_IF(info.planes != 1, L"More than one plane", ERROR);
  ERROR_IF(info.bitCount != 24 && info.bitCount != 8, L"Bit count per pixel isn't 24 or 8", ERROR);
  ERROR_IF(info.compression != 0, L"Unsupported compression", ERROR);

  width = info.width;
  height = info.height;
  components = info.bitCount / 8;
  data.resize(width * height * components);
  fseek(source, dataOffSet, SEEK_SET);

  for (i = 0; i < width * height; i++) {
    fread(color, 1, components, source);
    k = i * components;

    if (components == 1)
      data[k] = color[0];

    if (components >= 3) {
      data[k] = color[2];
      data[k + 1] = color[1];
      data[k + 2] = color[0];
    }

    if (components == 4)
      data[k + 3] = color[3];
  }

  return OK;
}

}
