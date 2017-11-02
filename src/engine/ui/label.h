// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_LABEL_H__
#define __VE_LABEL_H__

#include <string>

#include "engine/common.h"
#include "engine/math/maths.h"
#include "engine/ui/ui_control.h"
#include "engine/fonts/font.h"

namespace ve {

/**
    Label interface component.
    Label's properties which can be changed:
    <ul>
    <li>Text - string which is used in rendering.</li>
    <li>Color of the text. </li>
    <li>Font of the text. </li>
    <li>Length bound. This property is used in rendering. If text length in pixels is
    greater than length bound then only last part of the text will be shown (which is not longer
    than Length bound (in pixels).)
    </ul>
*/
class Label : public UIControl {
private:
  std::wstring text;
  Vector4f color;
  Font *font;
  int lengthBound;

public:
  /**
      Label constructor.
      @param parent - UI container that will be the owner of this label.
  */
  Label(UIContainer *parent);

  /**
      Extended label constructor.
      @param parent - UI container that will be the owner of this label.
      @param theText - Text which is contained in the label.
      @param  theColor - Text color.
  */
  Label(UIContainer *parent, std::wstring &theText,
    const Vector4f &theColor = Vector4f(1.0, 1.0, 1.0, 1.0));

  /**
      Renders this label.
      @return OK if render succeeded.
      @return non-OK if engine error occurred.
  */
  virtual Outcome render();

  /**
      Sets text for this label.
      @param newText - new text for this label.
  */
  void setText(std::wstring newText);

  /**
      Sets text color for this label.
      @param newColor - new text color for this label.
  */
  void setColor(Vector4f newColor);

  /**
      Sets font for this label.
      @param newFont - new font for this label.
  */
  void setFont(Font *newFont);

  /**
      Sets text bound for this label. Set 0 to disable
      text length control.
      @param length - new value for text length in pixels or
      0 if length control disabled.
  */
  void setLengthBound(uint length);

  /**
      Returns this label's text.
      @return Text of this label.
  */
  std::wstring getText();

  /**
      Returns text color.
      @return Text color of this label.
  */
  Vector4f getColor();

  /**
      Returns font which is used for rendering.
      @return Font which is used to render text.
  */
  Font* getFont();
};

}

#endif // __VE_LABEL_H_
