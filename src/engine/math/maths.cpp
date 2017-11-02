// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "common.h"
#include "math/maths.h"

namespace ve {
double Maths::PI = 3.1415926;

/**
    Checks if point XOY projection lies inside rectangle
    XOY projection specified by top-left corner and dimensions.
    @param point - Point to check.
    @param corner - Left-top corner of the rectangle area.
    @param width - Width of the rectangle.
    @param height - Height of the rectangle.
*/
bool Maths::pointInRect(const Vector3f point, const Vector3f corner, float width, float height) {
  return (point[0] >= corner[0] && point[0] <= corner[0] + width &&
    point[1] >= corner[1] && point[1] <= corner[1] + height);
}

/**
    Checks if points is inside triangle or not.
    @param point - Point that is needed to be checked.
    @param v1 - The first vertex of the triangle.
    @param v2 - The second vertex of the triangle.
    @param v3 - The third vertex of the triangle.
    @return 'true' if point is inside the triangle and false otherwise.
*/
bool Maths::isPointInsideTriangle(Vector2f point, Vector2f v1, Vector2f v2, Vector2f v3) {
  float s1 = Maths::abs(cross(v2 - v1, v3 - v1));
  float s2 = Maths::abs(cross(v1 - point, v2 - point)) +
    Maths::abs(cross(v2 - point, v3 - point)) +
    Maths::abs(cross(v1 - point, v3 - point));

  return Maths::abs(s1 - s2) < 1e-3;
}

}
