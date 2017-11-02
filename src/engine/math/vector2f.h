// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_VECTOR2F_H__
#define __VE_VECTOR2F_H__

#include "engine/common.h"

namespace ve {

/**
    2D Vector.
*/
class Vector2f {
private:
  /** Vector components */
  float x;
  float y;

public:
  /**
      Simple constructor.
      Default vector: (0, 0)
  */
  Vector2f();

  /**
      Copy constructor.
      @param newValue - 2D Vector to copy data from.
  */
  Vector2f(const Vector2f &newValue);

  /**
      Extended constructor.
      @param newX - X component.
      @param newY - Y component.
  */
  Vector2f(float newX, float newY);

  /**
      operator =
      @param newValue - 2D Vector to copy value from.
  */
  Vector2f& operator = (const Vector2f &newValue);

  /**
      Returns vector component (X or Y)
      @param index - Component index to return (0 or 1)
      @return X or Y component respectively.
  */
  float& operator[] (uint index);

  /**
      Returns vector component (X or Y)
      @param index - Component index to return (0 or 1)
      @return X or Y component respectively.
  */
  const float operator[] (uint index) const;

  friend Vector2f operator * (const Vector2f &A, float B);
  friend Vector2f operator * (float A, const Vector2f &B);
  friend Vector2f operator + (const Vector2f &A, const Vector2f &B);
  friend Vector2f operator - (const Vector2f &A, const Vector2f &B);

  /**
      Changes vector's components.
      @param x - new value for X component.
      @param y - new value for Y component.
  */
  void set(float x, float y);

  /**
      Normalizes this vector.
  */
  void norm();
};

}

#endif // __VE_VECTOR2F_H__
