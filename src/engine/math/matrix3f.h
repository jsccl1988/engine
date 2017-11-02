// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_MATRIX3F_H__
#define __VE_MATRIX3F_H__

#include "math/vector3f.h"

namespace ve {

/**
    3x3 matrix class which supports different operations.
    Data is stored row by row in a single array.
*/
class Matrix3f {
private:
  /** Elements */
  float m[3][3];

public:
  /**
      Simple constructor. Identity matrix by default.
  */
  Matrix3f();

  /**
      Extended constructor. Set specified value for all
      diagonal elements. The rest elements have zero values.
      @param Value - diagonal elements' value.
  */
  Matrix3f(float Value);

  /**
      Extended constructor. Loads elements from specified array, row
      by row from the first to the third.
      @param newMatrix - Array of float values to set to this matrix.
  */
  Matrix3f(float *newMatrix);

  /**
      Copy constructor. Simply copies elements from newMatrix to this matrix.
      @param newMatrix - Matrix to copy elements from.
  */
  Matrix3f(const Matrix3f &newMatrix);

  /**
      Operator "=" which simply copies elements of right-side matrix to this
      matrix.
  */
  Matrix3f& operator = (const Matrix3f &newMatrix);

  /**
      Multiplies this matrix on vector to get resulted vector.
      @param A - Vector to multiply this matrix on.
      @return (This matrix) * (A vector).
  */
  Vector3f operator * (const Vector3f &A);

  /**
      Multiplies two 3x3 matrices.
      @param A - First matrix to multiply.
      @param B - Second matrix to multiply.
      @return A * B matrix.
  */
  friend Matrix3f operator * (const Matrix3f &A, const Matrix3f &B);

  /**
      Returns row of this matrix.
      @param index - Index of the row from 0 to 2.
      @return Pointer to row elements array (three elements in the row).
  */
  float *operator[] (int index);

  /**
      Returns row of this matrix.
      @param index - Index of the row from 0 to 2.
      @return Pointer to row elements array (three elements in the row).
  */
  const float *operator[] (int index) const;

  /**
      Returns X-axis rotation matrix.
      @param angle - Angle of rotation
      @return Matric which rotates objects around X-axis on specified angle.
  */
  static Matrix3f XRotateMatrix(float angle);

  /**
      Returns Y-axis rotation matrix.
      @param angle - Angle of rotation
      @return Matric which rotates objects around Y-axis on specified angle.
  */
  static Matrix3f YRotateMatrix(float angle);

  /**
      Returns Z-axis rotation matrix.
      @param angle - Angle of rotation
      @return Matric which rotates objects around Z-axis on specified angle.
  */
  static Matrix3f ZRotateMatrix(float angle);

  /**
      Returns rotation matrix on specified yaw, pitch and roll angles.
      @param yaw - Yaw angles
      @param pitch - Pitch angles
      @param roll - Roll angles
      @return Matrix which rotates objects on specified yaw, pitch and roll angles.
      @see Euler angles.
  */
  static Matrix3f getYawPitchRollMatrix(float yaw, float pitch, float roll);
};

}

#endif // __VE_MATRIX3F_H__
