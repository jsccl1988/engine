// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "common.h"
#include "ext/multi_texture_ext.h"

namespace ve {

/**
    Do nothing.
    @param engine - pointer to GLEngine object which wants to initialize
    extension.
    @return OK everytime.
*/
Outcome MultiTextureExt::initialize(GLEngine *engine) {
  return OK;
}

/**
  Selects active texture unit.
  @param texture - Specifies which texture unit to make active.
*/
void MultiTextureExt::glActiveTexture(GLenum texture) {
  UNIMPLEMENTED();
}

}
