// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_ABSTRACT_CAMERA_H__
#define __VE_ABSTRACT_CAMERA_H__

#include "engine/common.h"
#include "engine/states/viewport_state.h"

namespace ve {

class Engine;

/**
    Abstract camera class. It contains only one parameter - viewport
    state that is set to the pipeline in apply().
*/
class AbstractCamera {
protected:
  /** Engine that is used to set up camera settings */
  Engine *engine;

  /** Viewport state of this camera. */
  ViewportState viewport;

public:
  /**
      Constructor.
      @param engine - Engine object that is used in this camera object
      to set up rendering parameters.
      @param theViewport - Viewport state of this camera.
  */
  AbstractCamera(Engine *engine, ViewportState theViewport);

  /**
      Changes viewport for this camera.
      @param newViewport - new viewport state for this camera.
  */
  void setViewport(ViewportState newViewport);

  /**
      Applies camera settings. Sets up viewport, modelview and
      projection matrices.
      @return OK if camera settings were applied successfully.
      @return non-OK if engine error occurred.
  */
  virtual Outcome apply();
};

}

#endif // __VE_ABSTRACT_CAMERA_H__
