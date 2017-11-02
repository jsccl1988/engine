// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "engines/gl_engine.h"
#include "textures/mips_impl.h"

namespace ve {

Outcome MIPsImpl::initialize(GLEngine *engine) {
  _glGenerateMipmap = (PFNGLGENERATEMIPMAPEXTPROC)engine->getProcAddress("glGenerateMipmap");
  CHECK_POINTER(_glGenerateMipmap);
  return OK;
}

void MIPsImpl::glGenerateMipmap(GLenum target) {
  _glGenerateMipmap(target);
}

}
