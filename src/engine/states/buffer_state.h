// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_BUFFERS_STATE_H__
#define __VE_BUFFERS_STATE_H__

namespace ve {

  /**
      Defines data buffer layout. If data pointer is NULL then buffer will be disabled during rendering.
  */
  struct BufferDesc {
    uint components;  //!< Number of components
    Type type;        //!< Type of each component
    uint stride;      //!< Distance between consequitive elements (or zero if they follow each other without gaps)
    void *data;       //!< Pointer to the data to set
    bool isVBO;       //!< Defines if data pointer points to Video Buffer ot just to an array in system memory

/**
  Buffer is disabled by default.
*/
    BufferDesc() {
      components = 3;
      type = FLOAT;
      stride = 0;
      data = 0;
      isVBO = true;
    }

    BufferDesc(uint components, Type type, uint stride, void* data, bool isVBO) {
      this->components = components;
      this->type = type;
      this->stride = stride;
      this->data = data;
      this->isVBO = isVBO;
    }
  };

  /**
      Defines state of the buffers during rendering. Set "data" member of BufferDesc
      structure to disable buffer.
  */
  struct BuffersState {
    BufferDesc indices;
    BufferDesc vertices;
    BufferDesc texCoords;
    BufferDesc normals;
  };

}

#endif // __VE_BUFFERS_STATE_H__
