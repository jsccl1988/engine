// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_VBOIMPL_H__
#define __VE_VBOIMPL_H__

#include "engine/common.h"
#include "engine/buffers/vbo_ext.h"

namespace ve {

/**
    This class was introduced to add to GLEngine "ARB_vertex_buffer_object"
    extension support. All the functions simply calls OpenGL functions with the same
    names. It contains only functions introduced in the
    "ARB_vertex_buffer_object" OpenGL extension.
    GLEngine uses object of this class to call video buffer functions if "ARB_vertex_buffer_object"
    extension is supported and object of VBOExt class if this extension is not supported.
    During initialization GLEngine decides if it should create an instance
    of this class or an instance of VBOExt class. It depends on "ARB_vertex_buffer_object"
    extension support by GPU.

    This technique of extensions support will lead to safe calls even
    for functions not supported by GPU.

    @see GLEngine::initialize()
    @see VBOExt
    @see VideoBuffer
*/
class VBOImpl : public VBOExt {
private:
  PFNGLGENBUFFERSPROC		_glGenBuffers;
  PFNGLDELETEBUFFERSPROC	_glDeleteBuffers;
  PFNGLBINDBUFFERPROC		_glBindBuffer;
  PFNGLBUFFERDATAPROC		_glBufferData;
  PFNGLMAPBUFFERPROC      _glMapBuffer;
  PFNGLUNMAPBUFFERPROC    _glUnmapBuffer;
  PFNGLGETBUFFERPARAMETERIVPROC _glGetBufferParameteriv;

public:
  VBOImpl();
  virtual ~VBOImpl();

  /**
      Loads "ARB_vertex_buffer_object" extension functions using GetProcAddress
      function of specified GLEngine object.
      @param engine - pointer to GLEngine object to initialize extension.
      @return OK if all the functions were loaded correctly.
      @return NULL_POINTER if at least one function was not loaded successfully.
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

#endif // __VE_VBOIMPL_H__
