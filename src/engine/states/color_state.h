// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_COLOR_STATE_H__
#define __VE_COLOR_STATE_H__

#include "engine/math/vector4f.h"

namespace ve {

/**
    Represents pipeline's current color state: R, G, B, A parameters.
*/
struct ColorState {
  float r;
  float g;
  float b;
  float a;

  ColorState() {
    r = g = b = a = 1.0f;
  }

  /**
      Extended constructor.
      @param color - The initial color state.
  */
  ColorState(Vector4f color) {
    r = color[0];
    g = color[1];
    b = color[2];
    a = color[3];
  }

  /**
      Extended constructor. Alpha component will be set to 1.0f
      @param theRed - red component of color state.
      @param theGreen - green component of color state.
      @param theBlue - blue component of color state.
  */
  ColorState(float theRed, float theGreen, float theBlue) {
    r = theRed;
    g = theGreen;
    b = theBlue;
    a = 1.0f;
  }

  /**
          Extended constructor.
          @param theRed - red component of color state.
          @param theGreen - green component of color state.
          @param theBlue - blue component of color state.
          @param theAlpha - alpha component of color state.
      */
  ColorState(float theRed, float theGreen, float theBlue, float theAlpha) {
    r = theRed;
    g = theGreen;
    b = theBlue;
    a = theAlpha;
  }

  /**
      Sets color components for this state.
      @param theRed - red component of color state.
      @param theGreen - green component of color state.
      @param theBlue - blue component of color state.
      @param theAlpha - alpha component of color state.
  */
  void set(float newRed, float newGreen, float newBlue, float newAlpha) {
    r = newRed;
    g = newGreen;
    b = newBlue;
    a = newAlpha;
  }
};

}

#endif // __VE_COLOR_STATE_H__
