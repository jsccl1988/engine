// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "buffers/vbo_ext.h"

namespace ve {

VBOExt::VBOExt() {
}

VBOExt::~VBOExt() {
}

Outcome VBOExt::initialize(GLEngine *engine) {
  return OK;
}

void VBOExt::glGenBuffers(GLsizei count, GLuint *handle) {
  UNIMPLEMENTED();
}

void VBOExt::glDeleteBuffers(GLsizei count, const GLuint *handle) {
  UNIMPLEMENTED();
}

void VBOExt::glBindBuffer(GLenum target, GLuint handle) {
  UNIMPLEMENTED();
}

void VBOExt::glBufferData(GLenum target, GLsizeiptr size, GLvoid *data, GLenum method) {
  UNIMPLEMENTED();
}

void* VBOExt::glMapBuffer(GLenum target, GLenum access) {
  UNIMPLEMENTED();
  return NULL;
}

GLboolean VBOExt::glUnmapBuffer(GLenum target) {
  UNIMPLEMENTED();
  return GL_FALSE;
}

void VBOExt::glGetBufferParameteriv(GLenum target, GLenum param, GLint *value) {
  UNIMPLEMENTED();
}

}
