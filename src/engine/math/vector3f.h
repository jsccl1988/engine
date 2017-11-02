// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_VECTOR3F_H__
#define __VE_VECTOR3F_H__

#include "engine/common.h"

namespace ve {

/**
    3D Vector.
*/
class Vector3f {
private:
  /** Vector components */
  float x;
  float y;
  float z;

public:
  /**
      Simple constructor.
      Default vector: (0, 0, 0)
  */
  Vector3f();

  /**
      Copy constructor.
      @param newValue - 3D Vector to copy data from.
  */
  Vector3f(const Vector3f &newValue);

  /**
      Extended constructor.
      @param newX - X component.
      @param newY - Y component.
      @param newZ - Z component.
  */
  Vector3f(float newX, float newY, float newZ);

  /**
      operator =
      @param newValue - 3D Vector to copy value from.
  */
  Vector3f& operator = (const Vector3f &newValue);

  /**
      Returns vector component (X, Y or Z)
      @param index - Component index to return (from 0 to 2)
      @return X, Y or Z component respectively.
  */
  float& operator[] (uint index);

  /**
      Returns vector component (X, Y or Z)
      @param index - Component index to return (from 0 to 2)
      @return X, Y or Z component respectively.
  */
  const float operator[] (uint index) const;

  friend Vector3f operator * (const Vector3f &A, float B);
  friend Vector3f operator * (float A, const Vector3f &B);
  friend Vector3f operator + (const Vector3f &A, const Vector3f &B);
  Vector3f operator += (const Vector3f &A);
  friend Vector3f operator - (const Vector3f &A, const Vector3f &B);

  /**
      Normalizes this vector.
  */
  void norm();

  /**
      Sets components of this vector.
      @param newX - X component.
      @param newY - Y component.
      @param newZ - Z component.
  */
  void set(float newX, float newY, float newZ);
};

}

#endif // __VE_VECTOR3F_H__
