// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_PLANE_H__
#define __VE_PLANE_H__

namespace ve {

/**
    Planes representation in format: A * x + B * y + C * z + D = 0
*/
class Plane {
private:
  /** Normal */
  float A;
  float B;
  float C;
  float D;

public:
  /**
      Simple constructor.
      Default plane: x + y + z = 0
  */
  Plane();

  /**
      Extended constructor to set plane:
      A * x + B * y + C * z = 0
      @param newA - A parameter.
      @param newB - B parameter.
      @param newC - C parameter.
  */
  Plane(float newA, float newB, float newC);

  /**
      Extended constructor to set plane:
      A * x + B * y + C * z + D = 0
      @param newA - A parameter.
      @param newB - B parameter.
      @param newC - C parameter.
      @param newD - D parameter.
  */
  Plane(float newA, float newB, float newC, float newD);

  /**
      Copy constructor. Copies (A, B, C, D) plane parameters.
  */
  Plane(const Plane &newValue);

  /**
      Copies (A, B, C, D) plane parameters.
  */
  Plane& operator = (const Plane &newValue);

  /**
      Returns plane coefficient specified by index (from 0 to 3)
      @param index - index of plane parameter to return (from 0 to 3)
      @return from A to D respectively.
  */
  float& operator[] (int index);

  /**
      Returns plane coefficient specified by index (from 0 to 3)
      @param index - index of plane parameter to return (from 0 to 3)
      @return from A to D respectively.
  */
  const float operator[] (int index) const;

  /**
      Normalize normal vector (A, B, C) for this plane.
  */
  void norm();

  /**
      Sets plane parameters to specify plane in format:
      A * x + B * y + C * z + D = 0
      @param newA - A parameter.
      @param newB - B parameter.
      @param newC - C parameter.
      @param newD - D parameter.
  */
  void setCoeff(float newA, float newB, float newC, float newD);
};

}

#endif // __VE_PLANEF_H__
