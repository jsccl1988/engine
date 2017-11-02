// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "cameras/abstract_camera.h"
#include "engines/engine.h"

namespace ve {

/**
    Constructor.
    @param engine - Engine object which will be used in this camera object
    to set up rendering parameters.
    @param theViewport - Viewport state which will be applied when this camera
    is active.
*/
AbstractCamera::AbstractCamera(Engine *engine, ViewportState theViewport) {
  this->engine = engine;
  viewport = theViewport;
}

/**
    Changes viewport for this camera.
    @param newViewport - new viewport state for this camera.
*/
void AbstractCamera::setViewport(ViewportState newViewport) {
  viewport = newViewport;
}

/**
    Applies camera settings. Sets up viewport, modelview and
    projection matrices.
    @return OK if camera settings were applied successfully.
    @return non-OK if engine error occurred.
*/
Outcome AbstractCamera::apply() {
  ASSERT(engine->getStateManager()->setViewportState(viewport));
  return OK;
}

}
