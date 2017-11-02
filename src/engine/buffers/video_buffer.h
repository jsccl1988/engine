// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_VIDEO_BUFFER_H__
#define __VE_VIDEO_BUFFER_H__

#include "engine/common.h"

/** @file eeVideoBuffer.h */

namespace ve {

class Engine;

/**
    Specifies type of video buffer array.
*/
enum Array {
  TEXTURE_COORD_ARRAY,    /*!< Texture coordinates array. */
  COLOR_ARRAY,            /*!< Color values array.        */
  INDEX_ARRAY,            /*!< Array of indices.          */
  NORMAL_ARRAY,           /*!< Array of normals.          */
  VERTEX_ARRAY            /*!< Vertex coordiantes array.  */
};

/**
    This enum specifies usage method, which would
    help driver to manager buffer location.
*/
enum VideoBufferStoreMethod {
  STATIC_DRAW,
  STATIC_READ,
  STATIC_COPY,
  DYNAMIC_DRAW,
  DYNAMIC_READ,
  DYNAMIC_COPY,
  STREAM_DRAW,
  STREAM_READ,
  STREAM_COPY
};

/**
    Video Buffer objects represents memory blocks on GPU-side.
    They are usually used to store geometry data in video memory
    to reduce bandwidth. This class allows allocate video memory,
    upload, download & modify data.

    <b>Note:</b> Video Buffer objects must be created only
    through Engine::createVideoBuffer() calls.
*/
class VideoBuffer {
private:
  /**
      Engine class created this video buffer.
  */
  Engine *engine;

  /**
      Engine defined handle that is used to store
      instance-specific data.
  */
  Handle handle;

  /**
      Type of array to specify what kind of data it contains.
      @see Array
  */
  Array type;

public:
  /**
      VideoBuffer constructor. Use Engine::createVideoBuffer() to create
      an instance of VideoBuffer class.
      @param engine - pointer to Engine class that creates this instance.
      @param handle - instance-specific handle that is used by Engine class.
      @param newType - type of data this buffer will contain.
  */
  VideoBuffer(Engine *engine, Handle handle, Array newType = VERTEX_ARRAY);

  /**
      VideoBuffer destructor. Calls Engine::freeVideoBuffer() function to
      free allocated resources.
  */
  virtual ~VideoBuffer();

  /**
      Uploads data from system memory to video buffer.
      @param data - pointer to data block to upload to VBO.
      @param size - size of data to upload.
      @param method - defines usage of this buffer. It helps OpenGL driver
      to manage this video buffer efficiently.
      @return OK if operation succeeded.
      @return NULL_POINTER if data pointer is NULL.
      @return INVALID_ENUM if method param is incorrect.
      @return ERROR in case of engine error or OpenGL error.
      @see VideoBufferStoreMethod
  */
  virtual Outcome update(void *data, unsigned int size, VideoBufferStoreMethod method);

  /**
      Maps GPU video memory to system memory. This
      function allows you to get an access to buffer data
      in system memory to modify it and then send it
      back again to GPU memory.
      @param access - specifies access you need.
      @return pointer to a system memory block that contains
      video buffer data.
      @return NULL if access type is incorrect or engine error
      occurred.
      @see AccessType
  */
  virtual void* map(AccessType access);

  /**
      This command sends mapped & modified data back to GPU memory.
      @return OK if operation succeeded.
      @return ERROR in case of engine error.
  */
  virtual Outcome unmap();

  /**
      Returns handle that is used by Engine class to store
      instance-specific information.
      @return Instance handle.
  */
  Handle getHandle();

  /**
      Returns array type that describes a kind of data it contains.
      @return Array type.
      @see Array
  */
  Array getType();
};

}

#endif // __VE_VIDEO_BUFFER_H__
