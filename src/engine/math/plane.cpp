// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include <math.h>

#include "common.h"
#include "math/plane.h"
#include "math/maths.h"

namespace ve {

Plane::Plane() {
  A = 1.0;
  B = 1.0;
  C = 1.0;
  D = 0.0;
}

Plane::Plane(float newA, float newB, float newC) :A(newA), B(newB), C(newC), D(0) {
}

Plane::Plane(float newA, float newB, float newC, float newD) : A(newA), B(newB), C(newC), D(newD) {
}

Plane::Plane(const Plane &newValue) {
  A = newValue[0];
  B = newValue[1];
  C = newValue[2];
  D = newValue[3];
}

Plane& Plane::operator = (const Plane &newValue) {
  if (this != &newValue) {
    A = newValue[0];
    B = newValue[1];
    C = newValue[2];
    D = newValue[3];
  }
  return *this;
}

float& Plane::operator[] (int index) {
  switch (index) {
  case 0: return A;
  case 1: return B;
  case 2: return C;
  case 3: return D;
  default: EPIC_FAIL(L"Invalid Index");
  }
}

//FIXME Move duplicated code to one method
const float Plane::operator[] (int index) const {
  switch (index) {
  case 0: return A;
  case 1: return B;
  case 2: return C;
  case 3: return D;
  default: EPIC_FAIL(L"Invalid Index");
  }
}

void Plane::norm() {
  float l = A * A + B * B + C * C;

  if (!Maths::equals(l, 0)) {
    l = sqrt(l);
    A = A / l;
    B = B / l;
    C = C / l;
    D = D / l;
  }
}

void Plane::setCoeff(float newA, float newB, float newC, float newD) {
  A = newA;
  B = newB;
  C = newC;
  D = newD;
}

}
