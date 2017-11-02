// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "buffers/frame_buffer.h"
#include "engines/engine.h"

namespace ve {

FrameBuffer::FrameBuffer(Engine *engine, Handle handle) {
  this->engine = engine;
  this->handle = handle;
}

FrameBuffer::~FrameBuffer() {
  engine->freeFrameBuffer(this);
}

Outcome FrameBuffer::bind() {
  return engine->bindFrameBuffer(this);
}

Outcome FrameBuffer::unbind() {
  return engine->unbindFrameBuffer();
}

FrameBufferStatus FrameBuffer::checkStatus() {
  return engine->checkFrameBufferStatus();
}

Outcome FrameBuffer::attachRenderBuffer(RenderBuffer *renderBuffer, RenderBufferSlot slot) {
  return engine->attachRenderBuffer(this, renderBuffer, slot);
}

Outcome FrameBuffer::attachTexture2D(Texture *texture2D, RenderBufferSlot slot) {
  return engine->attachTexture(this, texture2D, slot);
}

Handle FrameBuffer::getHandle() {
  return handle;
}

}
