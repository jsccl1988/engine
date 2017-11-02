// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_MATHS_H__
#define __VE_MATHS_H__

#include <cstdlib>
#include <cmath>
#include <ctime>

#include "engine/consts.h"
#include "engine/types.h"
#include "engine/math/vector2f.h"
#include "engine/math/vector3f.h"
#include "engine/math/vector4f.h"
#include "engine/math/plane.h"

namespace ve {

/**
    Class with routine maths operations.
*/
class Maths {
public:
  static double PI;

  /**
      Returns maximum value for two numbers.
  */
  static int max(int a, int b) {
    return a > b ? a : b;
  }

  /**
      Returns maximum value for two numbers.
  */
  static float max(float a, float b) {
    return a > b ? a : b;
  }

  /**
      Returns maximum value for three numbers.
  */
  static int max(int a, int b, int c) {
    return Maths::max(Maths::max(a, b), c);
  }

  /**
      Returns maximum value for three numbers.
  */
  static float max(float a, float b, float c) {
    return Maths::max(Maths::max(a, b), c);
  }

  /**
      Returns absolute value of the float number.
      @param a - float value
      @return Absolute value of a.
  */
  static float abs(float a) {
    return a >= 0 ? a : -a;
  }

  /**
      Returns absolute value of the double precision number.
      @param a - double precision value
      @return Absolute value of a.
  */
  static double abs(double a) {
    return a >= 0 ? a : -a;
  }

  /**
      Clamps value X to specified boundaries using following algorithm:
      <ol>
      <li>If X is less then low bound then low bound will be returned. </li>
      <li>If X is greater then high bound then high bound will be returned. </li>
      <li>If X is between low and high bounds then X will be returned. </li>
      </ol>
      @param x - Value to clamp.
      @param low_bound - Low bound of clamp segment.
      @param high_bound - High bound of clamp segment.
      @return Clamped value.
  */
  static float clamp(float x, float low_bound, float high_bound) {
    if (x < low_bound) {
      return low_bound;
    }

    if (x > high_bound) {
      return high_bound;
    }

    return x;
  }

  /**
      Computes dot product of 2D vectors.
      @param a - First vector
      @param b - Second vector
      @return Dot product of a and b vectors.
  */
  static float dot(const Vector2f a, const Vector2f b) {
    return a[0] * b[0] + a[1] * b[1];
  }

  /**
      Computes dot product of 3D vectors.
      @param a - First vector
      @param b - Second vector
      @return Dot product of a and b vectors.
  */
  static float dot(const Vector3f a, const Vector3f b) {
    return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
  }

  /**
      Computes dot product of 4D vectors.
      @param a - First vector
      @param b - Second vector
      @return Dot product of a and b vectors.
  */
  static float dot(const Vector4f a, const Vector4f b) {
    return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3]);
  }

  /**
      Returns if dot product of plane normal and vector is positive.
      @return 'true' if dot product of plane normal and vector is positive.
  */
  static bool inPositiveHalfSpace(const Plane plane, const Vector3f a) {
    return (plane[0] * a[0] + plane[1] * a[1] + plane[2] * a[2] + plane[3] > 0);
  }

  /**
      Checks if point XOY projection lies inside rectangle
      XOY projection specified by top-left corner and dimensions.
      @param point - Point to check.
      @param corner - Left-top corner of the rectangle area.
      @param width - Width of the rectangle.
      @param height - Height of the rectangle.
  */
  static bool pointInRect(const Vector3f point, const Vector3f corner, float width, float height);

  /**
      Checks if points is inside triangle or not.
      @param point - Point that is needed to be checked.
      @param v1 - The first vertex of the triangle.
      @param v2 - The second vertex of the triangle.
      @param v3 - The third vertex of the triangle.
      @return 'true' if point is inside the triangle and false otherwise.
  */
  static bool isPointInsideTriangle(Vector2f point, Vector2f v1, Vector2f v2, Vector2f v3);

  /**
      Computes cross product of 2D vectors.
      @param a - First vector
      @param b - Second vector
      @return Cross product of a and b vectors.
  */
  static float cross(const Vector2f a, const Vector2f b) {
    return a[0] * b[1] - a[1] * b[0];
  }

  /**
      Computes cross product of 3D vectors.
      @param a - First vector
      @param b - Second vector
      @return Cross product of a and b vectors.
  */
  static Vector3f cross(const Vector3f a, const Vector3f b) {
    return Vector3f(a[1] * b[2] - a[2] * b[1], -a[0] * b[2] + a[2] * b[0],
      a[0] * b[1] - a[1] * b[0]);
  }

  /**
      Returns integer random number from 0 to n-1.
      @param n - Range of random numbers.
      @return Random number.
  */
  static int random(int n) {
    return (rand() % n);
  }

  /**
      Returns float random number from [0, 1) semi-interval.
      @return Random float number.
  */
  static float randomf() {
    return random(10000) / 10000.0f;
  }

  /**
      Check with 1E-6 accuracy if two float numbers are equal.
      @return 'true' if |a - b| less than 1E-6 and 'false' if not.
  */
  static bool equals(float a, float b) {
    return Maths::abs(a - b) < 1e-6;
  }

  /**
      Check with 1E-6 accuracy if two double numbers are equal.
      @return 'true' if |a - b| less than 1E-6 and 'false' if not.
  */
  static bool equals(double a, double b) {
    return Maths::abs(a - b) < 1e-6;
  }

};

}

#endif // __VE_MATHS_H__
