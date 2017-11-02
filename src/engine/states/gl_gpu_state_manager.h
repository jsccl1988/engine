// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_GL_GPU_STATE_MANAGER_H__
#define __VE_GL_GPU_STATE_MANAGER_H__

#include <map>

#include "engine/common.h"

#include "engine/ext/multi_texture_ext.h"
#include "engine/buffers/vbo_ext.h"
#include "engine/shaders/shaders_ext.h"
#include "engine/states/alpha_test_state.h"
#include "engine/states/depth_test_state.h"
#include "engine/states/blend_state.h"
#include "engine/states/color_state.h"
#include "engine/states/viewport_state.h"
#include "engine/states/gpu_state_manager.h"

namespace ve {
class GLEngine;

class GLGPUStateManager : public GPUStateManager {
private:
  GLEngine *engine;

  std::map<int, int> GLToEngine;

  MultiTextureExt *MultiTextureFunctions;
  VBOExt *VBOFunctions;
  ShadersExt *ShadersFunctions;

  /**
      Converts OpenGL enum to Engine's enum.
      @param value - OpenGL enum constant.
      @return Engine's constant.
  */
  int convertGLEnum(GLenum value);

  /**
      Converts Engine's enum to OpenGL's enum by looking up at the map table.
      @param tableIndex - Table to look constant at.
      @param value - Engine's enum constant.
      @return OpenGL's constant.
  */
  GLenum convertToGLEnum(uint tableIndex, uint value);

  /**
    Returns texture bound to current texture slot.
    @return Texture bound to current texture slot.
  */
  Texture* getTexture();

  /**
    Returns texture sampler from the current slot.
    @return Texture sampler from the current slot.
  */
  TextureSampler getTextureSampler(GLenum target);

  /**
    Returns texture environment mode from the current texture slot.
    @return texture environment mode from the current texture slot.
  */
  TextureEnvMode getTextureEnvMode();

  /**
      Returns current world view matrix.
      @return current world view matrix.
  */
  Matrix4f getWorldViewMatrix();

  /**
      Returns current projection matrix.
      @return current projection matrix.
  */
  Matrix4f getProjectionMatrix();

  /**
      Sets WorldView matrix.
      @param matrix - New value for WorldView matrix.
      @return OK if operation succeeded.
      @return non-OK in case of renderer error.
  */
  Outcome setWorldViewMatrix(Matrix4f matrix);

  /**
      Sets Projection matrix.
      @param matrix - New value for Projection matrix.
      @return OK if operation succeeded.
      @return non-OK in case of renderer error.
  */
  Outcome setProjectionMatrix(Matrix4f matrix);

  /* ********************************************** */
  /*             Alpha test functions               */
  /* ********************************************** */

/**
      Returns alpha test state.
  */
  virtual AlphaTestState readAlphaTestState();

  /**
      Sets alpha test state.
      @param state - State of the alpha testing stage.
      @return OK if operation succeeded.
      @return ERROR if error occurred in renderer.
  */
  virtual Outcome writeAlphaTestState(AlphaTestState state);

  /* ********************************************** */
  /*             Depth test functions               */
  /* ********************************************** */

/**
      Returns depth test state.
  */
  virtual DepthTestState readDepthTestState();

  /**
      Sets depth test state.
      @param state - State of the depth testing stage.
      @return OK if operation succeeded.
      @return ERROR if error occurred in renderer.
  */
  virtual Outcome writeDepthTestState(DepthTestState state);

  /* ********************************************** */
  /*               Blending functions               */
  /* ********************************************** */

/**
      Returns current state of blend stage.
      @return Current state of blend stage.
  */
  virtual BlendState readBlendState();

  /**
      Sets blend state of the pipeline.
      @param state - State of blending operations to set.
      @return OK if operation succeeded.
      @return ERROR if error occurred in renderer.
  */
  virtual Outcome writeBlendState(BlendState state);

  /* ********************************************** */
  /*               Viewport functions               */
  /* ********************************************** */

/**
      Returns viewport state of pipeline.
      @return ViewportState object that contains information about current
      viewport state of the pipeline.
  */
  virtual ViewportState readViewportState();

  /**
      Sets viewport using ViewportState object.
      @param state - Viewport state to set.
      @return OK if operation succeeded.
      @return ERROR if error occurred in renderer.
  */
  virtual Outcome writeViewportState(ViewportState state);

  /* ********************************************** */
  /*                 Color functions                */
  /* ********************************************** */

/**
      Returns current color.
      @return Current color that is used to fill polygons.
  */
  virtual ColorState readColorState();

  /**
      Sets color state.
      @param state - Color state to make active.
  */
  virtual Outcome writeColorState(ColorState colorState);

  /* ********************************************** */
  /*               Texture functions                */
  /* ********************************************** */

/**
Returns textures state of the pipeline. It contains texture that are
currently bound, their samplers and texture environment parameters.
@return Current textures state of the pipeline.
*/
  virtual TexturesState readTexturesState();

  /**
    Sets textures state.
    @param state - Texture state to set.
    @return OK if operation succeeded.
    @return non-OK in case of any error.
  */
  virtual Outcome writeTexturesState(TexturesState state);

  /* ********************************************** */
      /*                Matrix functions                */
      /* ********************************************** */

  /**
          Returns Matrix state of the pipeline.
          @return Matrix state of the pipeline.
      */
  virtual MatrixState readMatrixState();

  /**
      Sets the matrix state of the pipeline.
      @param state - New matrix state.
      @return OK if operation succeeded.
      @return non-OK if error occurred.
  */
  virtual Outcome writeMatrixState(MatrixState state);

  /* ********************************************** */
      /*                 Buffers functions              */
      /* ********************************************** */

  /**
          Returns buffers currently bound to the pipeline and their state.
          @return Buffers currently bound to the pipeline and their state.
      */
  virtual BuffersState readBuffersState();

  /**
      Sets buffers and their parameters.
      @param state - Structure that contains buffers and their parameters
      @return OK if operation succeeded.
      @return non-OK in case of error.
  */
  virtual Outcome writeBuffersState(BuffersState state);

  /* ********************************************** */
      /*                 Shaders functions              */
      /* ********************************************** */

  /**
    Returns shaders that is currently bound to the pipeline.
    @return Shaders that is currently bound to the pipeline.
  */
  virtual ShadersState readShadersState();

  /**
    Binds shaders to the pipeline.
    @param state - State that contains program to bound.
    @return OK if operation succeeded.
    @return non-OK in case of error.
  */
  virtual Outcome writeShadersState(ShadersState state);

public:
  /**
      Default constructor.
  */
  GLGPUStateManager(GLEngine *engine, MultiTextureExt *MultiTextureFunctions, VBOExt *VBOFunctions,
    ShadersExt *ShadersFunctions);

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
  virtual Outcome setClearColorValue(float red, float green, float blue, float alpha);

  /**
      Sets value for depth buffer clearing.
      @param depth - Depth value to clear depth buffer before rendering.
      @return OK if operation succeeded.
      @return ERROR if error occurred in renderer.
  */
  virtual Outcome setClearDepthValue(float depth);

  /**
      Changes rendering mode for front or back polygon faces to fill/line mode/point mode.
      @param face - type of the face(s) to change rendering for.
      @param mode - new rendering mode.
      @return OK if operation succeeded.
      @return ERROR if error occurred in renderer.
  */
  virtual Outcome setPolygonMode(Face face, PolygonMode mode);

  /**
      Sets width for rendered lines.
      @return size - Width to use for line rendering.
      @return OK if operation succeeded.
      @return ERROR if error occurred in renderer.
  */
  virtual Outcome setLineWidth(float size);

  /**
      Enables or disables (depending on a 'enabled' flag) depth offset for specified faces.
      @param mode - Faces to enable/disable depth offset for.
      @param enabled - passing 'true' enables depth offset and 'false' disables.
      @return OK if operation succeeded.
      @return ERROR if error occurred in renderer.
  */
  virtual Outcome enableDepthOffset(PolygonMode mode, bool enabled);

  /**
      Sets the scale and bias used to calculate depth values.

      @param rFactor -Specifies a scale factor which is used to create a variable depth offset for each
      polygon. The initial value is 0.
      @param dFactor - Is multiplied by an implementation specific value to create a constant depth offset.
      The initial value is 0.

      @return OK if operation succeeded.
      @return ERROR if error occurred in renderer.
  */
  virtual Outcome depthOffsetParams(float rFactor, float dFactor);
};

}

#endif // __VE_GL_GPU_STATE_MANAGER_H__
