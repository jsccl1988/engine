// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include <memory.h>
#include <math.h>

#include "common.h"
#include "math/matrix3f.h"
#include "math/vector3f.h"

namespace ve {

Matrix3f::Matrix3f() {
  memset(m, 0, sizeof(m));
  m[0][0] = m[1][1] = m[2][2] = 1.0;
}

Matrix3f::Matrix3f(float Value) {
  memset(m, 0, sizeof(m));
  m[0][0] = m[1][1] = m[2][2] = Value;
}

Matrix3f::Matrix3f(float *newMatrix) {
  memcpy(m, newMatrix, sizeof(m));
}

Matrix3f::Matrix3f(const Matrix3f &newMatrix) {
  memcpy(m, newMatrix.m, sizeof(m));
}

Matrix3f& Matrix3f::operator = (const Matrix3f &newMatrix) {
  if (this == &newMatrix) {
    return *this;
  }

  memcpy(m, newMatrix.m, sizeof(m));
  return *this;
}

Vector3f Matrix3f::operator * (const Vector3f &A) {
  Vector3f result;

  for (int i = 0; i < 3; i++) {
    result[i] = m[i][0] * A[0] + m[i][1] * A[1] + m[i][2] * A[2];
  }

  return result;
}

Matrix3f operator * (const Matrix3f &A, const Matrix3f &B) {
  Matrix3f result;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      result[i][j] = 0;

      for (int k = 0; k < 3; k++) {
        result[i][j] += A[i][k] * B[k][j];
      }
    }
  }

  return result;
}

float* Matrix3f::operator[] (int index) {
  ERROR_IF((index < 0) || (index >= 3), L"Index is out of bounds", NULL);
  return m[index];
}

const float* Matrix3f::operator[] (int index) const {
  ERROR_IF((index < 0) || (index >= 3), L"Index is out of bounds", NULL);
  return m[index];
}

Matrix3f Matrix3f::XRotateMatrix(float angle) {
  Matrix3f Result(1);
  float Cos = (float)cos(angle);
  float Sin = (float)sin(angle);

  Result[1][1] = Cos;
  Result[1][2] = Sin;
  Result[2][1] = -Sin;
  Result[2][2] = Cos;
  return Result;
}

Matrix3f Matrix3f::YRotateMatrix(float angle) {
  Matrix3f Result(1);
  float Cos = (float)cos(angle);
  float Sin = (float)sin(angle);

  Result[0][0] = Cos;
  Result[0][2] = -Sin;
  Result[2][0] = Sin;
  Result[2][2] = Cos;
  return Result;
}

Matrix3f Matrix3f::ZRotateMatrix(float angle) {
  Matrix3f Result(1);
  float Cos = (float)cos(angle);
  float Sin = (float)sin(angle);

  Result[0][0] = Cos;
  Result[0][1] = Sin;
  Result[1][0] = -Sin;
  Result[1][1] = Cos;
  return Result;
}

Matrix3f Matrix3f::getYawPitchRollMatrix(float yaw, float pitch, float roll) {
  Matrix3f result = ZRotateMatrix(roll) * YRotateMatrix(yaw) * XRotateMatrix(pitch);
  return result;
}

}
