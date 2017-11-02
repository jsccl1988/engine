// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "engines/gl_device_caps.h"
#include "engines/gl_engine.h"

namespace ve {

/**
    Default constructor. Do nothing.
*/
GLDeviceCaps::GLDeviceCaps(Engine *engine) :DeviceCaps(engine) {
}

/**
    Set extension that contains FBO fucntions.
    @param FBOFunctions - FBO extension to retrieve data from.
    @return OK if FBOFunctions is not NULL.
    @return NULL otherwise.
*/
Outcome GLDeviceCaps::setFBOFunctions(FBOExt *FBOFunctions) {
  CHECK_POINTER(FBOFunctions);

  this->FBOFunctions = FBOFunctions;

  return OK;
}

/**
    Checks if vertical synchronization is supported by the GPU.
    @return 'true' if vertical synchronization is supported and
    'false' otherwise.
*/
bool GLDeviceCaps::isVSyncSupported() {
#ifdef VE_WINDOWS
  return ((GLEngine*)engine)->isExtensionSupported("WGL_EXT_swap_control");
#endif
#ifdef VE_LINUX
  return ((GLEngine*)engine)->isExtensionSupported("GLX_SGI_video_sync");
#endif
}

/**
    Checks if anisotropic filtration is supported on GPU.
    @return true if anisotropic filtration is supported by GPU.
    @return false if anisotropic filtration is not supported by GPU.
*/
bool GLDeviceCaps::isAnisotropySupported() {
  return ((GLEngine*)engine)->isExtensionSupported("GL_EXT_texture_filter_anisotropic");
}

/**
    Checks if video buffer objects are supported by this GPU. More formally,
    it checks if GL_ARB_vertex_buffer_object extension is supported.
    @return true if VBOs are supported.
    @return false if VBO are not supported
*/
bool GLDeviceCaps::isVBOSupported() {
  return ((GLEngine*)engine)->isExtensionSupported("GL_ARB_vertex_buffer_object");
}

/**
    Checks if automatic mip-maps generation is supported by this GPU. More formally,
    it checks if SGIS_generate_mipmap extension is supported.
    @return true if mip-maps generation is supported.
    @return false if mip-maps generation is not supported
*/
bool GLDeviceCaps::isMipMapsSupported() {
  return ((GLEngine*)engine)->isExtensionSupported("SGIS_generate_mipmap");
}

/**
    Checks if frame buffer objects are supported by this GPU. More formally,
    it checks if EXT_framebuffer_object extension is supported.
    @return true if FBOs are supported.
    @return false if FBOs are not supported
*/
bool GLDeviceCaps::isFBOSupported() {
  return ((GLEngine*)engine)->isExtensionSupported("EXT_framebuffer_object");
}

/**
    Checks if GLSL is supported by this GPU.
    @return true if GLSL is supported.
    @return false if GLSL is not supported
*/
bool GLDeviceCaps::isGLSLSupported() {
  return ((GLEngine*)engine)->isExtensionSupported("GL_ARB_shading_language_100") &&
    ((GLEngine*)engine)->isExtensionSupported("GL_ARB_shader_objects") &&
    ((GLEngine*)engine)->isExtensionSupported("GL_ARB_vertex_shader") &&
    ((GLEngine*)engine)->isExtensionSupported("GL_ARB_fragment_shader");
}

/**
  Checks if multi-texturing is supported by this GPU.
  @return true if multi-texturing is supported.
  @return false if multi-texturing is supported.
*/
bool GLDeviceCaps::isMultiTextureSupported() {
  return ((GLEngine*)engine)->isExtensionSupported("ARB_multitexture");
}

/**
    Returns number of texture slots available on this GPU.
    @return Number of texture slots available on this GPU.
*/
int GLDeviceCaps::getTextureSlotsCount() {
  int maxTextureUnits = 0;
  glGetIntegerv(GL_MAX_TEXTURE_UNITS, &maxTextureUnits);
  return maxTextureUnits;
}

/**
    Returns maximum number of color attachments that can
    be attached to a frame buffer.
*/
int GLDeviceCaps::getMaxColorAttachments() {
  return FBOFunctions->getMaxColorAttachments();
}

/**
    Returns max level of anisotropic filtration that is supported on the GPU.
    @return Max level of anisotropic filtration that is supported on the GPU.
*/
float GLDeviceCaps::getMaxAnisotropy() {
  float maxLevel = 0.0;
  GL_SAFE_CALL(glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxLevel), 0.0);
  return maxLevel;
}

}
