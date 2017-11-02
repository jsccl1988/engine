// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "buffers/render_buffer.h"
#include "engines/engine.h"

namespace ve {

RenderBuffer::RenderBuffer(Engine *engine, Handle handle, TextureFormat format, uint width, uint height) {
  this->engine = engine;
  this->format = format;
  this->width = width;
  this->height = height;
  this->handle = handle;
}

RenderBuffer::~RenderBuffer() {
  engine->freeRenderBuffer(this);
}

uint RenderBuffer::getWidth() {
  return width;
}

uint RenderBuffer::getHeight() {
  return height;
}

TextureFormat RenderBuffer::getFormat() {
  return format;
}

Handle RenderBuffer::getHandle() {
  return handle;
}

}
