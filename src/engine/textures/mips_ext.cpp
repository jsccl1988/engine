// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "textures/mips_ext.h"

namespace ve {

Outcome MIPsExt::initialize(GLEngine *engine) {
  return OK;
}

void MIPsExt::glGenerateMipmap(GLenum target) {
  UNIMPLEMENTED();
}

}
