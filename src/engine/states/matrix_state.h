// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_MATRIX_STATE_H__
#define __VE_MATRIX_STATE_H__

#include "engine/math/matrix4f.h"

namespace ve {

  /**
      Represent state of the worldview & projection matrices.
      */
  class MatrixState {
  public:
    /* World View Matrix */
    Matrix4f worldView;

    /* Projection Matrix */
    Matrix4f projection;

    /**
        Default constructor.
        */
    MatrixState() {
    }

    MatrixState(Matrix4f worldViewMatrix, Matrix4f projectionMatrix) {
      worldView = worldViewMatrix;
      projection = projectionMatrix;
    }
  };

}

#endif // __VE_MATRIX_STATE_H__
