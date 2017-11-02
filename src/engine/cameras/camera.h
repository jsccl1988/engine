// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_CAMERA_H__
#define __VE_CAMERA_H__

#include "engine/cameras/abstract_camera.h"
#include "engine/math/vector3f.h"

namespace ve {

class Engine;

/**
    Class to manage viewer's position and orientation in 3D space.
    Vectors to define camera state:
    <ul>
    <li>Position - position of the camera</li>
    <li>Look vector - direction of camera view (vector, non a position of object to look at)</li>
    <li>Up vector - normal vector for look vector for correct camera orientation.</li>
    </ul>
*/
class Camera : public AbstractCamera {
private:
  /** Camera's position. */
  Vector3f position;

  /** Camera's view vector */
  Vector3f look;

  /** Camera's 'up' vector */
  Vector3f up;

  /**
      Camera's 'side' vector: Cross product of
      'up' and 'look' vectors
  */
  Vector3f side;

  /**
      Specifies the distance from the viewer to the closest clipping plane.
      This value must be positive.
  */
  float zNear;

  /**
      Specifies the distance from the viewer to the farthest clipping plane.
      This value must be positive.
  */
  float zFar;

  /**
      View angle.
  */
  float fovy;

protected:
  /**
      Normalizes 'look' and 'up' vectors, recomputes 'side' vector.
  */
  void norm();

public:
  /**
      Constructor.
      @param engine - Engine object that creates this camera.
      @param theViewportState - Viewport state of this camera.
  */
  Camera(Engine *engine, ViewportState theViewportState);

  /**
      Constructor.
      @param engine - Engine object that creates this camera.
      @param theViewportState - Viewport state of this camera is active.
      @param newPosition - position of this camera.
      @param newLook - 'look' vector of this camera.
      @param newUp - 'up' vector of this camera.
  */
  Camera(Engine *engine, ViewportState theViewportState,
    Vector3f &newPosition, Vector3f &newLook, Vector3f &newUp);

  virtual Outcome apply();

  /**
      Sets camera orientation using Euler angles.
      @param newYaw - yaw angle.
      @param newPitch - pitch angle.
      @param newRoll - roll angle.
  */
  void setAngles(float newYaw, float newPitch, float newRoll);

  /**
      Move camera position along 'look' vector by 'offset' units.
      @param offset - Camera movement along 'look' vector.
  */
  void move(float offset);

  /**
      Move camera position along 'side' vector where 'side' =
      cross product of 'up' and 'look' vectors.
      @param offset - Camera movement along 'side' vector.
  */
  void sideMove(float offset);

  /**
      Returns position of this camera.
      @return position of this camera.
  */
  Vector3f getPosition();

  /**
      Returns 'look' vector of this camera.
      @return 'look' vector of this camera.
  */
  Vector3f getLook();

  /**
      Returns 'up' vector of this camera.
      @return 'up' vector of this camera.
  */
  Vector3f getUp();

  /**
      Returns 'side' vector of this camera.
      @return 'side' vector of this camera.
  */
  Vector3f getSide();

  /**
      Returns distance from the viewer to the farthest clipping plane.
      @return Distance from the viewer to the farthest clipping plane..
  */
  float getZFar();

  /**
      Sets new position for this camera.
      @param newPosition - New position for this camera.
  */
  void setPosition(const Vector3f newPosition);

  /**
      Sets new 'look' vector for this camera.
      @param newLook - New 'look' vector for this camera.
  */
  void setLook(const Vector3f newLook);

  /**
      Sets new 'up' vector for this camera.
      @param newUp - New 'up' vector for this camera.
  */
  void setUp(const Vector3f newUp);

  /**
      Specifies the distance from the viewer to the closest clipping plane.
      This value must be positive.
      @param newZNear - Distance from the viewer to the closest clipping plane.
      This value must be positive
  */
  void setZNear(float newZNear);

  /**
      Specifies the distance from the viewer to the farthest clipping plane.
      This value must be positive.
      @param newZNear - Distance from the viewer to the farthest clipping plane.
      This value must be positive
  */
  void setZFar(float newZFar);

  /**
      Set view angle of this camera.
      @param newFovy - New view angle of this camera.
  */
  void setFovy(float newFovy);
};

}

#endif // __VE_CAMERA_H__
