// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include <memory.h>
#include <math.h>

#include "common.h"
#include "math/matrix4f.h"

namespace ve {

Matrix4f::Matrix4f() {
  memset(m, 0, sizeof(m));
  identity();
}

Matrix4f::Matrix4f(float Value) {
  memset(m, 0, sizeof(m));
  m[0][0] = m[1][1] = m[2][2] = Value;
  m[3][3] = 1;
}

Matrix4f::Matrix4f(float *newMatrix) {
  memcpy(m, newMatrix, sizeof(m));
}

Matrix4f::Matrix4f(const Matrix4f &newMatrix) {
  memcpy(m, newMatrix.m, sizeof(m));
}

void Matrix4f::identity() {
  m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0;
}

Matrix4f& Matrix4f::operator = (const Matrix4f &newMatrix) {
  if (this == &newMatrix) return *this;
  memcpy(m, newMatrix.m, sizeof(m));
  return *this;
}

Vector4f Matrix4f::operator * (const Vector4f &a) {
  Vector4f result;
  int i;

  for (i = 0; i < 4; i++) {
    result[i] = m[i][0] * a[0] + m[i][1] * a[1] + m[i][2] * a[2] + m[i][3] * a[3];
  }

  return result;
}

Matrix4f operator * (const Matrix4f &A, const Matrix4f &B) {
  Matrix4f result;
  int i, j, k;

  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      result[i][j] = 0;

      for (k = 0; k < 4; k++) {
        result[i][j] = result[i][j] + A[i][k] * B[k][j];
      }
    }
  }

  return result;
}

float* Matrix4f::operator[] (int index) {
  ERROR_IF((index < 0) || (index > 3), L"Index is out of bounds", NULL);
  return m[index];
}

const float* Matrix4f::operator[] (int index) const {
  ERROR_IF((index < 0) || (index > 3), L"Index is out of bounds", NULL);
  return m[index];
}

void Matrix4f::scale(float factor) {
  m[0][0] *= factor;
  m[1][1] *= factor;
  m[2][2] *= factor;
}

void Matrix4f::translate(const Vector4f &translation) {
  m[0][3] += translation[0];
  m[1][3] += translation[1];
  m[2][3] += translation[2];
}

void Matrix4f::transpose() {
  int i, j;
  float tmp;

  for (i = 0; i < 3; i++)
    for (j = i + 1; j < 4; j++) {
      tmp = m[i][j];
      m[i][j] = m[j][i];
      m[j][i] = tmp;
    }
}

float* Matrix4f::getRaw() {
  return &m[0][0];
}

Matrix4f Matrix4f::xRotateMatrix(float angle) {
  Matrix4f result(1);
  float Cos = (float)cos(angle);
  float Sin = (float)sin(angle);

  result[1][1] = Cos;
  result[1][2] = Sin;
  result[2][1] = -Sin;
  result[2][2] = Cos;
  return result;
}

Matrix4f Matrix4f::yRotateMatrix(float angle) {
  Matrix4f result(1);
  float Cos = (float)cos(angle);
  float Sin = (float)sin(angle);

  result[0][0] = Cos;
  result[0][2] = -Sin;
  result[2][0] = Sin;
  result[2][2] = Cos;
  return result;
}

Matrix4f Matrix4f::zRotateMatrix(float angle) {
  Matrix4f result(1);
  float Cos = (float)cos(angle);
  float Sin = (float)sin(angle);

  result[0][0] = Cos;
  result[0][1] = Sin;
  result[1][0] = -Sin;
  result[1][1] = Cos;
  return result;
}

Matrix4f Matrix4f::getYawPitchRollMatrix(float yaw, float pitch, float roll) {
  Matrix4f result = zRotateMatrix(roll) * yRotateMatrix(yaw) * xRotateMatrix(pitch);
  return result;
}

}
