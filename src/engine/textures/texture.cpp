// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include <memory.h>

#include "common.h"
#include "textures/texture.h"
#include "math/maths.h"
#include "engines/engine.h"
#include "tools/texture_tool.h"

namespace ve {

Texture::Texture(Engine *engine, TextureDesc desc, Handle handle) {
  this->engine = engine;
  this->handle = handle;
  this->desc = desc;
  memset(&desc, 0, sizeof(desc));
}

Texture::~Texture() {
  engine->freeTexture(this);
}

Handle Texture::getHandle() {
  return handle;
}

Outcome Texture::load(TextureFormat nativeformat, TextureData *data) {
  CHECK_RESULT(engine->updateTexture(this, nativeformat, data), L"Update Texture failed");
  return OK;
}

TextureDesc Texture::getDesc() {
  return desc;
}

}
