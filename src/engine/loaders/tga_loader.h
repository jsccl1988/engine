// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_TGALOADER_H__
#define __VE_TGALOADER_H__

#include <stdlib.h>

#include "engine/loaders/texture_loader.h"

namespace ve {

#pragma pack(push,1)

#ifndef DOXYGEN

typedef struct {
  unsigned char IDLength;
  unsigned char colorMapType;
  unsigned char imageType;
  unsigned short mapStart;
  unsigned short mapLenght;
  unsigned char mapDepth;
  unsigned short offsetX;
  unsigned short offsetY;
  unsigned short width;
  unsigned short height;
  unsigned char bitPerPixels;
  unsigned char imageDesc;
} TGAHeader;

#endif // DOXYGEN

#pragma pack(pop)

enum TGAImageType {
  TGA_TRUECOLOR = 2,
  TGA_GRAYSCALE = 3
};

/**
    Class for loading TGA textures.
*/
class TGALoader : public TextureLoader {
public:
  /**
      Simple constructor.
  */
  TGALoader();

  /**
      Loads TGA image from specified file starting from specified offset in bytes.
      Offset is usually 0, if TGA file is read, for example. But for files which are
      contained in some archive-style file it may be useful to use offset param.
      @param source - File to read data from.
      @param offset - Offset in bytes where TGA file starts.
      @return OK if TGA image was read successfully.
      @return non-OK in case of engine error.
  */
  virtual Outcome load(FILE* source, size_t offset);
};

}

#endif // __VE_TGALOADER_H__
