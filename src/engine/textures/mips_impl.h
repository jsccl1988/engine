// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_MIPS_IMPL_H__
#define __VE_MIPS_IMPL_H__

#include "engine/common.h"
#include "engine/textures/mips_ext.h"

namespace ve {

/**
    This class was produced to add to GLEngine "MIP levels autogeneration"
    ability. glGenerateMipmap simply calls the same function from OpenGL library.
    This class contains only function which was introduced
    in the "SGIS_generate_mipmap" OpenGL extension.
    GLEngine uses this class to generate MIP levels if "SGIS_generate_mipmap"
    extension is supported and uses MIPsExt class if this extension is not supported by GPU.
    During initialization GLEngine decides if it should create instance
    of this class or instance of MIPsExt class. It depends on "SGIS_generate_mipmap"
    extension support for GPU.

    This technique of extensions support will lead to safe calls even
    for functions which are not supported on GPU where executed.

    @see GLEngine::initialize()
*/
class MIPsImpl : public MIPsExt {
private:
  PFNGLGENERATEMIPMAPEXTPROC _glGenerateMipmap;

public:
  /**
      Loads extension functions using GetProcAddress function of specified GLEngine object.
      @param engine - pointer to GLEngine object which wants to initialize
      extension.
      @return OK if all the functions were loaded correctly.
      @return NULL_POINTER if at least one function was not loaded successfully.
  */
  virtual Outcome initialize(GLEngine *engine);
  virtual void glGenerateMipmap(GLenum target);
};

}

#endif // __VE_MIPS_IMPL_H__
