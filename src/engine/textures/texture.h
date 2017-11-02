// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_TEXTURE_H__
#define __VE_TEXTURE_H__

#include <string>

using namespace std;

#include "engine/common.h"
#include "engine/math/vector4f.h"

namespace ve {

class Engine;

typedef unsigned char TextureData;
typedef float TextureDataf;

/**
    Supported texture formats.
*/
enum TextureFormat {
  RGB8,           // = GL_RGB,
  RGBA8,          // = GL_RGBA,
  BGR8,           // = GL_BGR,
  BGRA8,          // = GL_BGRA,
  RGB_DXT1,       // = GL_COMPRESSED_RGB_S3TC_DXT1_EXT,
  RGBA_DXT1,      // = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT,
  RGBA_DXT3,      // = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT,
  RGBA_DXT5,      // = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,
  LUMINANCE8,     // = GL_LUMINANCE,
  INTENSITY8,     // = GL_INTENSITY,
  RGB16F,         // = GL_RGB16F_ARB,
  RGBA16F,        // = GL_RGBA16F_ARB,
  ALPHA16F,       // = GL_ALPHA16F_ARB,
  INTENSITY16F,   // = GL_INTENSITY16F_ARB,
  LUMINANCE16F,   // = GL_LUMINANCE16F_ARB,
  LUMINANCE_ALPHA16F, // = GL_LUMINANCE_ALPHA16F_ARB,
  RGB32F,         // = GL_RGB32F_ARB,
  RGBA32F,        // = GL_RGBA32F_ARB,
  ALPHA32F,       // = GL_ALPHA32F_ARB,
  INTENSITY32F,   // = GL_INTENSITY32F_ARB,
  LUMINANCE32F,   // = GL_LUMINANCE32F_ARB,
  LUMINANCE_ALPHA32F // = GL_LUMINANCE_ALPHA32F_ARB
};

/**
    Supported texture filter: Linear & Bilinear.
*/
enum TextureFilter {
  NEAREST = 0,
  LINEAR,
  NEAREST_MIPMAP_NEAREST,     // For minFilter only
  LINEAR_MIPMAP_NEAREST,      // For minFilter only
  NEAREST_MIPMAP_LINEAR,      // For minFilter only
  LINEAR_MIPMAP_LINEAR        // For minFilter only
};

/**
    Texture loading mode. Defines compression type
    during texture loading.
*/
enum TextureLoadMode {
  TLM_UNCOMPRESSED = 0,
  TLM_DXT1,
  TLM_DXT3,
  TLM_DXT5
};

/**
    Defines behavior of texture mapping when texture coords are out of range.
    It is set per texture coordinate and may be different for different coordinates.
*/
enum TextureWrapMode {
  CLAMP = 0,
  REPEAT,
  CLAMP_TO_EDGE
};

/**
    Memory pool for texture storing.
*/
enum Pool {
  P_MANAGED,
  P_DEFAULT,
  P_SYSMEMORY
};

enum Usage {
  U_UNDEFINED
};

/**
    Texture description.
    <ul>
    <li>width - Width of the texture</li>
    <li>height - Height of the texture</li>
    <li>pool - Memory type where texture is being stored</li>
    <li>usage - For future usage</li>
    </ul>
*/
struct TextureDesc {
  TextureFormat format;
  int width;
  int height;
  Pool pool;
  Usage usage;
};

/**
    Texture filters to apply for the texture.
    Only linear and bilinear modes are supported now.
    <ul>
    <li>minFilter - minification filter</li>
    <li>magFilter - magnification filter</li>
    </ul>
*/
struct TextureSampler {
  TextureFilter minFilter;
  TextureFilter magFilter;
  float anisotropy;
  TextureWrapMode sTexture;
  TextureWrapMode tTexture;
  TextureWrapMode rTexture;

  /**
      Default constructor. Sets both filters to bilinear.
  */
  TextureSampler() {
    /* Binilear filtering */
    minFilter = LINEAR;
    magFilter = LINEAR;

    /* Anisotropy is off */
    anisotropy = 0.0;

    /* Texture wrap modes */
    sTexture = CLAMP;
    tTexture = CLAMP;
    rTexture = CLAMP;
  }

  TextureSampler(TextureFilter minFilter, TextureFilter magFilter) {
    /* Set filtering */
    this->minFilter = minFilter;
    this->magFilter = magFilter;

    /* Anisotropy is off */
    anisotropy = 0.0;

    /* Texture wrap modes */
    sTexture = CLAMP;
    tTexture = CLAMP;
    rTexture = CLAMP;
  }
};

/**
    Simply holds texture environment parameters.
    @see OpenGL's glTexEnvi and glTexEnvf functions to full information
    about this parameter.
*/
struct TextureEnvMode {
  TextureEnvironment envMode;

  TextureEnvMode() {
    envMode = REPLACE;
  }

  TextureEnvMode(TextureEnvironment theEnvMode) {
    envMode = theEnvMode;
  }

};

/**
    Represents Texture objects. This objects allocates GPU memory for the texture,
    stores texture and it used to bind it to the graphic pipeline.

    <b>Note:</b> Create Texture objects only through Engine::createTexture() function.
*/
class Texture {
protected:
  /** Engine that created this texture object. */
  Engine *engine;

  /** Texture description. */
  TextureDesc desc;

private:
  /** Handle which is used in Engine class to store instance-specific data. */
  Handle handle;

public:
  /**
      Texture constructor.

      <b>Note:</b>Objects of this class must be created only through
      Engine::createTexture() function.
      @param engine - Engine object that creates this texture.
      @param desc - Texture description.
      @param handle - Handle of this texture that is used to store
      instance-specific data.
  */
  Texture(Engine *engine, TextureDesc desc, Handle handle);

  /**
      Destructor. Frees allocated video memory using Engine::freeTexture() function.
  */
  virtual ~Texture();

  /**
      Returns instance-specific handle.
      @return Instance-specific handle.
  */
  Handle getHandle();

  /**
      Loads data to texture memory.
      @param data - Color data to load in texture memory.
      @return OK if data update succeeded.
      @return non-OK if engine error occurred.
  */
  Outcome load(TextureFormat nativeformat, TextureData *data);

  /**
      Returns texture description.
      @return Texture description.
  */
  TextureDesc getDesc();
};

}

#endif // __VE_TEXTURE_H__
