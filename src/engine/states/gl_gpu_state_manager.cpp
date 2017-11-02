// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "states/gl_gpu_state_manager.h"
#include "tools/texture_tool.h"
#include "math/maths.h"
#include "engines/gl_engine.h"

namespace ve {

/**
    Map to convert OpenGL consts to engine's and vice versa
*/
const static int g_GLToEngineMap[][2] =
{
    {GL_LESS, LESS}, {GL_LEQUAL, LEQUAL}, {GL_GREATER, GREATER}, {GL_GEQUAL, GEQUAL}, {GL_EQUAL, EQUAL},
    {GL_ZERO, ZERO}, {GL_ONE, ONE}, {GL_SRC_COLOR, SRC_COLOR}, {GL_DST_COLOR, DST_COLOR},
    {GL_ONE_MINUS_DST_COLOR, ONE_MINUS_DST_COLOR}, {GL_SRC_ALPHA, SRC_ALPHA},
    {GL_ONE_MINUS_SRC_ALPHA, ONE_MINUS_SRC_ALPHA}, {GL_DST_ALPHA, DST_ALPHA},
    {GL_ONE_MINUS_DST_ALPHA, ONE_MINUS_DST_ALPHA}, {GL_SRC_ALPHA_SATURATE, SRC_ALPHA_SATURATE},
    {GL_REPLACE, REPLACE}, {GL_MODULATE, MODULATE}, {GL_DECAL, DECAL}, {GL_BLEND, BLEND},
    {GL_ADD, ADD}, {GL_CLAMP, CLAMP}, {GL_REPEAT, REPEAT}, {GL_CLAMP_TO_EDGE, CLAMP_TO_EDGE},
    {GL_NEAREST, NEAREST}, {GL_LINEAR, LINEAR}, {GL_NEAREST_MIPMAP_NEAREST, NEAREST_MIPMAP_NEAREST},
    {GL_LINEAR_MIPMAP_NEAREST, LINEAR_MIPMAP_NEAREST}, {GL_NEAREST_MIPMAP_LINEAR, NEAREST_MIPMAP_LINEAR},
    {GL_LINEAR_MIPMAP_LINEAR, LINEAR_MIPMAP_LINEAR}, {GL_SHORT, SHORT}, {GL_INT, INT},
    {GL_FLOAT, FLOAT}, {GL_DOUBLE, DOUBLE}, {GL_UNSIGNED_INT, UNSIGNED_INT},
    {GL_UNSIGNED_BYTE, UNSIGNED_BYTE}, {GL_UNSIGNED_SHORT, UNSIGNED_SHORT}
};

/* Indexes of map tables for different constants */
const static int COMPARISON_TABLE = 0;
const static int TEXTURE_FILTER_TABLE = 1;
const static int TEXTURE_COORD_WRAP_MODE_TABLE = 2;
const static int TEXTURE_ENVIRONMENT_TABLE = 3;
const static int FACE_TABLE = 4;
const static int POLYGON_MODE_TABLE = 5;
const static int BLEND_FACTOR_TABLE = 6;
const static int TYPE_TABLE = 7;

const static int g_ComparisonTable[] = { GL_LESS, GL_LEQUAL, GL_GREATER, GL_GEQUAL, GL_EQUAL };

const static int g_TextureFilterTable[] =
{ GL_NEAREST, GL_LINEAR, GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST,
  GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR
};

const static int g_TextureCoordWrapModeTable[] = { GL_CLAMP, GL_REPEAT, GL_CLAMP_TO_EDGE };

const static int g_TextureEnvironmentTable[] = { GL_REPLACE, GL_MODULATE, GL_DECAL, GL_BLEND, GL_ADD };

const static int g_FaceTable[] = { GL_BACK, GL_FRONT, GL_FRONT_AND_BACK };

const static int g_PolygonModeTable[] = { GL_POINT, GL_LINE, GL_FILL };

const static int g_BlendFactorTable[] =
{
    GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_DST_COLOR,
    GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA,
    GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_SRC_ALPHA_SATURATE
};

const static int g_TypeTable[] = { GL_SHORT, GL_INT, GL_FLOAT,
  GL_DOUBLE, GL_UNSIGNED_INT, GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT };

const static int* g_EngineToGLMap[] =
{
    g_ComparisonTable,
    g_TextureFilterTable,
    g_TextureCoordWrapModeTable,
    g_TextureEnvironmentTable,
    g_FaceTable,
    g_PolygonModeTable,
    g_BlendFactorTable,
g_TypeTable
};

const static uint g_TableSize[] =
{
    sizeof(g_ComparisonTable) / sizeof(int),
    sizeof(g_TextureFilterTable) / sizeof(int),
    sizeof(g_TextureCoordWrapModeTable) / sizeof(int),
    sizeof(g_TextureEnvironmentTable) / sizeof(int),
    sizeof(g_FaceTable) / sizeof(int),
    sizeof(g_PolygonModeTable) / sizeof(int),
    sizeof(g_BlendFactorTable) / sizeof(int),
sizeof(g_TypeTable) / sizeof(int)
};

const static int g_TablesCount = sizeof(g_EngineToGLMap) / sizeof(int*);

/**
    Default constructor.
*/
GLGPUStateManager::GLGPUStateManager(GLEngine *engine, MultiTextureExt *MultiTextureFunctions, VBOExt *VBOFunctions,
  ShadersExt *ShadersFunctions) :GPUStateManager() {
  this->engine = engine;
  this->MultiTextureFunctions = MultiTextureFunctions;
  this->ShadersFunctions = ShadersFunctions;
  this->VBOFunctions = VBOFunctions;

  for (int i = 0; i < g_TablesCount; i++) {
    GLToEngine[g_GLToEngineMap[i][0]] = g_GLToEngineMap[i][1];
  }

  readState();
}

/**
    Converts OpenGL enum to Engine's enum.
    @param value - OpenGL enum constant.
    @return Engine's constant.
*/
int GLGPUStateManager::convertGLEnum(GLenum value) {
  return GLToEngine[(int)value];
}

/**
    Converts Engine's enum to OpenGL's enum.
    @param tableIndex - Table to look constant at.
    @param value - Engine's enum constant.
    @return OpenGL's constant.
*/
GLenum GLGPUStateManager::convertToGLEnum(uint tableIndex, uint value) {
  ERROR_IF(tableIndex >= g_TablesCount, L"Unknown table", (GLenum)ERROR);
  ERROR_IF(value >= g_TableSize[tableIndex], L"Unnown value", (GLenum)ERROR);
  return g_EngineToGLMap[tableIndex][value];
}

/* ********************************************** */
/*             Alpha test functions               */
/* ********************************************** */

/**
    Returns alpha test state.
*/
AlphaTestState GLGPUStateManager::readAlphaTestState() {
  AlphaTestState newState;
  int func = 0;
  float ref = 0;

  glGetIntegerv(GL_ALPHA_TEST_FUNC, &func);
  glGetFloatv(GL_ALPHA_TEST_REF, &ref);

  newState.isEnabled = (glIsEnabled(GL_ALPHA_TEST) == GL_TRUE);
  newState.func = static_cast<ve::Comparison>(convertGLEnum(func));
  newState.refValue = ref;

  return newState;
}

/**
    Sets alpha test state.
    @param state - State of the alpha testing stage.
    @return OK if operation succeeded.
    @return ERROR if error occurred in renderer.
*/
Outcome GLGPUStateManager::writeAlphaTestState(AlphaTestState state) {
  if (state.isEnabled) {
    glEnable(GL_ALPHA_TEST);
    GL_SAFE_CALL(glAlphaFunc(convertToGLEnum(COMPARISON_TABLE, state.func), state.refValue), ERROR);
  } else {
    glDisable(GL_ALPHA_TEST);
  }
  return OK;
}

/* ********************************************** */
/*             Depth test functions               */
/* ********************************************** */

/**
    Returns depth test state.
*/
DepthTestState GLGPUStateManager::readDepthTestState() {
  DepthTestState newState;
  GLboolean depthMask;
  int func = 0;

  glGetBooleanv(GL_DEPTH_WRITEMASK, &depthMask);
  glGetIntegerv(GL_DEPTH_FUNC, &func);

  newState.isEnabled = (glIsEnabled(GL_DEPTH_TEST) == GL_TRUE);
  newState.depthMask = (depthMask == GL_TRUE);
  newState.func = static_cast<ve::Comparison>(convertGLEnum(func));

  return newState;
}

/**
    Sets depth test state.
    @param state - State of the depth testing stage.
    @return OK if operation succeeded.
    @return ERROR if error occurred in renderer.
*/
Outcome GLGPUStateManager::writeDepthTestState(DepthTestState state) {
  if (state.isEnabled) {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(convertToGLEnum(COMPARISON_TABLE, state.func));
  } else {
    glDisable(GL_DEPTH_TEST);
  }
  return OK;
}

/* ********************************************** */
/*               Blending functions               */
/* ********************************************** */

/**
    Returns current state of blend stage.
    @return Current state of blend stage.
*/
BlendState GLGPUStateManager::readBlendState() {
  BlendState newState;
  int sFactor = 0;
  int dFactor = 0;

  glGetIntegerv(GL_BLEND_SRC, &sFactor);
  glGetIntegerv(GL_BLEND_DST, &dFactor);

  newState.isEnabled = (glIsEnabled(GL_BLEND) == GL_TRUE);
  newState.sourceFactor = static_cast<BlendFactor>(convertGLEnum(sFactor));
  newState.destFactor = static_cast<BlendFactor>(convertGLEnum(dFactor));

  return newState;
}

/**
    Sets blend state of the pipeline.
    @param state - State of blending operations to set.
    @return OK if operation succeeded.
    @return ERROR if error occurred in renderer.
*/
Outcome GLGPUStateManager::writeBlendState(BlendState state) {
  if (state.isEnabled) {
    glEnable(GL_BLEND);
    GLenum sFactor = convertToGLEnum(BLEND_FACTOR_TABLE, state.sourceFactor);
    GLenum dFactor = convertToGLEnum(BLEND_FACTOR_TABLE, state.destFactor);
    GL_SAFE_CALL(glBlendFunc(sFactor, dFactor), ERROR);
  } else {
    glDisable(GL_BLEND);
  }

  return OK;
}

/* ********************************************** */
/*               Viewport functions               */
/* ********************************************** */

/**
    Returns viewport state of pipeline.
    @return ViewportState object that contains information about current
    viewport state of the pipeline.
*/
ViewportState GLGPUStateManager::readViewportState() {
  int values[4];

  GL_SAFE_CALL(glGetIntegerv(GL_VIEWPORT, values), ViewportState(0, 0, 0, 0));

  return ViewportState(values[0], values[1], values[2], values[3]);
}

/**
    Sets viewport using ViewportState object.
    @param state - Viewport state to set.
    @return OK if operation succeeded.
    @return ERROR if error occurred in renderer.
*/
Outcome GLGPUStateManager::writeViewportState(ViewportState state) {
  GL_SAFE_CALL(glViewport(state.x, state.y, state.width, state.height), ERROR);
  return OK;
}

/* ********************************************** */
/*                 Color functions                */
/* ********************************************** */

/**
    Returns current color.
    @return Current color that is used to fill polygons.
*/
ColorState GLGPUStateManager::readColorState() {
  float color[4];

  GL_SAFE_CALL(glGetFloatv(GL_CURRENT_COLOR, color), ColorState(0, 0, 0, 0));

  return ColorState(color[0], color[1], color[2], color[3]);
}

/**
    Sets color state.
    @param state - Color state to make active.
*/
Outcome GLGPUStateManager::writeColorState(ColorState colorState) {
  glColor4f(colorState.r, colorState.g, colorState.b, colorState.a);
  GL_CHECK(ERROR);
  return OK;
}

/* ********************************************** */
/*               Texture functions                */
/* ********************************************** */

/**
  Returns texture bound to current texture slot.
  @return Texture bound to current texture slot.
*/
Texture* GLGPUStateManager::getTexture() {
  GLint id;
  glGetIntegerv(GL_TEXTURE_BINDING_2D, &id);

  if (id == 0) {
    glGetIntegerv(GL_TEXTURE_BINDING_RECTANGLE_ARB, &id);

    if (id == 0) {
      return NULL;
    }

    return engine->getTextureByGLId(id);
  }

  return engine->getTextureByGLId(id);
}

/**
  Returns texture sampler from the current slot.
  @return Texture sampler from the current slot.
*/
TextureSampler GLGPUStateManager::getTextureSampler(GLenum target) {
  GLint filter = 0;
  GLint wrapMode = 0;
  TextureSampler sampler;

  DeviceCaps *devCaps = engine->getDeviceCaps();
  if (devCaps->isAnisotropySupported()) {
    glGetTexParameterfv(target, GL_TEXTURE_MAX_ANISOTROPY_EXT, &sampler.anisotropy);
  } else {
    sampler.anisotropy = 0;
  }

  glGetTexParameteriv(target, GL_TEXTURE_MAG_FILTER, &filter);
  sampler.magFilter = static_cast<TextureFilter>(convertGLEnum(filter));

  glGetTexParameteriv(target, GL_TEXTURE_MIN_FILTER, &filter);
  sampler.minFilter = static_cast<TextureFilter>(convertGLEnum(filter));

  glGetTexParameteriv(target, GL_TEXTURE_WRAP_S, &wrapMode);
  sampler.sTexture = static_cast<TextureWrapMode>(convertGLEnum(wrapMode));

  glGetTexParameteriv(target, GL_TEXTURE_WRAP_T, &wrapMode);
  sampler.tTexture = static_cast<TextureWrapMode>(convertGLEnum(wrapMode));

  glGetTexParameteriv(target, GL_TEXTURE_WRAP_R, &wrapMode);
  sampler.rTexture = static_cast<TextureWrapMode>(convertGLEnum(wrapMode));

  return sampler;
}

/**
  Returns texture environment mode from the current texture slot.
  @return texture environment mode from the current texture slot.
*/
TextureEnvMode GLGPUStateManager::getTextureEnvMode() {
  TextureEnvMode texEnv;
  GLint env;

  glGetTexEnviv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, &env);
  texEnv.envMode = static_cast<TextureEnvironment>(convertGLEnum(env));

  return texEnv;
}

/**
  Returns textures state of the pipeline. It contains texture that are
  currently bound, their samplers and texture environment parameters.
  @return Current textures state of the pipeline.
*/
TexturesState GLGPUStateManager::readTexturesState() {
  TexturesState texturesState;

  for (uint i = 0; i < SLOTS_IN_TEXTURE_STATE; i++) {
    GL_SAFE_CALL(MultiTextureFunctions->glActiveTexture(GL_TEXTURE0 + i), NULL);

    if (glIsEnabled(GL_TEXTURE_2D) || glIsEnabled(GL_TEXTURE_RECTANGLE_ARB)) {
      texturesState.slots[i] = getTexture();

      if (texturesState.slots[i] != NULL) {
        GLenum target = GL_TEXTURE_2D;

        if (TextureTool::isNPOTSTexture(texturesState.slots[i])) {
          target = GL_TEXTURE_RECTANGLE_ARB;
        }

        texturesState.samplers[i] = getTextureSampler(target);
        texturesState.texEnv[i] = getTextureEnvMode();
      }
    }
  }

  return texturesState;
}

/**
  Sets textures state.
  @param state - Texture state to set.
  @return OK if operation succeeded.
  @return non-OK in case of any error.
*/
Outcome GLGPUStateManager::writeTexturesState(TexturesState state) {
  for (uint i = 0; i < SLOTS_IN_TEXTURE_STATE; i++) {
    Texture *texture = state.slots[i];

    GL_SAFE_CALL(MultiTextureFunctions->glActiveTexture(GL_TEXTURE0 + i), ERROR);

    if (texture != NULL) {
      GLhandleARB handle = texture->getHandle();
      TextureSampler sampler = state.samplers[i];
      TextureEnvMode texEnv = state.texEnv[i];
      GLenum target = GL_TEXTURE_2D;

      if (TextureTool::isNPOTSTexture(texture)) {
        target = GL_TEXTURE_RECTANGLE_ARB;
      }

      glEnable(target);

      GL_SAFE_CALL(glBindTexture(target, handle), ERROR);

      /* Check if anisotropy was set */
      if (!Maths::equals(sampler.anisotropy, 0)) {
        GL_SAFE_CALL(glTexParameterf(target, GL_TEXTURE_MAX_ANISOTROPY_EXT, sampler.anisotropy), ERROR);
      }

      GL_SAFE_CALL(glTexParameteri(target, GL_TEXTURE_MAG_FILTER, convertToGLEnum(TEXTURE_FILTER_TABLE, sampler.magFilter)), ERROR);
      GL_SAFE_CALL(glTexParameteri(target, GL_TEXTURE_MIN_FILTER, convertToGLEnum(TEXTURE_FILTER_TABLE, sampler.minFilter)), ERROR);
      GL_SAFE_CALL(glTexParameteri(target, GL_TEXTURE_WRAP_S, convertToGLEnum(TEXTURE_COORD_WRAP_MODE_TABLE, sampler.sTexture)), ERROR);
      GL_SAFE_CALL(glTexParameteri(target, GL_TEXTURE_WRAP_T, convertToGLEnum(TEXTURE_COORD_WRAP_MODE_TABLE, sampler.tTexture)), ERROR);
      GL_SAFE_CALL(glTexParameteri(target, GL_TEXTURE_WRAP_R, convertToGLEnum(TEXTURE_COORD_WRAP_MODE_TABLE, sampler.rTexture)), ERROR);
      GL_SAFE_CALL(glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, convertToGLEnum(TEXTURE_ENVIRONMENT_TABLE, texEnv.envMode)), ERROR);
    } else {
      glDisable(GL_TEXTURE_2D);
      glDisable(GL_TEXTURE_RECTANGLE_ARB);
    }
  }

  return OK;
}

/* ********************************************** */
/*                Matrix functions                */
/* ********************************************** */

/**
    Returns Matrix state of the pipeline.
    @return Matrix state of the pipeline.
*/
MatrixState GLGPUStateManager::readMatrixState() {
  return MatrixState(getWorldViewMatrix(), getProjectionMatrix());
}

/**
    Sets the matrix state of the pipeline.
    @param state - New matrix state.
    @return OK if operation succeeded.
    @return non-OK if error occurred.
*/
Outcome GLGPUStateManager::writeMatrixState(MatrixState state) {
  ASSERT(setWorldViewMatrix(state.worldView));
  ASSERT(setProjectionMatrix(state.projection));
  return OK;
}

/**
    Returns current world view matrix.
    @return current world view matrix.
*/
Matrix4f GLGPUStateManager::getWorldViewMatrix() {
  Matrix4f result;
  float data[16];

  glGetFloatv(GL_MODELVIEW_MATRIX, data);

  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      result[row][col] = data[row + 4 * col];
    }
  }

  return result;
}

/**
    Returns current projection matrix.
    @return current projection matrix.
*/
Matrix4f GLGPUStateManager::getProjectionMatrix() {
  Matrix4f result;
  float data[16];

  glGetFloatv(GL_PROJECTION_MATRIX, data);

  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      result[row][col] = data[row + 4 * col];
    }
  }

  return result;
}

/**
    Sets WorldView matrix.
    @param matrix - New value for WorldView matrix.
    @return OK if operation succeeded.
    @return non-OK in case of renderer error.
*/
Outcome GLGPUStateManager::setWorldViewMatrix(Matrix4f matrix) {
  GLfloat data[16];

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      data[4 * i + j] = matrix[j][i];
    }
  }

  glMatrixMode(GL_MODELVIEW);
  glLoadMatrixf(data);

  return OK;
}

/**
    Sets Projection matrix.
    @param matrix - New value for Projection matrix.
    @return OK if operation succeeded.
    @return non-OK in case of renderer error.
*/
Outcome GLGPUStateManager::setProjectionMatrix(Matrix4f matrix) {
  GLfloat data[16];

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      data[4 * i + j] = matrix[j][i];
    }
  }

  glMatrixMode(GL_PROJECTION);
  glLoadMatrixf(data);

  return OK;
}

/* ********************************************** */
/*                 Buffers functions              */
/* ********************************************** */

/**
    Returns buffers currently bound to the pipeline and their state.
    @return Buffers currently bound to the pipeline and their state.
*/
BuffersState GLGPUStateManager::readBuffersState() {
  BuffersState buffersState;
  GLint id = 0;
  GLint type = 0;
  GLint size = 0;
  GLint stride = 0;

  /* Index buffer */
  glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &id);

  if (id == 0) {
    buffersState.indices.data = NULL;
  } else {
    buffersState.indices.isVBO = true;
    buffersState.indices.data = (void*)engine->getBufferById(id);
  }

  /* Vertex buffer */
  if (glIsEnabled(GL_VERTEX_ARRAY)) {
    glGetPointerv(GL_VERTEX_ARRAY_POINTER, &buffersState.vertices.data);

    if (buffersState.vertices.data == NULL) {
      buffersState.vertices.isVBO = true;
      glGetIntegerv(GL_VERTEX_ARRAY_BUFFER_BINDING, &id);
      buffersState.vertices.data = engine->getBufferById(id);
    } else {
      buffersState.vertices.isVBO = false;
    }

    glGetIntegerv(GL_VERTEX_ARRAY_SIZE, &size);
    glGetIntegerv(GL_VERTEX_ARRAY_TYPE, &type);
    glGetIntegerv(GL_VERTEX_ARRAY_STRIDE, &stride);

    buffersState.vertices.components = size;
    buffersState.vertices.type = static_cast<Type>(convertGLEnum(type));
    buffersState.vertices.stride = stride;
  } else {
    buffersState.vertices.data = NULL;
  }

  /* Texture Coordinates */
  if (glIsEnabled(GL_TEXTURE_COORD_ARRAY)) {
    glGetPointerv(GL_TEXTURE_COORD_ARRAY_POINTER, &buffersState.texCoords.data);

    if (buffersState.texCoords.data == NULL) {
      buffersState.texCoords.isVBO = true;
      glGetIntegerv(GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING, &id);
      buffersState.texCoords.data = engine->getBufferById(id);
    } else {
      buffersState.texCoords.isVBO = false;
    }

    glGetIntegerv(GL_TEXTURE_COORD_ARRAY_SIZE, &size);
    glGetIntegerv(GL_TEXTURE_COORD_ARRAY_TYPE, &type);
    glGetIntegerv(GL_TEXTURE_COORD_ARRAY_STRIDE, &stride);

    buffersState.texCoords.components = size;
    buffersState.texCoords.type = static_cast<Type>(convertGLEnum(type));
    buffersState.texCoords.stride = stride;
  } else {
    buffersState.texCoords.data = NULL;
  }

  /* Normals */
  if (glIsEnabled(GL_NORMAL_ARRAY)) {
    glGetPointerv(GL_NORMAL_ARRAY_POINTER, &buffersState.normals.data);

    if (buffersState.normals.data == NULL) {
      buffersState.normals.isVBO = true;
      glGetIntegerv(GL_NORMAL_ARRAY_BUFFER_BINDING, &id);
      buffersState.normals.data = engine->getBufferById(id);
    } else {
      buffersState.normals.isVBO = false;
    }

    glGetIntegerv(GL_NORMAL_ARRAY_TYPE, &type);
    glGetIntegerv(GL_NORMAL_ARRAY_STRIDE, &stride);
    buffersState.normals.components = 3;
    buffersState.normals.type = static_cast<Type>(convertGLEnum(type));
    buffersState.normals.stride = stride;
  } else {
    buffersState.normals.data = NULL;
  }

  return buffersState;
}

/**
    Sets buffers and their parameters.
    @param state - Structure that contains buffers and their parameters
    @return OK if operation succeeded.
    @return non-OK in case of error.
*/
Outcome GLGPUStateManager::writeBuffersState(BuffersState state) {
  BufferDesc &desc = state.indices;

  /* Index array */
  if (desc.data != NULL) {
    if (desc.isVBO) {
      VideoBuffer *buffer = (VideoBuffer*)desc.data;
      GL_SAFE_CALL(VBOFunctions->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->getHandle()), ERROR);
    }
  } else {
    GL_SAFE_CALL(VBOFunctions->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0), ERROR);
  }

  /* Vertex array */
  desc = state.vertices;
  if (desc.data != NULL) {
    if (desc.isVBO) {
      VideoBuffer *buffer = (VideoBuffer*)desc.data;
      GL_SAFE_CALL(VBOFunctions->glBindBuffer(GL_ARRAY_BUFFER, buffer->getHandle()), ERROR);
    }

    GL_SAFE_CALL(glEnableClientState(GL_VERTEX_ARRAY), ERROR);
    GL_SAFE_CALL(glVertexPointer(desc.components, convertToGLEnum(TYPE_TABLE, desc.type), desc.stride, (desc.isVBO) ? 0 : desc.data), ERROR);
  } else {
    GL_SAFE_CALL(glDisableClientState(GL_VERTEX_ARRAY), ERROR);
  }

  /* Texture coordinates */
  desc = state.texCoords;
  if (desc.data != NULL) {
    if (desc.isVBO) {
      VideoBuffer *buffer = (VideoBuffer*)desc.data;
      GL_SAFE_CALL(VBOFunctions->glBindBuffer(GL_ARRAY_BUFFER, buffer->getHandle()), ERROR);
    }

    GL_SAFE_CALL(glEnableClientState(GL_TEXTURE_COORD_ARRAY), ERROR);
    GL_SAFE_CALL(glTexCoordPointer(desc.components, convertToGLEnum(TYPE_TABLE, desc.type),
      desc.stride, (desc.isVBO) ? 0 : desc.data), ERROR);
  } else {
    GL_SAFE_CALL(glDisableClientState(GL_TEXTURE_COORD_ARRAY), ERROR);
  }

  /* Normals */
  desc = state.normals;
  if (desc.data != NULL) {
    if (desc.isVBO) {
      VideoBuffer *buffer = (VideoBuffer*)desc.data;
      GL_SAFE_CALL(VBOFunctions->glBindBuffer(GL_ARRAY_BUFFER, buffer->getHandle()), ERROR);
    }

    GL_SAFE_CALL(glEnableClientState(GL_NORMAL_ARRAY), ERROR);
    GL_SAFE_CALL(glNormalPointer(convertToGLEnum(TYPE_TABLE, desc.type), desc.stride, (desc.isVBO) ? 0 : desc.data), ERROR);
  } else {
    GL_SAFE_CALL(glDisableClientState(GL_NORMAL_ARRAY), ERROR);
  }

  GL_SAFE_CALL(VBOFunctions->glBindBuffer(GL_ARRAY_BUFFER, 0), ERROR);

  return OK;
}

/* ********************************************** */
  /*                 Shaders functions              */
  /* ********************************************** */

/**
  Returns shaders that is currently bound to the pipeline.
  @return Shaders that is currently bound to the pipeline.
*/
ShadersState GLGPUStateManager::readShadersState() {
  GLint id = 0;
  ShadersState shadersState;

  glGetIntegerv(GL_CURRENT_PROGRAM, &id);

  if (id != 0) {
    shadersState.program = engine->getProgramById(id);
  }

  return shadersState;
}

/**
  Binds shaders to the pipeline.
  @param state - State that contains program to bound.
  @return OK if operation succeeded.
  @return non-OK in case of error.
*/
Outcome GLGPUStateManager::writeShadersState(ShadersState state) {
  if (state.program != NULL) {
    GL_SAFE_CALL(ShadersFunctions->glUseProgram(state.program->getHandle()), ERROR);
  } else {
    GL_SAFE_CALL(ShadersFunctions->glUseProgram(0), ERROR);
  }

  return OK;
}

/* ********************************************** */
  /*                 Other functions                */
  /* ********************************************** */

  /**
      Sets color that will be used to clear back buffer.
      @param red - red component of the color.
      @param green - green component of the color.
      @param blue - blue component of the color.
      @param alpha - alpha component of the color.
      @return OK if operation succeeded.
      @return ERROR if error occurred in renderer.
  */
Outcome GLGPUStateManager::setClearColorValue(float red, float green, float blue, float alpha) {
  glClearColor(red, green, blue, alpha);
  return OK;
}

/**
    Sets value for depth buffer clearing.
    @param depth - Depth value to clear depth buffer before rendering.
    @return OK if operation succeeded.
    @return ERROR if error occurred in renderer.
*/
Outcome GLGPUStateManager::setClearDepthValue(float depth) {
  glClearDepth(depth);
  return OK;
}

/**
    Changes rendering mode for front or back polygon faces to fill/line mode/point mode.
    @param face - type of the face(s) to change rendering for.
    @param mode - new rendering mode.
    @return OK if operation succeeded.
    @return ERROR if error occurred in renderer.
*/
Outcome GLGPUStateManager::setPolygonMode(Face face, PolygonMode mode) {
  GLenum GLFace = convertToGLEnum(FACE_TABLE, face);
  GLenum GLMode = convertToGLEnum(POLYGON_MODE_TABLE, mode);
  glPolygonMode(GLFace, GLMode);
  return OK;
}

/**
    Sets width for rendered lines.
    @return size - Width to use for line rendering.
    @return OK if operation succeeded.
    @return ERROR if error occurred in renderer.
*/
Outcome GLGPUStateManager::setLineWidth(float size) {
  GL_SAFE_CALL(glLineWidth(size), ERROR);
  return OK;
}

/**
    Enables or disables (depending on a 'enabled' flag) depth offset for specified faces.
    @param mode - Faces to enable/disable depth offset for.
    @param enabled - passing 'true' enables depth offset and 'false' disables.
    @return OK if operation succeeded.
    @return ERROR if error occurred in renderer.
*/
Outcome GLGPUStateManager::enableDepthOffset(PolygonMode mode, bool enabled) {
  int tmp = 0;

  switch (mode) {
  case POINT:
    tmp = GL_POLYGON_OFFSET_POINT;
    break;
  case LINE:
    tmp = GL_POLYGON_OFFSET_LINE;
    break;
  case FILL:
    tmp = GL_POLYGON_OFFSET_FILL;
    break;
  default:
    FAIL(L"Unsupported mode", ERROR);
  }

  if (enabled) {
    glEnable(tmp);
  } else {
    glDisable(tmp);
  }

  return OK;
}

/**
    Sets the scale and bias used to calculate depth values.

    @param rFactor -Specifies a scale factor which is used to create a variable depth offset for each
    polygon. The initial value is 0.
    @param dFactor - Is multiplied by an implementation specific value to create a constant depth offset.
    The initial value is 0.

    @return OK if operation succeeded.
    @return ERROR if error occurred in renderer.
*/
Outcome GLGPUStateManager::depthOffsetParams(float rFactor, float dFactor) {
  glPolygonOffset(rFactor, dFactor);
  GL_CHECK(ERROR);
  return OK;
}

}
