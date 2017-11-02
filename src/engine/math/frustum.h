// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_FRUSTUM_H__
#define __VE_FRUSTUM_H__

#include "consts.h"
#include "types.h"
#include "math/bounding_box.h"
#include "math/plane.h"

namespace ve {

/**
    Class for operations with camera's frustum (which consists of six planes).
    <b>FIXME:</b>Need redesign.
*/
class Frustum {
private:
  /**
      Frustum planes.
  */
  Plane frustum[6];

public:
  /**
      Simple constructor.
  */
  Frustum();

  /**
      <b>FIXME:</b>This function needs reimplementation, because it uses OpenGL functions.
      It seems that Camera class should be added as parameter.
  */
  void update();

  /**
      Check if point is visible in this frustum.
      @param point - Point to check if it is inside this frustum.
      @return 'true' if it is inside and 'false' if not.
  */
  bool isVisible(Vector3f point);

  /**
      Check if bounding box is visible in this forum.
      @param boundingBox - Bounding box to check if it is inside frustum.
      It is considered that bounding box is inside this frustum if at least
      one point of this box is visible.
  */
  bool isVisible(BoundingBox boundingBox);
};

}

#endif // __VE_FRUSTUM_H__
