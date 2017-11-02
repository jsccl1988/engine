// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "buffers/fbo_impl.h"
#include "engines/gl_engine.h"

namespace ve {

FBOImpl::FBOImpl() {
}

FBOImpl::~FBOImpl() {
}

Outcome FBOImpl::initialize(GLEngine *engine) {
  _glGenFramebuffers = (PFNGLGENFRAMEBUFFERSEXTPROC)engine->getProcAddress("glGenFramebuffersEXT");
  CHECK_POINTER(_glGenFramebuffers);

  _glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSEXTPROC)engine->getProcAddress("glDeleteFramebuffersEXT");
  CHECK_POINTER(_glDeleteFramebuffers);

  _glBindFramebuffer = (PFNGLBINDFRAMEBUFFEREXTPROC)engine->getProcAddress("glBindFramebufferEXT");
  CHECK_POINTER(_glBindFramebuffer);

  _glIsFramebuffer = (PFNGLISFRAMEBUFFEREXTPROC)engine->getProcAddress("glIsFramebufferEXT");
  CHECK_POINTER(_glIsFramebuffer);

  _glGenRenderbuffers = (PFNGLGENRENDERBUFFERSEXTPROC)engine->getProcAddress("glGenRenderbuffersEXT");
  CHECK_POINTER(_glGenRenderbuffers);

  _glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSEXTPROC)engine->getProcAddress("glDeleteRenderbuffersEXT");
  CHECK_POINTER(_glDeleteRenderbuffers);

  _glBindRenderbuffer = (PFNGLBINDRENDERBUFFEREXTPROC)engine->getProcAddress("glBindRenderbufferEXT");
  CHECK_POINTER(_glBindRenderbuffer);

  _glIsRenderbuffer = (PFNGLISRENDERBUFFEREXTPROC)engine->getProcAddress("glIsRenderbufferEXT");
  CHECK_POINTER(_glIsRenderbuffer);

  _glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEEXTPROC)engine->getProcAddress("glRenderbufferStorageEXT");
  CHECK_POINTER(_glRenderbufferStorage);

  _glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC)engine->getProcAddress("glFramebufferRenderbufferEXT");
  CHECK_POINTER(_glFramebufferRenderbuffer);

  _glFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DEXTPROC)engine->getProcAddress("glFramebufferTexture1D");
  CHECK_POINTER(_glFramebufferTexture1D);

  _glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DEXTPROC)engine->getProcAddress("glFramebufferTexture2D");
  CHECK_POINTER(_glFramebufferTexture2D);

  _glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DEXTPROC)engine->getProcAddress("glFramebufferTexture3D");
  CHECK_POINTER(_glFramebufferTexture3D);

  _glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC)engine->getProcAddress("glCheckFramebufferStatusEXT");
  CHECK_POINTER(_glCheckFramebufferStatus);

  return OK;
}

void FBOImpl::glGenFramebuffers(GLsizei count, GLuint *ids) {
  _glGenFramebuffers(count, ids);
}

void FBOImpl::glDeleteFramebuffers(GLsizei count, GLuint *ids) {
  _glDeleteFramebuffers(count, ids);
}

void FBOImpl::glBindFramebuffer(GLenum target, GLuint id) {
  _glBindFramebuffer(target, id);
}

GLboolean FBOImpl::glIsFramebuffer(GLuint id) {
  return _glIsFramebuffer(id);
}

void FBOImpl::glGenRenderbuffers(GLsizei count, GLuint *ids) {
  _glGenRenderbuffers(count, ids);
}

void FBOImpl::glDeleteRenderbuffers(GLsizei count, GLuint *ids) {
  _glDeleteRenderbuffers(count, ids);
}

void FBOImpl::glBindRenderbuffer(GLenum target, GLuint id) {
  _glBindRenderbuffer(target, id);
}

GLboolean FBOImpl::glIsRenderbuffer(GLuint id) {
  return _glIsRenderbuffer(id);
}

void FBOImpl::glRenderbufferStorage(GLenum target, GLenum internalFormat, GLsizei width, GLsizei height) {
  _glRenderbufferStorage(target, internalFormat, width, height);
}

void FBOImpl::glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum rbTarget, GLuint rbId) {
  _glFramebufferRenderbuffer(target, attachment, rbTarget, rbId);
}

int FBOImpl::getMaxColorAttachments() {
  int maxColors = 0;
  glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS_EXT, &maxColors);
  return maxColors;
}

void FBOImpl::glFramebufferTexture1D(GLenum target, GLenum attachment, GLenum texTarget, GLuint texId, int level) {
  _glFramebufferTexture1D(target, attachment, texTarget, texId, level);
}

void FBOImpl::glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum texTarget, GLuint texId, int level) {
  _glFramebufferTexture2D(target, attachment, texTarget, texId, level);
}

void FBOImpl::glFramebufferTexture3D(GLenum target, GLenum attachment, GLenum texTarget, GLuint texId, int level, int zOffset) {
  _glFramebufferTexture3D(target, attachment, texTarget, texId, level, zOffset);
}

GLenum FBOImpl::glCheckFramebufferStatus(GLenum target) {
  return _glCheckFramebufferStatus(target);
}

}
