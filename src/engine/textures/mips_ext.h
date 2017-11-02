// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_MIPS_EXT_H__
#define __VE_MIPS_EXT_H__

#include "engine/common.h"

namespace ve {

class GLEngine;

/**
    This class was produced to add to GLEngine "MIP levels autogeneration"
    ability. glGenerateMipmap function simply writes "Function is not implemented"
    to a log file. This class contains only function which was introduced
    in the "SGIS_generate_mipmap" OpenGL extension.
    GLEngine uses this class to generate MIP levels if "SGIS_generate_mipmap"
    extension is not supported and uses MIPsImpl class if this extension is supported by GPU.
    During initialization GLEngine decides if it should create instance
    of this class or instance of MIPsImpl class. It depends on "SGIS_generate_mipmap"
    extension support for GPU.

    This technique of extensions support will lead to safe calls even
    for functions which are not supported on GPU where executed.

    @see GLEngine::initialize()
*/
class MIPsExt {
public:
  /**
      Do nothing.
      @param engine - pointer to GLEngine object which wants to initialize
      extension.
      @return OK everytime.
  */
  virtual Outcome initialize(GLEngine *engine);
  virtual void glGenerateMipmap(GLenum target);
};

}

#endif // __VE_MIPS_EXT_H__
