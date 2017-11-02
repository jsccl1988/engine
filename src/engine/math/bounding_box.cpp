// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "common.h"
#include "math/bounding_box.h"

namespace ve {

BoundingBox::BoundingBox() {
}

BoundingBox::BoundingBox(const BoundingBox& newValue) {
  Size = newValue.Size;
  Corner = newValue.Corner;
}


//FIXME Please review it carefully!
BoundingBox& BoundingBox::operator = (const BoundingBox& newValue) {
  if (this != &newValue) {
    Size = newValue.Size;
    Corner = newValue.Corner;
  }
  return *this;
}

/* Get functions */
Vector3f BoundingBox::getCorner() const {
  return Corner;
}

Vector3f BoundingBox::getSize() const {
  return Size;
}

Vector3f BoundingBox::getPoint(int Index) const {
  const int coeff[8][3] =
  { {0, 0, 0}, {1, 0, 0}, {1, 1, 0}, {0, 1, 0},
      {0, 0, 1}, {1, 0, 1}, {1, 1, 1}, {0, 1, 1}
  };

  ERROR_IF(Index < 0 || Index >= 8, L"Index is out of bounds", Vector3f(0, 0, 0));
  return Vector3f(Corner[0] + coeff[Index][0] * Size[0], Corner[1] + coeff[Index][1] * Size[1], Corner[2] + coeff[Index][2] * Size[2]);
}

/* Set functions */
void BoundingBox::setup(const Vector3f &LeftBottomNearCorner, float newXSize, float newYSize, float newZSize) {
  Corner = LeftBottomNearCorner;
  Size[0] = newXSize;
  Size[1] = newYSize;
  Size[2] = newZSize;
}

void BoundingBox::setCorner(const Vector3f &newCorner) {
  Corner = newCorner;
}

void BoundingBox::setSize(float newXSize, float newYSize, float newZSize) {
  Size[0] = newXSize;
  Size[1] = newYSize;
  Size[2] = newZSize;
}

void BoundingBox::setSize(const Vector3f &newSize) {
  Size = newSize;
}

}
