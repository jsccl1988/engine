// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "common.h"
#include "cameras/camera.h"
#include "math/maths.h"
#include "math/vector3f.h"
#include "math/matrix3f.h"
#include "engines/engine.h"

namespace ve {

Camera::Camera(Engine *engine, ViewportState theViewportState) :AbstractCamera(engine, theViewportState) {
  position = Vector3f(0, 0, 0);
  look = Vector3f(1, 0, 0);
  up = Vector3f(0, 0, 1);
  zFar = 700;
  fovy = 80;
  zNear = 0.1f;
  norm();
}

Camera::Camera(Engine *engine, ViewportState theViewportState,
  Vector3f &newPosition, Vector3f &newLook, Vector3f &newUp) :AbstractCamera(engine, theViewportState) {
  position = newPosition;
  look = newLook;
  up = newUp;
  zFar = 700;
  fovy = 80;
  zNear = 0.1f;
  norm();
}

void Camera::norm() {
  look.norm();
  up.norm();
  side = Maths::cross(up, look);
  side.norm();
}

Outcome Camera::apply() {
  float width = (float)viewport.width;
  float height = (float)viewport.height;

  ASSERT(AbstractCamera::apply());
  ASSERT(engine->enableMatrix(PROJECTION));
  ASSERT(engine->loadIdentityMatrix());
  ASSERT(engine->multPerspectiveMatrix(fovy, width / height, zNear, zFar));
  ASSERT(engine->enableMatrix(MODELVIEW));
  ASSERT(engine->loadIdentityMatrix());
  ASSERT(engine->multLookAtMatrix(position, position + look, up));
  return OK;
}

void Camera::setAngles(float newYaw, float newPitch, float newRoll) {
  Matrix3f transform = Matrix3f::getYawPitchRollMatrix(newYaw, newPitch, newRoll);
  look = transform * Vector3f(1, 0, 0);
  side = transform * Vector3f(0, 1, 0);
  up = transform * Vector3f(0, 0, 1);
  norm();
}

void Camera::move(float offset) {
  position += offset * look;
}

void Camera::sideMove(float offset) {
  position += offset * side;
}

Vector3f Camera::getPosition() {
  return position;
}

Vector3f Camera::getLook() {
  return look;
}

Vector3f Camera::getUp() {
  return up;
}

Vector3f Camera::getSide() {
  return side;
}

float Camera::getZFar() {
  return zFar;
}

/* Set functions */
void Camera::setPosition(const Vector3f newPosition) {
  position = newPosition;
}

void Camera::setLook(const Vector3f newLook) {
  look = newLook;
  norm();
}

void Camera::setUp(const Vector3f newUp) {
  up = newUp;
  norm();
}

void Camera::setZFar(float newZFar) {
  zFar = newZFar;
}

void Camera::setZNear(float newZNear) {
  zNear = newZNear;
}

void Camera::setFovy(float newFovy) {
  fovy = newFovy;
}

}
