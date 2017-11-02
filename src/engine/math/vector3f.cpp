// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include <math.h>
#include "math/maths.h"
#include "math/vector3f.h"
#include "common.h"

namespace ve {

Vector3f::Vector3f() {
  x = y = z = 0.0f;
}

Vector3f::Vector3f(const Vector3f &newValue) {
  x = newValue.x;
  y = newValue.y;
  z = newValue.z;
}

Vector3f::Vector3f(float newX, float newY, float newZ) {
  x = newX;
  y = newY;
  z = newZ;
}

Vector3f& Vector3f::operator = (const Vector3f &newValue) {
  x = newValue.x;
  y = newValue.y;
  z = newValue.z;
  return *this;
}

float& Vector3f::operator[] (uint index) {
  switch (index) {
  case 0: return x;
  case 1: return y;
  case 2: return z;
  default: EPIC_FAIL(L"Invalid Index");
  }
}

//FIXME Move duplicated code to one method
const float Vector3f::operator[] (uint index) const {
  switch (index) {
  case 0: return x;
  case 1: return y;
  case 2: return z;
  default: EPIC_FAIL(L"Invalid Index");
  }
}

Vector3f operator * (const Vector3f &A, float B) {
  Vector3f result(A.x * B, A.y * B, A.z * B);
  return result;
}

Vector3f operator * (float A, const Vector3f &B) {
  Vector3f result(B.x * A, B.y * A, B.z * A);
  return result;
}

Vector3f operator + (const Vector3f &A, const Vector3f &B) {
  Vector3f result(A.x + B.x, A.y + B.y, A.z + B.z);
  return result;
}

Vector3f Vector3f::operator += (const Vector3f &A) {
  x += A.x;
  y += A.y;
  z += A.z;

  return *this;
}

Vector3f operator - (const Vector3f &A, const Vector3f &B) {
  Vector3f result(A.x - B.x, A.y - B.y, A.z - B.z);
  return result;
}

void Vector3f::norm() {
  double l = x * x + y * y + z * z;

  if (!Maths::equals(l, 0)) {
    l = sqrt(l);
    x /= l;
    y /= l;
    z /= l;
  }
}

void Vector3f::set(float newX, float newY, float newZ) {
  x = newX;
  y = newY;
  z = newZ;
}

}
