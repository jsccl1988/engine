// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_ORTHO_CAMERA_H__
#define __VE_ORTHO_CAMERA_H__

#include "engine/cameras/abstract_camera.h"

namespace ve {

class Engine;

/**
    Camera that uses orthogonal projection and may be useful in 2D games.
    This camera class may set four different coordinate systems which are used almost
    in every GUI system / 2D game.
    Use two flags to choose coordinate system: indentity flag and inverse flag.

    Their combinations and resulted coordinate systems:
    <ul>
    <li>indentity = true, inverse = true: Left-upper corner - (0, 0),
    right-bottom - (1, 1). </li>
    <li>indentity = false, inverse = true: Left-upper corner - (0, 0),
    right-bottom - (width, height). </li>
    <li>indentity = false, inverse = false: Left-upper corner - (-width / 2, height / 2),
    right-bottom - (width / 2, -height / 2). </li>
    <li>indentity = true, inverse = false: Left-upper corner - (-1, 1),
    right-bottom - (1, -1). </li>
    </ul>
*/
class OrthoCamera : public AbstractCamera {
private:
  bool identity;
  bool inverse;

public:
  /**
      Constructor.
      @param engine - Engine class that creates this camera.
      @param theViewportState - Viewport state of this camera.
      @param identity - Indentity flag.
      @param inverse - Inverse flag.
  */
  OrthoCamera(Engine *engine, ViewportState theViewportState, bool identity, bool inverse);

  /**
      Applies camera settings. Sets up viewport, modelview and
      projection matrices.
      @return OK if camera settings were applied successfully.
      @return non-OK if error occurred.
  */
  virtual Outcome apply();

  /**
      Sets identity flag for this camera.
      @param value - new value of identity flag.
  */
  void setIdentityFlag(bool value);

  /**
      Returns indenty flag.
      @return Identity flag value.
  */
  bool getIdentityFlag();

  /**
      Sets inverse flag for this camera.
      @param value - new value of inverse flag.
  */
  void setInverseFlag(bool value);

  /**
      Returns inverse flag.
      @return Inverse flag value.
  */
  bool getInverseFlag();
};

}

#endif // __VE_ORTHO_CAMERA_H__
