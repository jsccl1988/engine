// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "common.h"
#include "math/maths.h"
#include "math/frustum.h"

namespace ve {

Frustum::Frustum() {
  update();
}

void Frustum::update() {
  float proj[16];
  float view[16];
  float clip[16];

  // Get ModelViewProjetion matrix
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glGetFloatv(GL_MODELVIEW_MATRIX, view);
  glGetFloatv(GL_PROJECTION_MATRIX, proj);
  glLoadMatrixf(proj);
  glMultMatrixf(view);
  glGetFloatv(GL_MODELVIEW_MATRIX, clip);
  glPopMatrix();

  // Left clipping plane
  frustum[0].setCoeff(clip[3] + clip[0], clip[7] + clip[4], clip[11] + clip[8], clip[15] + clip[12]);
  // Right clipping plane
  frustum[1].setCoeff(clip[3] - clip[0], clip[7] - clip[4], clip[11] - clip[8], clip[15] - clip[12]);
  // Top clipping plane
  frustum[2].setCoeff(clip[3] - clip[1], clip[7] - clip[5], clip[11] - clip[9], clip[15] - clip[13]);
  // Bottom clipping plane
  frustum[3].setCoeff(clip[3] + clip[1], clip[7] + clip[5], clip[11] + clip[9], clip[15] + clip[13]);
  // Near clipping plane
  frustum[4].setCoeff(clip[3] + clip[2], clip[7] + clip[6], clip[11] + clip[10], clip[15] + clip[14]);
  // Far clipping plane
  frustum[5].setCoeff(clip[3] - clip[2], clip[7] - clip[6], clip[11] - clip[10], clip[15] - clip[14]);
}

bool Frustum::isVisible(Vector3f point) {
  int i;

  for (i = 0; i < 6; i++)
    if (!Maths::inPositiveHalfSpace(frustum[i], point))
      return false;

  return true;
}

bool Frustum::isVisible(BoundingBox boundingBox) {
  Vector3f point[8];
  int i, j;
  bool flag;

  for (i = 0; i < 8; i++)
    point[i] = boundingBox.getPoint(i);

  for (i = 0; i < 6; i++) {
    flag = true;

    for (j = 0; j < 8; j++)
      if (Maths::inPositiveHalfSpace(frustum[i], point[j])) {
        flag = false;
        break;
      }

    if (flag == true) {
      return false;
    }
  }
  return true;
}

}
