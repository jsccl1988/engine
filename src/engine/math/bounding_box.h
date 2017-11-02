// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_BOUNDING_BOX_H__
#define __VE_BOUNDING_BOX_H__

#include "math/vector3f.h"

namespace ve {

/**
    For future usage. Possibly it needs redesign.
*/
class BoundingBox {
private:
  Vector3f Size;
  Vector3f Corner;

public:
  BoundingBox();
  BoundingBox(const BoundingBox& newValue);
  BoundingBox& operator = (const BoundingBox& newValue);
  /* Get functions */
  Vector3f getCorner() const;
  Vector3f getSize() const;
  Vector3f getPoint(int Index) const;
  /* Set functions */
  void setup(const Vector3f &LeftBottomNearCorner, float newXSize, float newYSize, float newZSize);
  void setCorner(const Vector3f &newCorner);
  void setSize(float newXSize, float newYSize, float newZSize);
  void setSize(const Vector3f &newSize);
};

}

#endif // __VE_BOUNDING_BOX_H__
