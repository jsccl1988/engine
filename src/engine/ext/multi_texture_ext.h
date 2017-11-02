// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_MULTI_TEXTURE_EXT_H__
#define __VE_MULTI_TEXTURE_EXT_H__

#include "engine/common.h"

namespace ve {

class GLEngine;

/**
    This class was produced to add to GLEngine "Multi-texture rendering"
    ability. All the functions simply writes "Function is not implemented"
    to a log file. It contains only functions which were introduced
    in the "ARB_multitexture" OpenGL extension.
    GLEngine uses this class to call extension functions if "ARB_multitexture"
    extension is not supported and MultiTextureImpl class if this extension is supported by GPU.
    During initialization GLEngine decides if it should create instance
    of this class or instance of MultiTextureImpl class. It depends on "ARB_multitexture"
    extension support for GPU.

    This technique of extensions support will lead to safe calls even
    for functions which are not supported on GPU where executed.

    @see GLEngine::initialize()
    @see MultiTextureImpl
*/
class MultiTextureExt {
public:

  /**
      Do nothing.
      @param engine - pointer to GLEngine object which wants to initialize
      extension.
      @return OK everytime.
  */
  virtual Outcome initialize(GLEngine *engine);

  /**
    Selects active texture unit.
    @param texture - Specifies which texture unit to make active.
  */
  virtual void glActiveTexture(GLenum texture);

};

}

#endif // __VE_MULTI_TEXTURE_EXT_H__
