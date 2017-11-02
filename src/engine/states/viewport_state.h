// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_VIEWPORT_STATE_H__
#define __VE_VIEWPORT_STATE_H__

namespace ve {

/**
    Represents pipeline's viewport state: x, y, width and height parameters.
*/
struct ViewportState {
  int x;
  int y;
  int width;
  int height;

  /**
      Default constructor. All parameters are zeros.
  */
  ViewportState() {
    x = y = width = height = 0;
  }

  /**
      Extended constructor for viewport state.
      @param x - X coordinate of the left-bottom corner of the viewport.
      @param y - Y coordinate of the left-bottom corner of the viewport.
      @param theWidth - Width of the viewport.
      @param theHeight - Width of the viewport.
  */
  ViewportState(int theX, int theY, int theWidth, int theHeight) {
    x = theX;
    y = theY;
    width = theWidth;
    height = theHeight;
  }
};

}

#endif // __VE_VIEWPORT_STATE_H__
