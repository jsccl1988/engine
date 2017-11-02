// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_VBOEXT_H__
#define __VE_VBOEXT_H__

#include "engine/common.h"

namespace ve {

class GLEngine;

/**
    This class was introduced to add to GLEngine support of Video Buffer Objects.
    All the functions simply writes "Function is not implemented"
    to a log file. It contains only functions introduced
    in the "ARB_vertex_buffer_object" OpenGL extension.
    GLEngine uses object of this class to call video buffer related functions if "ARB_vertex_buffer_object"
    extension is not supported and object of VBOImpl class if this extension is supported by GPU.
    During initialization GLEngine decides if it should create an instance
    of this class or an instance of VBOImpl class. It depends on "ARB_vertex_buffer_object"
    extension support by GPU.

    This technique of extensions support will lead to safe calls even
    for functions not supported on GPU where executed.

    @see GLEngine::initialize()
    @see VBOImpl
    @see VideoBuffer
*/
class VBOExt {
public:
  VBOExt();
  virtual ~VBOExt();

  /**
      Do nothing.
      @param engine - pointer to GLEngine object that is used to initialize
      extension.
      @return OK everytime.
  */
  virtual Outcome initialize(GLEngine *engine);
  virtual void glGenBuffers(GLsizei count, GLuint *handle);
  virtual void glDeleteBuffers(GLsizei count, const GLuint *handle);
  virtual void glBindBuffer(GLenum target, GLuint handle);
  virtual void glBufferData(GLenum target, GLsizeiptr size, GLvoid *data, GLenum method);
  virtual void* glMapBuffer(GLenum target, GLenum access);
  virtual GLboolean glUnmapBuffer(GLenum target);
  virtual void glGetBufferParameteriv(GLenum target, GLenum param, GLint *value);
};

}

#endif // __VE_VBOEXT_H__
