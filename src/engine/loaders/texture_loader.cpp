// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "common.h"
#include "textures/texture.h"
#include "loaders/texture_loader.h"
#include "engines/engine.h"
#include "tools/texture_tool.h"

namespace ve {

TextureLoader::TextureLoader() {
}

TextureData *TextureLoader::getData() {
  return &data[0];
}

/* Get functions */
int TextureLoader::getWidth() {
  return width;
}

int TextureLoader::getHeight() {
  return height;
}

int TextureLoader::getComponents() {
  return components;
}

///FIXME: Is this function correct?
///At any rate.. This function sucks.. sorry :)
TextureFormat TextureLoader::getFormat() {
  if (components == 1) {
    return LUMINANCE8;
  }

  if (components == 3) {
    return RGB8;
  } else {
    return RGBA8;
  }
}

Texture* TextureLoader::createTexture(Engine* engine, bool useMips) {
  Texture* newTexture = engine->createTexture(getFormat(), getWidth(), getHeight(), getFormat(), getData(), useMips);
  ERROR_IF(newTexture == NULL, L"Format: " + StringTool::intToStr(getFormat()) + L" Width: " +
    StringTool::intToStr(getWidth()) + L" Height: " + StringTool::intToStr(getHeight()) +
    L" Mips: " + StringTool::intToStr((int)useMips), NULL);
  return newTexture;
}

/**
    Applies TextureTool::applyColorKey() function to the loaded data.
    @param redKey - Red component of key color.
    @param greenKey - Green component of key color.
    @param blueKey - Blue component of key color.
    @param Result of TextureTool::applyColotKey().
*/
Outcome TextureLoader::applyColorKey(uchar redKey, uchar greenKey, uchar blueKey) {
  ASSERT(TextureTool::applyColorKey(getData(), getWidth() * getHeight(), redKey, greenKey, blueKey));
  return OK;
}

}
