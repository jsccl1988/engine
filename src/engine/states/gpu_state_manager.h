// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_GPU_STATE_MANAGER_H__
#define __VE_GPU_STATE_MANAGER_H__

#include <stack>

#include "engine/states/gpu_state.h"
#include "engine/textures/texture.h"
#include "engine/math/matrix4f.h"

namespace ve {

/**
    Defines different states of the pipeline that could
    be set via StateManager class.
*/
enum PipelineState {
  /* Rasterizer states */
  ALPHA_TEST_STATE = 1,
  DEPTH_TEST_STATE = 2,
  BLEND_STATE = 4,
  COLOR_STATE = 8,
  TEXTURES_STATE = 16,

  /* Transform states */
  VIEWPORT_STATE = 32,
  MATRIX_STATE = 64,

  /* Input assembler states */
  BUFFERS_STATE = 128,

  /* Shaders */
  SHADERS_STATE = 256,

  /* Group of the states */
  RASTERIZER_STATE = ALPHA_TEST_STATE | DEPTH_TEST_STATE | BLEND_STATE | COLOR_STATE | TEXTURES_STATE,
  TRANSFORM_STATE = VIEWPORT_STATE | MATRIX_STATE,
  INPUT_ASSEMBLER_STATE = BUFFERS_STATE,

  /* Pipeline state */
  GPU_STATE = RASTERIZER_STATE | TRANSFORM_STATE | INPUT_ASSEMBLER_STATE | SHADERS_STATE
};

/**
    Manages all pipeline states.
*/
class GPUStateManager {
private:
  /*
      Stacks to implement push / pop functions for different states.
  */
  std::stack<AlphaTestState> alphaStack;
  std::stack<DepthTestState> depthStack;
  std::stack<BlendState> blendStack;
  std::stack<ViewportState> viewportStack;
  std::stack<ColorState> colorStack;
  std::stack<MatrixState> matrixStack;
  std::stack<TexturesState> texturesStack;
  std::stack<BuffersState> buffersStack;
  std::stack<ShadersState> shadersStack;

  /*
    Current state of the pipeline.
  */
  GPUState state;

protected:

  /**
      Fill state object with information about all pipeline stages at
      the current moment of time.
  */
  void readState();

  /* ********************************************** */
  /*             Alpha test functions               */
  /* ********************************************** */

/**
      Returns alpha test state.
  */
  virtual AlphaTestState readAlphaTestState() = 0;

  /**
      Sets alpha test state.
      @param state - State of the alpha testing stage.
      @return OK if operation succeeded.
      @return ERROR if error occurred in renderer.
  */
  virtual Outcome writeAlphaTestState(AlphaTestState state) = 0;

  /* ********************************************** */
  /*             Depth test functions               */
  /* ********************************************** */

/**
      Returns depth test state.
  */
  virtual DepthTestState readDepthTestState() = 0;

  /**
      Sets depth test state.
      @param state - State of the depth testing stage.
      @return OK if operation succeeded.
      @return ERROR if error occurred in renderer.
  */
  virtual Outcome writeDepthTestState(DepthTestState state) = 0;

  /* ********************************************** */
  /*               Blending functions               */
  /* ********************************************** */

/**
      Returns current state of blend stage.
      @return Current state of blend stage.
  */
  virtual BlendState readBlendState() = 0;

  /**
      Sets blend state of the pipeline.
      @param state - State of blending operations to set.
      @return OK if operation succeeded.
      @return ERROR if error occurred in renderer.
  */
  virtual Outcome writeBlendState(BlendState state) = 0;

  /* ********************************************** */
  /*               Viewport functions               */
  /* ********************************************** */

/**
      Returns viewport state of pipeline.
      @return ViewportState object that contains information about current
      viewport state of the pipeline.
  */
  virtual ViewportState readViewportState() = 0;

  /**
      Sets viewport using ViewportState object.
      @param state - Viewport state to set.
      @return OK if operation succeeded.
      @return ERROR if error occurred in renderer.
  */
  virtual Outcome writeViewportState(ViewportState state) = 0;

  /* ********************************************** */
  /*                 Color functions                */
  /* ********************************************** */

/**
      Returns current color.
      @return Current color that is used to fill polygons.
  */
  virtual ColorState readColorState() = 0;

  /**
      Sets color state.
      @param state - Color state to make active.
  */
  virtual Outcome writeColorState(ColorState colorState) = 0;

  /* ********************************************** */
  /*               Texture functions                */
  /* ********************************************** */

/**
Returns textures state of the pipeline. It contains texture that are
currently bound, their samplers and texture environment parameters.
@return Current textures state of the pipeline.
*/
  virtual TexturesState readTexturesState() = 0;

  /**
    Sets textures state.
    @param state - Texture state to set.
    @return OK if operation succeeded.
    @return non-OK in case of any error.
  */
  virtual Outcome writeTexturesState(TexturesState state) = 0;

  /* ********************************************** */
      /*                Matrix functions                */
      /* ********************************************** */

  /**
          Returns Matrix state of the pipeline.
          @return Matrix state of the pipeline.
      */
  virtual MatrixState readMatrixState() = 0;

  /**
      Sets the matrix state of the pipeline.
      @param state - New matrix state.
      @return OK if operation succeeded.
      @return non-OK if error occurred.
  */
  virtual Outcome writeMatrixState(MatrixState state) = 0;

  /* ********************************************** */
      /*                 Buffers functions              */
      /* ********************************************** */

  /**
          Returns buffers currently bound to the pipeline and their state.
          @return Buffers currently bound to the pipeline and their state.
      */
  virtual BuffersState readBuffersState() = 0;

  /**
      Sets buffers and their parameters.
      @param state - Structure that contains buffers and their parameters
      @return OK if operation succeeded.
      @return non-OK in case of error.
  */
  virtual Outcome writeBuffersState(BuffersState state) = 0;

  /* ********************************************** */
      /*                 Shaders functions              */
      /* ********************************************** */

  /**
    Returns shaders that is currently bound to the pipeline.
    @return Shaders that is currently bound to the pipeline.
  */
  virtual ShadersState readShadersState() = 0;

  /**
    Binds shaders to the pipeline.
    @param state - State that contains program to bound.
    @return OK if operation succeeded.
    @return non-OK in case of error.
  */
  virtual Outcome writeShadersState(ShadersState state) = 0;

public:
  /**
    Default constructor.
  */
  GPUStateManager();

  /**
      Returns GPUState object that contains information about all pipeline stages at
      the current moment of time.
  */
  GPUState *getState();

  /* ********************************************** */
  /*             Push / Pop functions               */
  /* ********************************************** */

  /**
      Pushes to internal stacks states that are defined in flags
      as a result of logical "or" for different PipelineState enums.
      @param flags - Flags that represents which states should be
      pushed into the stacks.
  */
  virtual void pushStates(ve::uint flags);

  /**
      Pops from internal stacks states that are defined in flags
      as a result of logical "or" for different PipelineState enums.
      @param flags - Flags that represents which states should be
      taken from the stacks.
  */
  virtual void popStates(ve::uint flags);

  /* ********************************************** */
  /*             Alpha test functions               */
  /* ********************************************** */

/**
      Returns alpha test state.
  */
  virtual AlphaTestState getAlphaTestState();

  /**
      Sets alpha test state.
      @param state - State of the alpha testing stage.
      @return OK if operation succeeded.
      @return ERROR if error occurred in renderer.
  */
  virtual Outcome setAlphaTestState(AlphaTestState state);

  /* ********************************************** */
  /*             Depth test functions               */
  /* ********************************************** */

  /**
      Returns depth test state.
  */
  virtual DepthTestState getDepthTestState();

  /**
      Sets depth test state.
      @param state - State of the depth testing stage.
      @return OK if operation succeeded.
      @return ERROR if error occurred in renderer.
  */
  virtual Outcome setDepthTestState(DepthTestState state);

  /* ********************************************** */
  /*               Blending functions               */
  /* ********************************************** */

  /**
      Returns current state of blend stage.
      @return Current state of blend stage.
  */
  virtual BlendState getBlendState();

  /**
      Sets blend state of the pipeline.
      @param state - State of blending operations to set.
      @return OK if operation succeeded.
      @return ERROR if error occurred in renderer.
  */
  virtual Outcome setBlendState(BlendState state);

  /* ********************************************** */
  /*               Viewport functions               */
  /* ********************************************** */

  /**
      Returns viewport state of pipeline.
      @return ViewportState object that contains information about current
      viewport state of the pipeline.
  */
  virtual ViewportState getViewportState();

  /**
      Sets viewport using ViewportState object.
      @param state - Viewport state to set.
      @return OK if operation succeeded.
      @return ERROR if error occurred in renderer.
  */
  virtual Outcome setViewportState(ViewportState state);

  /* ********************************************** */
  /*                 Color functions                */
  /* ********************************************** */

  /**
      Returns current color.
      @return Current color that is used to fill polygons.
  */
  virtual ColorState getColorState();

  /**
      Sets color state.
      @param state - Color state to make active.
  */
  virtual Outcome setColorState(ColorState colorState);

  /* ********************************************** */
  /*               Texture functions                */
  /* ********************************************** */

/**
Returns textures state of the pipeline. It contains texture that are
currently bound, their samplers and texture environment parameters.
@return Current textures state of the pipeline.
*/
  virtual TexturesState getTexturesState();

  /**
    Sets textures state.
    @param state - Texture state to set.
    @return OK if operation succeeded.
    @return non-OK in case of any error.
  */
  virtual Outcome setTexturesState(TexturesState state);

  /* ********************************************** */
      /*                Matrix functions                */
      /* ********************************************** */

      /**
          Returns Matrix state of the pipeline.
          @return Matrix state of the pipeline.
      */
  virtual MatrixState getMatrixState();

  /**
      Sets the matrix state of the pipeline.
      @param state - New matrix state.
      @return OK if operation succeeded.
      @return non-OK if error occurred.
  */
  virtual Outcome setMatrixState(MatrixState state);

  /* ********************************************** */
      /*                 Buffers functions              */
      /* ********************************************** */

      /**
          Returns buffers currently bound to the pipeline and their state.
          @return Buffers currently bound to the pipeline and their state.
      */
  virtual BuffersState getBuffersState();

  /**
      Sets buffers and their parameters.
      @param state - Structure that contains buffers and their parameters
      @return OK if operation succeeded.
      @return non-OK in case of error.
  */
  virtual Outcome setBuffersState(BuffersState state);

  /* ********************************************** */
      /*                 Shaders functions              */
      /* ********************************************** */

  /**
    Returns shaders that is currently bound to the pipeline.
    @return Shaders that is currently bound to the pipeline.
  */
  virtual ShadersState getShadersState();

  /**
    Binds shaders to the pipeline.
    @param state - State that contains program to bound.
    @return OK if operation succeeded.
    @return non-OK in case of error.
  */
  virtual Outcome setShadersState(ShadersState state);

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
  virtual Outcome setClearColorValue(float red, float green, float blue, float alpha) = 0;

  /**
      Sets value for depth buffer clearing.
      @param depth - Depth value to clear depth buffer before rendering.
      @return OK if operation succeeded.
      @return ERROR if error occurred in renderer.
  */
  virtual Outcome setClearDepthValue(float depth) = 0;

  /**
      Changes rendering mode for front or back polygon faces to fill/line mode/point mode.
      @param face - type of the face(s) to change rendering for.
      @param mode - new rendering mode.
      @return OK if operation succeeded.
      @return ERROR if error occurred in renderer.
  */
  virtual Outcome setPolygonMode(Face face, PolygonMode mode) = 0;

  /**
      Sets width for rendered lines.
      @return size - Width to use for line rendering.
      @return OK if operation succeeded.
      @return ERROR if error occurred in renderer.
  */
  virtual Outcome setLineWidth(float size) = 0;

  /**
      Enables or disables (depending on a 'enabled' flag) depth offset for specified faces.
      @param mode - Faces to enable/disable depth offset for.
      @param enabled - passing 'true' enables depth offset and 'false' disables.
      @return OK if operation succeeded.
      @return ERROR if error occurred in renderer.
  */
  virtual Outcome enableDepthOffset(PolygonMode mode, bool enabled) = 0;

  /**
      Sets the scale and bias used to calculate depth values.

      @param rFactor -Specifies a scale factor which is used to create a variable depth offset for each
      polygon. The initial value is 0.
      @param dFactor - Is multiplied by an implementation specific value to create a constant depth offset.
      The initial value is 0.

      @return OK if operation succeeded.
      @return ERROR if error occurred in renderer.
  */
  virtual Outcome depthOffsetParams(float rFactor, float dFactor) = 0;
};

}

#endif // __VE_GPU_STATE_MANAGER_H__
