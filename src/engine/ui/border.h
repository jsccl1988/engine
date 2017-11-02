// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_BORDER_H__
#define __VE_BORDER_H__

#include "engine/common.h"
#include "engine/math/vector4f.h"
#include "engine/ui/ui_control.h"
#include "engine/states/buffer_state.h"

namespace ve {

class UI;

/**
    Border class defines sprite which is usually used for rendering
    boundaries for different interface components: Form, Button, etc.
    It is rendered as lined rectangle with specified line width and line
    color. UI components are not a strict usage for this class.
    Can be used separately as independent sprite.

    <b>Note:</b> Objects of this class must be created only through
    UI::createBorder() function.

    <b>Trick:</b> If several interface components use the same line width
    and line color there is no need to create Border objects with different sizes.
    It is sufficient to create only one and set to all interface components. It
    will works fine, because every interface component resize border component to
    its dimensions before rendering.
*/
class Border : public UIControl {
private:
  /** Border mask, 15 by default */
  uchar mask;
  int lineWidth;
  Vector4f color;
  BuffersState buffersState;

public:
  /** Mask for border sides: What sides to show */
  static const int LEFT = 1;
  static const int UP = 2;
  static const int RIGHT = 4;
  static const int DOWN = 8;
  static const int ALL = 15;

  /**
      Border constructor.
      @param parent - UI object that will be the owner of this border.
  */
  Border(UIContainer *parent);

  /**
      Extended border constructor.
      @param owner - UI object which creates this sprite.
      @param width - Width of this rectangular border.
      @param height - Height of this rectangular border.
      @param color - Color of this rectangular border.
  */
  Border(UIContainer *parent, int width, int height, Vector4f color);

  /**
      Extended border constructor.
      @param owner - UI object which creates this sprite.
      @param color - Color of this rectangular border.
      @param lineWidth - Line width to use for this border.
  */
  Border(UIContainer *parent, Vector4f color, int lineWidth);

  /**
      Renders border as lined rectangular area with specified
      line width and line color.
      @return OK if render succeeded.
      @return non-OK if engine error occurred.
  */
  virtual Outcome render();

  /**
      Sets line width for this border.
      @param newWidth - new line width for this border.
  */
  void setLineWidth(int newWidth);

  /**
      Returns width of lines.
      @return Line width.
  */
  int getLineWidth();

  /**
      Sets line color for this border.
      @param newColor - new line color for this border.
  */
  void setColor(Vector4f newColor);

  /**
      Returns line color.
      @return Line color.
  */
  Vector4f getColor();

  /**
      Sets border mask. Use constants defines in this class to define border mask.
      Only sides defines by this mask will be shown.
      For example: setMask(Border::UP + Border::LEFT) will show only upper and left side.
  */
  void setMask(uchar newMask);

  /**
      Returns border sides mask.
      @return Side mask for this border.
  */
  uchar getMask();
};

}

#endif // __VE_BORDER_H__
