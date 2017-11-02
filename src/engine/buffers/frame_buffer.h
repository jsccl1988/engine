// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_FRAME_BUFFER_H__
#define __VE_FRAME_BUFFER_H__

#include "engine/common.h"
#include "engine/buffers/render_buffer.h"

namespace ve {

class Engine;

/**
    FrameBuffer class introduces support
    of OpenGL "EXT_framebuffer_object" extension. It means that if
    GPU supports this extension Engine classes will be able to create
    FrameBuffer objects. They are usually used for off-screen rendering.
    Rendering of refraction maps, mirrors effects can be done only with
    ability to render in a off-screen surfaces (textures). This class also
    provides support for procedural textures. With FrameBuffer textures
    can be generated 'on-a-fly'. During one draw command several
    textures can be produced.

    Font rendering system in VR Engine works through this mechanism
    to render symbols in a texture and then uses it (texture) as a cache
    of already rendered symbols.

    Standard workflow for FrameBuffer objects:
    <ul>
    <li> Create FrameBuffer object.</li>
    <li> Attach RenderBuffers or Textures.</li>
    <li> Bind FrameBuffer and set render settings.</li>
    <li> Render something.</li>
    <li> Unbind FrameBuffer.</li>
    </ul>

    Instances of this class must be created only through createFrameBuffer()
    calls of Engine class objects.

    @see Engine::createFrameBuffer()
*/
class FrameBuffer {
private:
  /**
      Engine created this instance.
  */
  Engine *engine;

  /**
      Handle that is used only by Engine class to store instance-specific
      information.
  */
  Handle handle;

public:
  /**
      FrameBuffer constructor. It is used only by Engine classes.
      You should create FrameBuffer classes only through createFrameBuffer()
      function of Engine objects.
      @param engine - Engine that creates object
      @param handle - Handle for storing instance-specific information in Engine class.
      @see Engine::createFrameBuffer()
  */
  FrameBuffer(Engine *engine, Handle handle);

  /**
      FrameBuffer destructor. It calls freeFrameBuffer() function of Engine class
      to free allocated resources.
  */
  ~FrameBuffer();

  /**
      Binds this FrameBuffer to the pipeline. Following draw commands will render
      to this FrameBuffer. No special influence on render settings.
      @return OK if operation succeeded.
      @return ERROR in case of internal error.
  */
  Outcome bind();

  /**
      Switches rendering back to default frame buffer that was created
      during window creation.
      @return OK if operation succeeded.
      @return ERROR in case of internal error.
  */
  Outcome unbind();

  /**
      Checks status of frame buffer that is currently bound to the pipeline.
      Highly recommended to use this function before rendering to be sure that all
      formats are supported and engine is ready to render to this frame
      buffer.
      @return FrameBufferStatus constant.
      @see FrameBufferStatus
  */
  FrameBufferStatus checkStatus();

  /**
      Attaches render buffer to this frame buffer.
      @param renderBuffer - pointer to render buffer object which
      should be attached to this frame buffer.
      @param slot - RenderBufferSlot constant that defines how this
      render buffer will be used.
      @return OK if operation succeeded.
      @return NULL_POINTER if renderBuffer is NULL.
      @return ERROR in case of incorrect slot or internal error.
      @see RenderBuffer
      @see RenderBufferSlot
  */
  Outcome attachRenderBuffer(RenderBuffer *renderBuffer, RenderBufferSlot slot);

  /**
      Attaches texture to this frame buffer.
      @param texture2D - pointer to Texture object which
      should be attached to this frame buffer.
      @param slot - RenderBufferSlot constant that defines how this
      texture will be used.
      @return OK if operation succeeded.
      @return NULL_POINTER if texture2D is NULL.
      @return ERROR in case of incorrect slot or internal error.
      @see Texture
      @see RenderBufferSlot
  */
  Outcome attachTexture2D(Texture *texture2D, RenderBufferSlot slot);

  /**
      Returns handle that is used by Engine classes to store
      instance-specific information.
      @return handle that is used inside Engine classes.
  */
  Handle getHandle();
};

}

#endif // VE_FRAME_BUFFER_H__
