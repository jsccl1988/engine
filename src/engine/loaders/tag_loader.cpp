// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include <stdio.h>

#include "common.h"
#include "loaders/tga_loader.h"

namespace ve {

  TGALoader::TGALoader() {
  }

  Outcome TGALoader::load(FILE* source, size_t offset) {
    TGAHeader header;
    unsigned char color[4], mask;
    int i, j, k;

    fseek(source, offset, SEEK_SET);
    fread(&header, 1, sizeof(TGAHeader), source);
    ERROR_IF(header.colorMapType != 0, L"There is color map which not supported", ERROR);
    ERROR_IF(header.imageType != TGA_TRUECOLOR && header.imageType != TGA_GRAYSCALE, L"Unsupported image type", ERROR);
    width = header.width;
    height = header.height;
    components = header.bitPerPixels / 8;
    if (header.IDLength != 0) {
      fseek(source, header.IDLength, SEEK_CUR);
    }
    data.resize(width * height * components);
    // Mask = 0 then image starts in left bottom corner
    mask = header.imageDesc & 0x30;
    for (i = 0; i < height; i++) {
      for (j = 0; j < width; j++) {
        fread(color, 1, components, source);

        if (mask != 0) {
          k = ((height - i - 1) * width + j) * components;
        } else {
          k = (i * width + j) * components;
        }

        if (components == 1) {
          data[k] = color[0];
        }

        if (components >= 3) {
          data[k + 0] = color[2];
          data[k + 1] = color[1];
          data[k + 2] = color[0];
        }

        if (components == 4) {
          data[k + 3] = color[3];
        }
      }
    }

    return OK;
  }

}
