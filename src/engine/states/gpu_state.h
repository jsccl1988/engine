// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_GPU_STATE_H__
#define __VE_GPU_STATE_H__

#include "engine/states/viewport_state.h"
#include "engine/states/blend_state.h"
#include "engine/states/color_state.h"
#include "engine/states/alpha_test_state.h"
#include "engine/states/depth_test_state.h"
#include "engine/states/matrix_state.h"
#include "engine/states/textures_state.h"
#include "engine/states/buffer_state.h"
#include "engine/states/shaders_state.h"

namespace ve {

/**
    Represents GPU state. Contains a lot of information about any stage of pipeline. Useful to debug
    problems during rendering.
*/
class GPUState {
public:
  /**
      Viewport state
  */
  ViewportState viewportState;

  /**
      Blending stage state.
  */
  BlendState blendState;

  /**
      Current color state.
  */
  ColorState colorState;

  /**
      Alpha test state.
  */
  AlphaTestState alphaTestState;

  /**
      Depth test state.
  */
  DepthTestState depthTestState;

  /**
      Transformation matrices state.
  */
  MatrixState matrixState;

  /**
    Texture slots state.
  */
  TexturesState texturesState;

  /**
          Buffers state.
      */
  BuffersState buffersState;

  /**
    Shaders state
  */
  ShadersState shadersState;
};

}

#endif // __VE_GPU_STATE_H__
