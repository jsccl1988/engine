// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_FBO_IMPL_H__
#define __VE_FBO_IMPL_H__

#include "engine/common.h"
#include "engine/buffers/fbo_ext.h"

namespace ve {

class GLEngine;

/**
    This class was produced to add to GLEngine "Render to texture"
    ability. All the functions simply calls OpenGL functions with the same
    names. It contains only functions introduced
    in the "EXT_framebuffer_object" OpenGL extension.
    GLEngine uses object of this class to call frame buffer functions if "EXT_framebuffer_object"
    extension is supported and object of FBOExt class if this extension is not supported.
    During initialization GLEngine decides if it should create an instance
    of this class or an instance of FBOExt class. It depends on "EXT_framebuffer_object"
    extension support for GPU.

    This technique of extensions support will lead to safe calls even
    for functions not supported on GPU where executed.

    @see GLEngine::initialize()
    @see FBOExt
*/
class FBOImpl : public FBOExt {
private:
  PFNGLGENFRAMEBUFFERSEXTPROC _glGenFramebuffers;
  PFNGLDELETEFRAMEBUFFERSEXTPROC _glDeleteFramebuffers;
  PFNGLBINDFRAMEBUFFEREXTPROC _glBindFramebuffer;
  PFNGLISFRAMEBUFFEREXTPROC _glIsFramebuffer;
  PFNGLGENRENDERBUFFERSEXTPROC _glGenRenderbuffers;
  PFNGLDELETERENDERBUFFERSEXTPROC _glDeleteRenderbuffers;
  PFNGLBINDRENDERBUFFEREXTPROC _glBindRenderbuffer;
  PFNGLISRENDERBUFFEREXTPROC _glIsRenderbuffer;
  PFNGLRENDERBUFFERSTORAGEEXTPROC _glRenderbufferStorage;
  PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC _glFramebufferRenderbuffer;
  PFNGLFRAMEBUFFERTEXTURE1DEXTPROC _glFramebufferTexture1D;
  PFNGLFRAMEBUFFERTEXTURE2DEXTPROC _glFramebufferTexture2D;
  PFNGLFRAMEBUFFERTEXTURE3DEXTPROC _glFramebufferTexture3D;
  PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC _glCheckFramebufferStatus;

public:
  FBOImpl();
  virtual ~FBOImpl();

  /**
      Loads extension functions using GetProcAddress function of specified GLEngine object.
      @param engine - pointer to GLEngine object which wants to initialize
      extension.
      @return OK if all the functions were loaded correctly.
      @return NULL_POINTER if at least one function was not loaded successfully.
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

#endif // __VE_FBO_IMPL_H__
