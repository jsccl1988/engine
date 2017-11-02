// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_MULTI_TEXTURE_IMPL_H__
#define __VE_MULTI_TEXTURE_IMPL_H__

#include "engine/ext/multi_texture_ext.h"

namespace ve {

class GLEngine;

/**
    This class was produced to add to GLEngine "Multi-texture rendering"
    ability. All the functions simply calls native OpenGL functions.
    It contains only functions which were introduced in the "ARB_multitexture" OpenGL extension.
    GLEngine uses this class to call extension functions if "ARB_multitexture"
    extension is supported and MultiTextureExt class if this extension is not supported by GPU.
    During initialization GLEngine decides if it should create instance
    of this class or instance of MultiTextureImpl class. It depends on "ARB_multitexture"
    extension support for GPU.

    This technique of extensions support will lead to safe calls even
    for functions which are not supported on GPU where executed.

    @see GLEngine::initialize()
    @see MultiTextureExt
*/
class MultiTextureImpl : public MultiTextureExt {
private:
  PFNGLACTIVETEXTUREPROC _glActiveTexture;

public:

  /**
    Loads extension functions using GetProcAddress function of specified GLEngine object.
    @param engine - pointer to GLEngine object which wants to initialize
    extension.
    @return OK if all the functions were loaded correctly.
      @return NULL_POINTER if at least one function was not loaded successfully.
    */
  virtual Outcome initialize(GLEngine *engine);

  /**
    Selects active texture unit.
    @param texture - Specifies which texture unit to make active.
  */
  virtual void glActiveTexture(GLenum texture);

};

}

#endif // __VE_MULTI_TEXTURE_IMPL_H__
