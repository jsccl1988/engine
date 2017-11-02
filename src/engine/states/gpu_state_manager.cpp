// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include <stack>

#include "states/gpu_state_manager.h"

namespace ve {

/**
  Default constructor.
*/
GPUStateManager::GPUStateManager() {
}

/**
    Returns GPUState object that contains information about all pipeline stages at
    the current moment of time.
*/
void GPUStateManager::readState() {
  state.viewportState = readViewportState();
  state.colorState = readColorState();
  state.blendState = readBlendState();
  state.alphaTestState = readAlphaTestState();
  state.depthTestState = readDepthTestState();
  state.texturesState = readTexturesState();
  state.buffersState = readBuffersState();
  state.shadersState = readShadersState();
}

/**
      Returns GPUState object that contains information about all pipeline stages at
      the current moment of time.
  */
GPUState* GPUStateManager::getState() {
  GPUState *newState = new GPUState();
  newState->viewportState = getViewportState();
  newState->colorState = getColorState();
  newState->blendState = getBlendState();
  newState->alphaTestState = getAlphaTestState();
  newState->depthTestState = getDepthTestState();
  newState->texturesState = getTexturesState();
  newState->buffersState = getBuffersState();
  newState->shadersState = getShadersState();
  return newState;
}

/* ********************************************** */
/*             Push / Pop functions               */
/* ********************************************** */

/**
    Pushes to internal stacks states that are defined in flags
    as a result of logical "or" for different PipelineState enums.
    @param flags - Flags that represents which states should be
    pushed into the stacks.
*/
void GPUStateManager::pushStates(ve::uint flags) {
  /* Input assembler states */
  if (flags & BUFFERS_STATE) {
    buffersStack.push(getBuffersState());
  }

  /* Shaders */
  if (flags & SHADERS_STATE) {
    shadersStack.push(getShadersState());
  }

  /* Rasterizer states */
  if (flags & ALPHA_TEST_STATE) {
    alphaStack.push(getAlphaTestState());
  }

  if (flags & DEPTH_TEST_STATE) {
    depthStack.push(getDepthTestState());
  }

  if (flags & BLEND_STATE) {
    blendStack.push(getBlendState());
  }

  if (flags & COLOR_STATE) {
    colorStack.push(getColorState());
  }

  if (flags & TEXTURES_STATE) {
    texturesStack.push(getTexturesState());
  }

  /* Transform states */
  if (flags & VIEWPORT_STATE) {
    viewportStack.push(getViewportState());
  }

  if (flags & MATRIX_STATE) {
    matrixStack.push(getMatrixState());
  }
}

/**
    Pops from internal stacks states that are defined in flags
    as a result of logical "or" for different PipelineState enums.
    @param flags - Flags that represents which states should be
    taken from the stacks.
*/
void GPUStateManager::popStates(ve::uint flags) {
  /* Input assembler states */
  if (flags & BUFFERS_STATE) {
    setBuffersState(buffersStack.top());
    buffersStack.pop();
  }

  /* Shaders */
  if (flags & SHADERS_STATE) {
    setShadersState(shadersStack.top());
    shadersStack.pop();
  }

  /* Rasterizer states */
  if (flags & ALPHA_TEST_STATE) {
    setAlphaTestState(alphaStack.top());
    alphaStack.pop();
  }

  if (flags & DEPTH_TEST_STATE) {
    setDepthTestState(depthStack.top());
    depthStack.pop();
  }

  if (flags & BLEND_STATE) {
    setBlendState(blendStack.top());
    blendStack.pop();
  }

  if (flags & COLOR_STATE) {
    setColorState(colorStack.top());
    colorStack.pop();
  }

  if (flags & TEXTURES_STATE) {
    setTexturesState(texturesStack.top());
    texturesStack.pop();
  }

  /* Transform states */
  if (flags & VIEWPORT_STATE) {
    setViewportState(viewportStack.top());
    viewportStack.pop();
  }

  if (flags & MATRIX_STATE) {
    setMatrixState(matrixStack.top());
    matrixStack.pop();
  }
}

/* ********************************************** */
/*             Alpha test functions               */
/* ********************************************** */

/**
    Returns alpha test state.
*/
AlphaTestState GPUStateManager::getAlphaTestState() {
  return state.alphaTestState;
}

/**
  Sets alpha test state.
  @param state - State of the alpha testing stage.
  @return OK if operation succeeded.
  @return ERROR if error occurred in renderer.
*/
Outcome GPUStateManager::setAlphaTestState(AlphaTestState state) {
  this->state.alphaTestState = state;
  return writeAlphaTestState(state);
}

/* ********************************************** */
/*             Depth test functions               */
/* ********************************************** */

/**
    Returns depth test state.
*/
DepthTestState GPUStateManager::getDepthTestState() {
  return state.depthTestState;
}

/**
    Sets depth test state.
    @param state - State of the depth testing stage.
    @return OK if operation succeeded.
    @return ERROR if error occurred in renderer.
*/
Outcome GPUStateManager::setDepthTestState(DepthTestState state) {
  this->state.depthTestState = state;
  return writeDepthTestState(state);
}

/* ********************************************** */
/*               Blending functions               */
/* ********************************************** */

/**
    Returns current state of blend stage.
    @return Current state of blend stage.
*/
BlendState GPUStateManager::getBlendState() {
  return state.blendState;
}

/**
    Sets blend state of the pipeline.
    @param state - State of blending operations to set.
    @return OK if operation succeeded.
    @return ERROR if error occurred in renderer.
*/
Outcome GPUStateManager::setBlendState(BlendState state) {
  this->state.blendState = state;
  return writeBlendState(state);
}

/* ********************************************** */
/*               Viewport functions               */
/* ********************************************** */

/**
    Returns viewport state of pipeline.
    @return ViewportState object that contains information about current
    viewport state of the pipeline.
*/
ViewportState GPUStateManager::getViewportState() {
  return state.viewportState;
}

/**
    Sets viewport using ViewportState object.
    @param state - Viewport state to set.
    @return OK if operation succeeded.
    @return ERROR if error occurred in renderer.
*/
Outcome GPUStateManager::setViewportState(ViewportState state) {
  this->state.viewportState = state;
  return writeViewportState(state);
}

/* ********************************************** */
/*                 Color functions                */
/* ********************************************** */

/**
    Returns current color.
    @return Current color that is used to fill polygons.
*/
ColorState GPUStateManager::getColorState() {
  return state.colorState;
}

/**
    Sets color state.
    @param state - Color state to make active.
*/
Outcome GPUStateManager::setColorState(ColorState colorState) {
  this->state.colorState = colorState;
  return writeColorState(colorState);
}

/* ********************************************** */
/*               Texture functions                */
/* ********************************************** */

/**
Returns textures state of the pipeline. It contains texture that are
currently bound, their samplers and texture environment parameters.
@return Current textures state of the pipeline.
*/
TexturesState GPUStateManager::getTexturesState() {
  return state.texturesState;
}

/**
  Sets textures state.
  @param state - Texture state to set.
  @return OK if operation succeeded.
  @return non-OK in case of any error.
*/
Outcome GPUStateManager::setTexturesState(TexturesState state) {
  this->state.texturesState = state;
  return writeTexturesState(state);
}

/** ********************************************** */
  /*                Matrix functions                */
  /* ********************************************** */

  /**
      Returns Matrix state of the pipeline.
      @return Matrix state of the pipeline.
  */
MatrixState GPUStateManager::getMatrixState() {
  //return state.matrixState;
  return readMatrixState();
}

/**
    Sets the matrix state of the pipeline.
    @param state - New matrix state.
    @return OK if operation succeeded.
    @return non-OK if error occurred.
*/
Outcome GPUStateManager::setMatrixState(MatrixState state) {
  this->state.matrixState = state;
  return writeMatrixState(state);
}

/* ********************************************** */
  /*                 Buffers functions              */
  /* ********************************************** */

  /**
      Returns buffers currently bound to the pipeline and their state.
      @return Buffers currently bound to the pipeline and their state.
  */
BuffersState GPUStateManager::getBuffersState() {
  return state.buffersState;
}

/**
    Sets buffers and their parameters.
    @param state - Structure that contains buffers and their parameters
    @return OK if operation succeeded.
    @return non-OK in case of error.
*/
Outcome GPUStateManager::setBuffersState(BuffersState state) {
  this->state.buffersState = state;
  return writeBuffersState(state);
}

/* ********************************************** */
  /*                 Shaders functions              */
  /* ********************************************** */

/**
  Returns shaders that is currently bound to the pipeline.
  @return Shaders that is currently bound to the pipeline.
*/
ShadersState GPUStateManager::getShadersState() {
  return state.shadersState;
}

/**
  Binds shaders to the pipeline.
  @param state - State that contains program to bound.
  @return OK if operation succeeded.
  @return non-OK in case of error.
*/
Outcome GPUStateManager::setShadersState(ShadersState state) {
  this->state.shadersState = state;
  return writeShadersState(state);
}

}

