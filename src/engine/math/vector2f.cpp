// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include <math.h>
#include "common.h"
#include "math/maths.h"
#include "math/vector2f.h"

namespace ve {

Vector2f::Vector2f() {
  x = 0;
  y = 0;
}

Vector2f::Vector2f(const Vector2f &newValue) {
  x = newValue.x;
  y = newValue.y;
}

Vector2f::Vector2f(float newX, float newY) {
  x = newX;
  y = newY;
}

Vector2f& Vector2f::operator = (const Vector2f &newValue) {
  x = newValue.x;
  y = newValue.y;
  return *this;
}

float& Vector2f::operator[] (uint index) {
  switch (index) {
  case 0: return x;
  case 1: return y;
  default: EPIC_FAIL(L"Invalid index");
  }
}

const float Vector2f::operator[] (uint index) const {
  switch (index) {
  case 0: return x;
  case 1: return y;
  default: EPIC_FAIL(L"Invalid index");
  }
}

/**
    Changes vector's components.
    @param x - new value for X component.
    @param y - new value for Y component.
*/
void Vector2f::set(float x, float y) {
  this->x = x;
  this->y = y;
}

Vector2f operator * (const Vector2f &A, float B) {
  Vector2f result(A.x * B, A.y * B);
  return result;
}

Vector2f operator * (float A, const Vector2f &B) {
  Vector2f result(B.x * A, B.y * A);
  return result;
}

Vector2f operator + (const Vector2f &A, const Vector2f &B) {
  Vector2f result(A.x + B.x, A.y + B.y);
  return result;
}

Vector2f operator - (const Vector2f &A, const Vector2f &B) {
  Vector2f result(A.x - B.x, A.y - B.y);
  return result;
}

void Vector2f::norm() {
  double l = x * x + y * y;

  if (!Maths::equals(l, 0)) {
    l = sqrt(l);
    x /= l;
    y /= l;
  }
}

}
