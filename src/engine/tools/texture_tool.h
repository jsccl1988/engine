// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_TEXTURE_TOOL_H__
#define __VE_TEXTURE_TOOL_H__

#include "engine/common.h"
#include "engine/textures/texture.h"
#include "engine/loaders/png_loader.h"
#include "engine/loaders/tga_loader.h"
#include "engine/loaders/bmp_loader.h"

namespace ve {

/**
    Class that contains useful static functions to work with textures / textures' data.
*/
class TextureTool {
private:
  /* Loader for .png files */
  static PNGLoader pngLoader;

  /* Loader for .tga files */
  static TGALoader tgaLoader;

  /* Loader for .bmp files */
  static BMPLoader bmpLoader;

public:

  /**
      Creates texture from file. Three type of images is supported by this function:
      PNG, TGA and BMP. There is no cache in this function and two calls with the same
      file name will return different textures with the same color data.
      @param engine - Engine that is used to create the texture.
      @param fileName - Path to the file to create texture from.
      @param useMips - Flag that defines if MIP levels should be created for the texture.
      Note that MIP levels are supported only for non-POT textures.
      @return Texture object if it was successfully created.
      @return NULL if image type is not supported.
  */
  static Texture* loadFromFile(Engine *engine, std::string fileName, bool useMips = true);

  /**
      Applies key-color for RGBA8 texture data. This functions iterates through all the pixels
      in the array and if the color is the same as given key-color sets 255 in alpha channel,
      0 in other case.

      <b>Note:</b> It works only for RGBA8 data layout.
      @param data - Texture data in RGBA8 format to apply key color.
      It will be modified.
      @param count - Number of pixels in the data array.
      @param keyRed - Red component of key color.
      @param keyGreen - Red component of key color.
      @param keyBlue - Blue component of key color.
      @return OK if operation succeeded.
      @return NULL_POINTER if data pointer is NULL.
  */
  static Outcome applyColorKey(TextureData *data, uint count, uchar keyRed, uchar keyGreen, uchar keyBlue);

  /**
      Changes alpha component for all the pixels in RGBA8 texture data array.
      <b>Note:</b> This function is only for RGBA8 data layout.
      @param data - Texture data in RGBA8 format to change alpha component.
      @param count - Number of pixels in the array.
      @param newAlpha - new value of the alpha component for all the pixels
      in the data array.
      @return OK if operation succeeded.
      @return NULL_POINTER if data pointer is NULL.
  */
  static Outcome setAlpha(TextureData *data, uint count, uchar newAlpha);

  /**
      Check if a given texture is NPOTS texture.
      @param texture - Texture to verify dimensions.
      @return true if te texture is NPOTS.
      @return else otherwise.
  */
  static bool isNPOTSTexture(Texture *texture);
};

}

#endif // __VE_TEXTURE_TOOL_H__
