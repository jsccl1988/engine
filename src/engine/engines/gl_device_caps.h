// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_GL_DEVICE_CAPS_H__
#define __VE_GL_DEVICE_CAPS_H__

#include "engine/common.h"
#include "engine/engines/device_caps.h"
#include "engine/buffers/fbo_ext.h"

namespace ve {

/**
    OpenGL implementation of DevCaps class.
    Provides access for device capabilities. Use this class to check
    support of different features and to retrieve GPU constants like
    number of texture slots and so on.
*/
class GLDeviceCaps : public DeviceCaps {
private:
  FBOExt *FBOFunctions;

public:
  /**
      Default constructor. Does nothing.
  */
  GLDeviceCaps(Engine *engine);

  /**
      Sets extension that contains FBO fucntions.
      @param FBOFunctions - FBO extension to retrieve data from.
      @return OK if FBOFunctions is not NULL.
      @return NULL otherwise.
  */
  Outcome setFBOFunctions(FBOExt *FBOFunctions);

  /**
      Checks if vertical synchronization is supported by GPU.
      @return 'true' if vertical synchronization is supported and
      'false' otherwise.
  */
  virtual bool isVSyncSupported();

  /**
      Checks if anisotropic filtration is supported by GPU.
      @return true if anisotropic filtration is supported by GPU.
      @return false if anisotropic filtration is not supported by GPU.
  */
  virtual bool isAnisotropySupported();

  /**
      Checks if video buffer objects are supported by this GPU. More formally,
      it checks if GL_ARB_vertex_buffer_object extension is supported.
      @return true if VBOs are supported.
      @return false if VBO are not supported
  */
  virtual bool isVBOSupported();

  /**
      Checks if automatic mip-maps generation is supported by this GPU. More formally,
      it checks if SGIS_generate_mipmap extension is supported.
      @return true if mip-maps generation is supported.
      @return false if mip-maps generation is not supported
  */
  virtual bool isMipMapsSupported();

  /**
      Checks if frame buffer objects are supported by this GPU. More formally,
      it checks if EXT_framebuffer_object extension is supported.
      @return true if FBOs are supported.
      @return false if FBOs are not supported
  */
  virtual bool isFBOSupported();

  /**
      Checks if GLSL is supported by this GPU.
      @return true if GLSL is supported.
      @return false if GLSL is not supported
  */
  virtual bool isGLSLSupported();

  /**
    Checks if multi-texturing is supported by this GPU.
    @return true if multi-texturing is supported.
    @return false if multi-texturing is supported.
  */
  virtual bool isMultiTextureSupported();

  /**
      Returns number of available texture slots available on this GPU.
      @return Number of available texture slots available on this GPU.
  */
  virtual int getTextureSlotsCount();

  /**
      Returns maximal number of color attachments that can
      be attached to a frame buffer.
  */
  virtual int getMaxColorAttachments();

  /**
      Returns maximal level of anisotropic filtration that is supported on the GPU.
      @return Maximal level of anisotropic filtration that is supported on the GPU.
  */
  virtual float getMaxAnisotropy();

};

}

#endif // __VE_GL_DEVICE_CAPS_H__
