// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "ext/multi_texture_impl.h"
#include "engines/gl_engine.h"

namespace ve {

/**
    Loads extension functions using GetProcAddress function of specified GLEngine object.
    @param engine - pointer to GLEngine object which wants to initialize
    extension.
    @return OK if all the functions were loaded correctly.
    @return NULL_POINTER if at least one function was not loaded successfully.
*/
Outcome MultiTextureImpl::initialize(GLEngine *engine) {
  _glActiveTexture = (PFNGLACTIVETEXTUREPROC)engine->getProcAddress("glActiveTextureARB");
  CHECK_POINTER(_glActiveTexture);

  return OK;
}

/**
  Selects active texture unit.
  @param texture - Specifies which texture unit to make active.
*/
void MultiTextureImpl::glActiveTexture(GLenum texture) {
  _glActiveTexture(texture);
}

}
