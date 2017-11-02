// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include <math.h>

#include "math/maths.h"
#include "math/vector3f.h"
#include "math/vector4f.h"

namespace ve {

Vector4f::Vector4f() {
  x = y = z = 0.0f;
}

Vector4f::Vector4f(const Vector4f &newValue) {
  x = newValue.x;
  y = newValue.y;
  z = newValue.z;
  w = newValue.w;
}

Vector4f::Vector4f(const Vector3f &newValue, float newW) {
  x = newValue[0];
  y = newValue[1];
  z = newValue[2];
  w = newW;
}

Vector4f::Vector4f(float newX, float newY, float newZ, float newW) {
  x = newX;
  y = newY;
  z = newZ;
  w = newW;
}

Vector4f& Vector4f::operator = (const Vector4f &newValue) {
  x = newValue.x;
  y = newValue.y;
  z = newValue.z;
  w = newValue.w;
  return *this;
}

Vector4f& Vector4f::operator = (const Vector3f &newValue) {
  x = newValue[0];
  y = newValue[1];
  z = newValue[2];
  w = 1;
  return *this;
}

float& Vector4f::operator[] (uint index) {
  switch (index) {
  case 0:
    return x;
  case 1:
    return y;
  case 2:
    return z;
  case 3:
    return w;
  default:
    EPIC_FAIL(L"Invalid index");
  }
}

const float Vector4f::operator[] (uint index) const {
  switch (index) {
  case 0:
    return x;
  case 1:
    return y;
  case 2:
    return z;
  case 3:
    return w;
  default:
    EPIC_FAIL(L"Invalid index");
  }
}

void Vector4f::norm() {
  double l = x * x + y * y + z * z + w * w;

  if (!Maths::equals(l, 0)) {
    l = sqrt(l);
    x /= l;
    y /= l;
    z /= l;
    w /= l;
  }
}

Vector4f operator * (Vector4f &A, float B) {
  Vector4f result(A.x * B, A.y * B, A.z * B, A.w * B);
  return result;
}

Vector4f operator * (float A, Vector4f &B) {
  Vector4f result(B.x * A, B.y * A, B.z * A, B.w * A);
  return result;
}

Vector4f operator + (Vector4f &A, Vector4f &B) {
  Vector4f result(A.x + B.x, A.y + B.y, A.z + B.z, A.w + B.w);
  return result;
}

Vector4f operator - (Vector4f &A, Vector4f &B) {
  Vector4f result(A.x - B.x, A.y - B.y, A.z - B.z, A.w - B.w);
  return result;
}

/**
    Changes vector components.
    @param newX - new value for X component.
    @param newY - new value for Y component.
    @param newZ - new value for Z component.
    @param newW - new value for W component.
*/
void Vector4f::set(float newX, float newY, float newZ, float newW) {
  x = newX;
  y = newY;
  z = newZ;
  w = newW;
}

}
