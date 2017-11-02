// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "common.h"
#include "buffers/video_buffer.h"
#include "engines/engine.h"

namespace ve {

VideoBuffer::VideoBuffer(Engine *engine, Handle handle, Array type) {
  this->engine = engine;
  this->handle = handle;
  this->type = type;
}

VideoBuffer::~VideoBuffer() {
  engine->freeBuffer(this);
}

Outcome VideoBuffer::update(void *data, unsigned int size, VideoBufferStoreMethod method) {
  if (type == INDEX_ARRAY) {
    CHECK_RESULT(engine->updateIndexBuffer(this, data, size, method), L"Update Buffer failed");
  } else {
    CHECK_RESULT(engine->updateBuffer(this, data, size, method), L"Update Buffer failed");
  }
  return OK;
}

void* VideoBuffer::map(AccessType access) {
  if (type == INDEX_ARRAY) {
    return engine->mapIndexBuffer(this, access);
  } else {
    return engine->mapBuffer(this, access);
  }
}

Outcome VideoBuffer::unmap() {
  if (type == INDEX_ARRAY) {
    CHECK_RESULT(engine->unmapIndexBuffer(this), L"Unmap failed");
  } else {
    CHECK_RESULT(engine->unmapBuffer(this), L"Unmap failed");
  }
  return OK;
}

Handle VideoBuffer::getHandle() {
  return handle;
}

Array VideoBuffer::getType() {
  return type;
}

}
