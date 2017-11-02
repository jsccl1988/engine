// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_SIMPLE_SPRITE_H__
#define __VE_SIMPLE_SPRITE_H__

#include "engine/sprites/sprite.h"
#include "engine/ui/border.h"
#include "engine/ui/label.h"
#include "engine/states/buffer_state.h"

namespace ve {

class Engine;

/**
    Sprite which is rendered without textures.
    It is rendered like a rectangular area filled in a constant color, it may has
    border and label inside. It is usefull to create simple interface without any need
    in textures.
*/
class SimpleSprite : public Sprite {
protected:
  Border *border;
  Label *label;
  ColorState colorState;
  BuffersState buffersState;

public:
  /**
      SimpleSprite constructor.
      @param engine - engine which creates this sprite.
  */
  SimpleSprite(Engine *engine);

  /**
      Extended SimpleSprite constructor.
      @param engine - engine which creates this sprite.
      @param theColor - Color of the sprite's area.
  */
  SimpleSprite(Engine *engine, Vector4f theColor);

  /**
      Renders sprite. It is rendered like a quad-area filled
      in a constant color. Then border and label is rendered
      if it was set.
      @return OK if render suceeded.
      @return non-OK in case of engine error.
  */
  virtual Outcome render();

  /**
      Sets border for this sprite.
      @param border - new Border object for this sprite.
  */
  void setBorder(Border *border);

  /**
      Returns border for this sprite.
      @return Border that is used in this sprite.
  */
  Border *getBorder();

  /**
      Sets label for this sprite.
      @param label - new Label object for this sprite.
  */
  void setLabel(Label *label);

  /**
      Sets background color for this sprite.
      @param color - new color for background.
  */
  void setBackgroundColor(Vector4f color);
};

}

#endif
