// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_BMPLOADER_H__
#define __VE_BMPLOADER_H__

#include <stdio.h>

#include "engine/common.h"
#include "engine/loaders/texture_loader.h"

namespace ve {

#pragma pack(push,1)

#ifndef DOXYGEN

typedef struct BMPHeader {
  char           type[2];
  unsigned long  size;
  unsigned short reserved1;
  unsigned short reserved2;
  unsigned long  offset;
} BMPHeader;

typedef struct BMPInfo {
  unsigned long size;
  unsigned long width;
  unsigned long height;
  unsigned short planes;
  unsigned short bitCount;
  unsigned long compression;
  unsigned long sizeImage;
  unsigned long XPelsPerMeter;
  unsigned long YPelPerMeter;
  unsigned long clrUsed;
  unsigned long clrImportant;
} BMPInfo;

#endif // DOXYGEN

#pragma pack(pop)

/**
    Class for loading BMP textures.
*/
class BMPLoader : public TextureLoader {
public:
  /**
      Simple constructor.
  */
  BMPLoader();

  /**
      Loads BMP image from specified file starting from specified offset in bytes.
      Offset is usually 0, if BMP file is read, for example. But for files which are
      contained in some archive-style file it may be useful to use offset param.
      @param source - File to read data from.
      @param offset - Offset in bytes where BMP file starts.
      @return OK if BMP image was read successfully.
      @return non-OK in case of engine error.
  */
  virtual Outcome load(FILE *source, size_t offset);
};

}

#endif // __VE_BMPLOADER_H__
