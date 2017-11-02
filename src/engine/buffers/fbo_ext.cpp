// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "buffers/fbo_ext.h"

namespace ve {

FBOExt::FBOExt() {
}

FBOExt::~FBOExt() {
}

Outcome FBOExt::initialize(GLEngine *engine) {
  return OK;
}

void FBOExt::glGenFramebuffers(GLsizei count, GLuint *ids) {
  UNIMPLEMENTED();
}

void FBOExt::glDeleteFramebuffers(GLsizei count, GLuint *ids) {
  UNIMPLEMENTED();
}

void FBOExt::glBindFramebuffer(GLenum target, GLuint id) {
  UNIMPLEMENTED();
}

GLboolean FBOExt::glIsFramebuffer(GLuint id) {
  UNIMPLEMENTED();
  return false;
}

void FBOExt::glGenRenderbuffers(GLsizei count, GLuint *ids) {
  UNIMPLEMENTED();
}

void FBOExt::glDeleteRenderbuffers(GLsizei count, GLuint *ids) {
  UNIMPLEMENTED();
}

void FBOExt::glBindRenderbuffer(GLenum target, GLuint id) {
  UNIMPLEMENTED();
}

GLboolean FBOExt::glIsRenderbuffer(GLuint id) {
  UNIMPLEMENTED();
  return false;
}

void FBOExt::glRenderbufferStorage(GLenum target, GLenum internalFormat, GLsizei width, GLsizei height) {
  UNIMPLEMENTED();
}

void FBOExt::glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum rbTarget, GLuint rbId) {
  UNIMPLEMENTED();
}

int FBOExt::getMaxColorAttachments() {
  UNIMPLEMENTED();
  return 0;
}

void FBOExt::glFramebufferTexture1D(GLenum target, GLenum attachment, GLenum texTarget, GLuint texId, int level) {
  UNIMPLEMENTED();
}

void FBOExt::glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum texTarget, GLuint texId, int level) {
  UNIMPLEMENTED();
}

void FBOExt::glFramebufferTexture3D(GLenum target, GLenum attachment, GLenum texTarget, GLuint texId, int level, int zOffset) {
  UNIMPLEMENTED();
}

GLenum FBOExt::glCheckFramebufferStatus(GLenum target) {
  UNIMPLEMENTED();
  return 0;
}

}
