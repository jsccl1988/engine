// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "buffers/vbo_impl.h"
#include "engines/gl_engine.h"

namespace ve {

VBOImpl::VBOImpl() :VBOExt() {
}

VBOImpl::~VBOImpl() {
}

Outcome VBOImpl::initialize(GLEngine *engine) {
  _glGenBuffers = (PFNGLGENBUFFERSPROC)engine->getProcAddress("glGenBuffersARB");
  _glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)engine->getProcAddress("glDeleteBuffersARB");
  _glBindBuffer = (PFNGLBINDBUFFERPROC)engine->getProcAddress("glBindBufferARB");
  _glBufferData = (PFNGLBUFFERDATAPROC)engine->getProcAddress("glBufferDataARB");
  _glMapBuffer = (PFNGLMAPBUFFERPROC)engine->getProcAddress("glMapBufferARB");
  _glUnmapBuffer = (PFNGLUNMAPBUFFERPROC)engine->getProcAddress("glUnmapBufferARB");
  _glGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC)engine->getProcAddress("glGetBufferParameterivARB");

  ERROR_IF(_glGenBuffers == 0 || _glDeleteBuffers == 0 || _glBindBuffer == 0 || _glBufferData == 0 ||
    _glMapBuffer == 0 || _glUnmapBuffer == 0 || _glGetBufferParameteriv == 0, L"VBO is not supported", ERROR);

  return OK;
}

void VBOImpl::glGenBuffers(GLsizei count, GLuint *handle) {
  _glGenBuffers(count, handle);
}

void VBOImpl::glDeleteBuffers(GLsizei count, const GLuint *handle) {
  _glDeleteBuffers(count, handle);
}

void VBOImpl::glBindBuffer(GLenum target, GLuint handle) {
  _glBindBuffer(target, handle);
}

void VBOImpl::glBufferData(GLenum target, GLsizeiptr size, GLvoid *data, GLenum method) {
  _glBufferData(target, size, data, method);
}

void* VBOImpl::glMapBuffer(GLenum target, GLenum access) {
  return _glMapBuffer(target, access);
}

GLboolean VBOImpl::glUnmapBuffer(GLenum target) {
  return _glUnmapBuffer(target);
}

void VBOImpl::glGetBufferParameteriv(GLenum target, GLenum param, GLint *value) {
  _glGetBufferParameteriv(target, param, value);
}

}

