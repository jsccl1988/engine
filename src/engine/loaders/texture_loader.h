// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_TEXTURELOADER_H__
#define __VE_TEXTURELOADER_H__

#include "engine/consts.h"
#include "engine/loaders/loader.h"
#include "engine/textures/texture.h"

namespace ve {

class Texture;
class Engine;

/**
    Base class for those classes which are used to load
    textures from files.
*/
class TextureLoader : public Loader {
protected:
  /** Width of loaded texture */
  int width;

  /** Height of loaded texture */
  int height;

  /** Number of component of loaded texture */
  int components;

  /** Texture data array */
  std::vector<TextureData> data;

public:

  /**
      Simple constructor.
  */
  TextureLoader();

  /**
      Returns color data for the last loaded texture.
      @return Color data for the last loaded texture.
  */
  TextureData *getData();

  /**
      Returns width of the last loaded texture.
      @return Width of the last loaded texture.
  */
  int getWidth();

  /**
      Returns height of the last loaded texture.
      @return Height of the last loaded texture.
  */
  int getHeight();

  /**
      Returns number of components of the last loaded texture.
      @return Number of components of the last loaded texture.
  */
  int getComponents();

  /**
      Returns format of the last loaded texture.
      @return format of the last loaded texture.
  */
  TextureFormat getFormat();

  /**
      Creates texture object from the loaded data using specified Engine object.
      @param engine - Engine object to use for texture creating.
      @param useMips - 'true' for MIPs auto-generation and 'false' to not use MIP levels.
      @return Pointer to Texture object if it was created successfully.
      @return NULL if engine error occurred or there was no load() calls.
  */
  Texture *createTexture(Engine* engine, bool useMips = true);

  /**
      Applies TextureTool::applyColorKey() function to the loaded data.
      @param redKey - Red component of key color.
      @param greenKey - Green component of key color.
      @param blueKey - Blue component of key color.
      @param Result of TextureTool::applyColotKey().
  */
  Outcome applyColorKey(uchar redKey, uchar greenKey, uchar blueKey);
};

}

#endif // __VE_TEXTURELOADER_H__
