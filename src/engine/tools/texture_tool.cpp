// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "tools/texture_tool.h"

namespace ve {

  PNGLoader TextureTool::pngLoader;

  TGALoader TextureTool::tgaLoader;

  BMPLoader TextureTool::bmpLoader;

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
  Texture* TextureTool::loadFromFile(Engine *engine, std::string fileName, bool useMips) {
    Texture *texture = NULL;
    std::string ext = StringTool::toLowerCase(StringTool::getFileExtension(fileName));

    if (ext == "png") {
      ERROR_IF(pngLoader.loadFromFile(fileName) != OK, L"Loading failed", NULL);
      texture = pngLoader.createTexture(engine, useMips);
      ERROR_IF(texture == NULL, L"NULL Pointer", NULL);
    } else if (ext == "tga") {
      ERROR_IF(tgaLoader.loadFromFile(fileName) != OK, L"Loading failed", NULL);
      texture = tgaLoader.createTexture(engine, useMips);
      ERROR_IF(texture == NULL, L"NULL Pointer", NULL);
    } else if (ext == "bmp") {
      ERROR_IF(bmpLoader.loadFromFile(fileName) != OK, L"Loading failed", NULL);
      texture = bmpLoader.createTexture(engine, useMips);
      ERROR_IF(texture == NULL, L"NULL Pointer", NULL);
    } else {
      LOG_ERROR(L"Unknown extension: " + StringTool::AsciiToWide(fileName) + L" / " + StringTool::AsciiToWide(ext));
    }

    return texture;
  }

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
  Outcome TextureTool::applyColorKey(TextureData *data, uint count, uchar keyRed, uchar keyGreen, uchar keyBlue) {
    CHECK_POINTER(data);

    for (uint i = 0; i < count; i++) {
      if (data[4 * i] == keyRed && data[4 * i + 1] == keyGreen && data[4 * i + 2] == keyBlue) {
        data[4 * i + 3] = 0;
      } else {
        data[4 * i + 3] = 255;
      }
    }

    return OK;
  }

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
  Outcome TextureTool::setAlpha(TextureData *data, uint count, uchar newAlpha) {
    CHECK_POINTER(data);

    for (uint i = 0; i < count; i++) {
      data[4 * i + 3] = newAlpha;
    }

    return OK;
  }

  /**
      Check if a given texture is NPOTS texture.
      @param texture - Texture to verify dimensions.
      @return true if te texture is NPOTS.
      @return else otherwise.
  */
  bool TextureTool::isNPOTSTexture(Texture *texture) {
    TextureDesc desc = texture->getDesc();
    return (((desc.width & (desc.width - 1)) != 0) || ((desc.height & (desc.height - 1)) != 0));
  }

}

