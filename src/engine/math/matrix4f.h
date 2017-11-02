// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_MATRIX4F_H__
#define __VE_MATRIX4F_H__

#include "engine/math/vector4f.h"

namespace ve {

/**
    4x4 matrix class which supports different operations.
    Data is stored row by row in a single array.
*/
class Matrix4f {
private:
  /** Elements */
  float m[4][4];

public:
  /**
      Simple constructor. Identity matrix by default.
  */
  Matrix4f();

  /**
      Extended constructor. Sets matrix:
      (Value 0     0     0)
      (0     Value 0     0)
      (0     0     Value 0)
      (0     0     0     1)
      @param Value - diagonal elements' value.
  */
  Matrix4f(float Value);

  /**
      Extended constructor. Loads elements from specified array, row
      by row from the first to the third.
      @param newMatrix - Array of float values to set to this matrix.
  */
  Matrix4f(float *newMatrix);

  /**
      Copy constructor. Simply copies elements from newMatrix to this matrix.
      @param newMatrix - Matrix to copy elements from.
  */
  Matrix4f(const Matrix4f &newMatrix);

  /**
      Operator "=" which simply copies elements of right-side matrix to this
      matrix.
  */
  Matrix4f& operator = (const Matrix4f &newMatrix);

  /**
      Multiplies this matrix on vector to get resulted vector.
      @param a - Vector to multiply this matrix on.
      @return (This matrix) * ('a' vector).
  */
  Vector4f operator * (const Vector4f &a);

  /**
      Multiplies two 4x4 matrices.
      @param a - First matrix to multiply.
      @param b - Second matrix to multiply.
      @return a * b matrix.
  */
  friend Matrix4f operator * (const Matrix4f &a, const Matrix4f &b);

  /**
      Returns row of this matrix.
      @param index - Index of the row from 0 to 3.
      @return Pointer to row elements array (four elements in the row).
  */
  float *operator[] (int index);

  /**
      Returns row of this matrix.
      @param index - Index of the row from 0 to 2.
      @return Pointer to row elements array (three elements in the row).
  */
  const float *operator[] (int index) const;

  /**
      Scale (0, 0), (1, 1), (2, 2) elements on specified factor.
      @param factor - Scaling factor for mentioned elements.
  */
  void scale(float factor);

  /**
      Adds translation vector to the last column of this matrix, thus
      to elements: (0, 3), (1, 3), (2, 3)
  */
  void translate(const Vector4f &translation);

  /**
      Sets this matrix to identity matrix.
  */
  void identity();

  /**
      Transposes this matrix.
  */
  void transpose();

  /**
      Returns pointer to elements.
      @return pointer to 16 elements of this matrix, row by row.
  */
  float *getRaw();

  /**
      Returns X-axis rotation matrix.
      @param angle - Angle of rotation
      @return Matric which rotates objects around X-axis on specified angle.
  */
  static Matrix4f xRotateMatrix(float angle);

  /**
      Returns Y-axis rotation matrix.
      @param angle - Angle of rotation
      @return Matric which rotates objects around Y-axis on specified angle.
  */
  static Matrix4f yRotateMatrix(float angle);

  /**
      Returns Z-axis rotation matrix.
      @param angle - Angle of rotation
      @return Matric which rotates objects around Z-axis on specified angle.
  */
  static Matrix4f zRotateMatrix(float angle);

  /**
      Returns rotation matrix on specified yaw, pitch and roll angles.
      @param yaw - Yaw angles
      @param pitch - Pitch angles
      @param roll - Roll angles
      @return Matrix which rotates objects on specified yaw, pitch and roll angles.
      @see Euler angles.
  */
  static Matrix4f getYawPitchRollMatrix(float yaw, float pitch, float roll);
};

}

#endif // __VE_MATRIX4F_H__
