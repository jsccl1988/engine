// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_VECTOR4F_H__
#define __VE_VECTOR4F_H__

#include "engine/math/vector3f.h"
#include "engine/common.h"

namespace ve {

/**
    4D Vector.
*/
class Vector4f {
private:
  /** Vector components */
  float x;
  float y;
  float z;
  float w;

public:
  /**
      Simple constructor.
      Default vector: (0, 0, 0)
  */
  Vector4f();

  /**
      Copy constructor.
      @param newValue - 4D Vector to copy data from.
  */
  Vector4f(const Vector4f &newValue);

  /**
      Extended constructor. Gets first three components
      from 3D vector and the last from specified W value.
      @param newValue - Vector to get three components from.
      @param newW - W component for this vector.
  */
  Vector4f(const Vector3f &newValue, float newW);

  /**
      Extended constructor.
      @param newX - X component.
      @param newY - Y component.
      @param newZ - Z component.
      @param newW - W component.
  */
  Vector4f(float newX, float newY, float newZ, float newW);

  /**
      operator =
      @param newValue - 4D Vector to copy value from.
  */
  Vector4f& operator = (const Vector4f &newValue);

  /**
      operator =. Copies data from 3D vector and set W component to 1.
      @param newValue - 3D Vector to copy value from.
  */
  Vector4f& operator = (const Vector3f &newValue);

  /**
      Returns vector component (X, Y, Z or W)
      @param index - Component index to return (from 0 to 3)
      @return X, Y, Z or W component respectively.
  */
  float& operator[] (uint index);

  /**
      Returns vector component (X, Y, Z or W)
      @param index - Component index to return (from 0 to 3)
      @return X, Y, Z or W component respectively.
  */
  const float operator[] (uint index) const;

  friend Vector4f operator * (Vector4f &A, float B);
  friend Vector4f operator * (float A, Vector4f &B);
  friend Vector4f operator + (Vector4f &A, Vector4f &B);
  friend Vector4f operator - (Vector4f &A, Vector4f &B);

  /**
      Normalizes this vector.
  */
  void norm();

  /**
      Changes vector components.
      @param newX - new value for X component.
      @param newY - new value for Y component.
      @param newZ - new value for Z component.
      @param newW - new value for W component.
  */
  void set(float newX, float newY, float newZ, float newW);
};

}

#endif // __VE_VECTOR4F_H__
