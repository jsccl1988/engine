// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_PNGLOADER_H__
#define __VE_PNGLOADER_H__

#include <stdlib.h>

#include "engine/zlib/zlib.h"
#include "engine/loaders/texture_loader.h"

// PNG chunks type
#define PNG_CHUNK_IHDR 0x49484452
#define PNG_CHUNK_IDAT 0x49444154
#define PNG_CHUNK_IEND 0x49454E44

// Compression methods
#define PNG_DEFLATE_METHOD  0

// Interlace methods
#define PNG_NO_INTERLACE    0
#define PNG_ADAM7_INTERLACE 1

// Filter methods
#define PNG_5FILTERS        0
#define FILTER_NONE         0
#define FILTER_SUB          1
#define FILTER_UP           2
#define FILTER_AVERAGE      3
#define FILTER_PAETH        4

namespace ve {

enum PNGColorType {
  PNG_GRAYSCALE = 0,
  PNG_RGB = 2,
  PNG_RGBA = 6
};

#pragma pack(push, 1)

#ifndef DOXYGEN

typedef unsigned char PNGHeader[8];     // Must be equal 137, 80, 78, 71, 13, 10, 26, 10

typedef struct {
  unsigned int length;
  unsigned int type;
} PNGChunk;

typedef unsigned int PNGCRC;

typedef struct {
  unsigned int width;
  unsigned int height;
  unsigned char bitDepth;
  unsigned char colorType;
  unsigned char compressionMethod;
  unsigned char filterMethod;
  unsigned char interlaceMethod;
} IHDRChunk;

#endif // DOXYGEN

#pragma pack(pop)

/**
    Class for loading PNG textures.
*/
class PNGLoader : public TextureLoader {
private:
  ZLib zLib;
  void reverseLongInt(unsigned int *x);
  void reverseWord(unsigned short *x);
  unsigned int paethPredictor(unsigned char a, unsigned char b, unsigned char c);

public:
  /**
      Simple constructor.
  */
  PNGLoader();

  /**
      Loads PNG image from specified file starting from specified offset in bytes.
      Offset is usually 0, if PNG file is read, for example. But for files which are
      contained in some archive-style file it may be useful to use offset param.
      @param source - File to read data from.
      @param offset - Offset in bytes where PNG file starts.
      @return OK if PNG image was read successfully.
      @return non-OK in case of engine error.
  */
  virtual Outcome load(FILE *source, size_t offset);
};

}

#endif // __VE_PNGLOADER_H__
