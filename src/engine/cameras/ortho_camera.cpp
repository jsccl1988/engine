// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "common.h"
#include "cameras/ortho_camera.h"
#include "engines/engine.h"

namespace ve {

/**
    Constructor.
    @param engine - Engine class that creates this camera.
    @param theViewport - Viewport state which will be applied when this camera is active.
    @param indentity - Indentity flag.
    @param inverse flag - Inverse flag.
*/
OrthoCamera::OrthoCamera(Engine *engine, ViewportState theViewportState,
  bool identity, bool inverse) :AbstractCamera(engine, theViewportState) {
  this->identity = identity;
  this->inverse = inverse;
}

/**
    Applies camera settings. Sets up viewport, modelview and
    projection matrices.
    @return OK if camera settings were applied successfully.
    @return non-OK if engine error occurred.
*/
Outcome OrthoCamera::apply() {
  float width = (float)viewport.width;
  float height = (float)viewport.height;

  ASSERT(AbstractCamera::apply());
  ASSERT(engine->enableMatrix(PROJECTION));
  ASSERT(engine->loadIdentityMatrix());
  ASSERT(engine->enableMatrix(MODELVIEW));
  ASSERT(engine->loadIdentityMatrix());

  if (!identity && inverse) {
    ASSERT(engine->scale(2.0f / width, -2.0f / height, 1.0f));
    ASSERT(engine->translate(-width / 2.0f, -height / 2.0f, 0.0f));
  }

  if (identity && inverse) {
    ASSERT(engine->scale(2.0, -2.0, 1.0));
    ASSERT(engine->translate(-0.5, -0.5, 0.0));
  }

  if (!identity && !inverse) {
    ASSERT(engine->scale(2.0f / width, 2.0f / height, 1.0f));
  }

  return OK;
}

/**
    Sets identity flag for this camera.
    @param value - new value of identity flag.
*/
void OrthoCamera::setIdentityFlag(bool value) {
  identity = value;
}

/**
    Returns indenty flag.
    @return Identity flag value.
*/
bool OrthoCamera::getIdentityFlag() {
  return identity;
}

/**
    Sets inverse flag for this camera.
    @param value - new value of inverse flag.
*/
void OrthoCamera::setInverseFlag(bool value) {
  inverse = value;
}

/**
    Returns inverse flag.
    @return Inverse flag value.
*/
bool OrthoCamera::getInverseFlag() {
  return inverse;
}

}
