// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "engines/engine.h"

namespace ve {

Engine::Engine() {
  logFileStream = new FileOutputStream("./eengine.log");
  Log::getInstance()->addOutputStream(logFileStream);
}

Engine::~Engine() {
  logFileStream->close();
}

int Engine::getComponents(TextureFormat format) {
  switch (format) {
  case ALPHA16F:
  case ALPHA32F:
  case INTENSITY8:
  case INTENSITY16F:
  case INTENSITY32F:
  case LUMINANCE8:
  case LUMINANCE16F:
  case LUMINANCE32F:
    return 1;

  case LUMINANCE_ALPHA16F:
  case LUMINANCE_ALPHA32F:
    return 2;

  case RGB8:
  case BGR8:
  case RGB16F:
  case RGB32F:
  case RGB_DXT1:
    return 3;

  case RGBA8:
  case BGRA8:
  case RGBA_DXT1:
  case RGBA_DXT3:
  case RGBA_DXT5:
  case RGBA16F:
  case RGBA32F:
    return 4;

  default:
    EPIC_FAIL(L"Unsupported format");
  }
}

}
