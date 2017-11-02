// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_RENDER_BUFFER_H__
#define __VE_RENDER_BUFFER_H__

#include "engine/common.h"
#include "engine/textures/texture.h"

namespace ve {

class Engine;

/**
    Represents an area of pixels of some format that can be attached to a frame buffer object.
RenderBuffer class is a part of support of "EXT_framebuffer_object" OpenGL extension.

    Objects of RenderBuffer class must be created only through createRenderBuffer()
    function of Engine class.

    @see Engine::createRenderBuffer()
    @see FrameBuffer::attachRenderBuffer()
*/
class RenderBuffer {
private:
  /** Engine class created this render buffer */
  Engine *engine;

  /** Width of this render buffer */
  uint width;

  /** Height of this render buffer */
  uint height;

  /** Format of this render buffer */
  TextureFormat format;

  /**
      Handle that is used by Engine classes to store
      instance-specific data.
  */
  Handle handle;

public:
  /**
      Objects can be instantiated only by Engine
      class through Engine::createRenderBuffer() function.
      @param engine - pointer to engine object that creates this object.
      @param format - format of this render buffer.
      @param width - width of this render buffer.
      @param height - height of this render buffer.
  */
  RenderBuffer(Engine *engine, Handle handle, TextureFormat format, uint width, uint height);

  /**
      Render buffer destructor. Calls Engine::freeRenderBuffer() to free
      allocated resources.
  */
  ~RenderBuffer();

  /**
Returns width of this render buffer.
      @return Width of this render buffer.
  */
  uint getWidth();

  /**
Returns height of this render buffer.
      @return Height of this render buffer.
  */
  uint getHeight();

  /**
Returns format of this render buffer.
      @return Format of this render buffer.
      @see TextureFormat
  */
  TextureFormat getFormat();

  /**
Returns handle that is used by Engine class to store instance-specific data.
      @return Handle that is used by Engine class to store instance-specific data.
  */
  Handle getHandle();
};

}

#endif // __VE_RENDER_BUFFER_H__
