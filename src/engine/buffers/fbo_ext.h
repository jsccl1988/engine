// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_FBO_EXT_H__
#define __VE_FBO_EXT_H__

#include "engine/common.h"

namespace ve {

class GLEngine;

/**
    This class was produced to add to GLEngine "Render to texture"
    ability. All the functions simply writes "Function is not implemented"
    to a log file. It contains only functions that were introduced
    in the "EXT_framebuffer_object" OpenGL extension.
    GLEngine uses object of this class to call frame buffer functions if "EXT_framebuffer_object"
    extension is not supported and object of FBOImpl class if this extension is supported by GPU.
    During initialization GLEngine decides if it should create instance
    of this class or instance of FBOImpl class. It depends on "EXT_framebuffer_object"
    extension support for GPU.

    This technique of extensions support will lead to safe calls even
    for functions not supported on GPU where executed.

    @see GLEngine::initialize()
    @see FBOImpl
*/
class FBOExt {
public:
  FBOExt();
  virtual ~FBOExt();

  /**
      Do nothing.
      @param engine - pointer to GLEngine object which wants to initialize
      extension.
      @return OK everytime.
  */
  virtual Outcome initialize(GLEngine *engine);
  virtual void glGenFramebuffers(GLsizei count, GLuint *ids);
  virtual void glDeleteFramebuffers(GLsizei count, GLuint *ids);
  virtual void glBindFramebuffer(GLenum target, GLuint id);
  virtual GLboolean glIsFramebuffer(GLuint id);
  virtual void glGenRenderbuffers(GLsizei count, GLuint *ids);
  virtual void glDeleteRenderbuffers(GLsizei count, GLuint *ids);
  virtual void glBindRenderbuffer(GLenum target, GLuint id);
  virtual GLboolean glIsRenderbuffer(GLuint id);
  virtual void glRenderbufferStorage(GLenum target, GLenum internalFormat, GLsizei width, GLsizei height);
  virtual void glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum rbTarget, GLuint rbId);
  virtual int getMaxColorAttachments();
  virtual void glFramebufferTexture1D(GLenum target, GLenum attachment, GLenum texTarget, GLuint texId, int level);
  virtual void glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum texTarget, GLuint texId, int level);
  virtual void glFramebufferTexture3D(GLenum target, GLenum attachment, GLenum texTarget, GLuint texId, int level, int zOffset);
  virtual GLenum glCheckFramebufferStatus(GLenum target);
};

}

#endif // __VE_FBO_EXT_H__
