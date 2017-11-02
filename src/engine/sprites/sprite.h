// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_SPRITE_H__
#define __VE_SPRITE_H__

#include "engine/common.h"
#include "engine/visible_object.h"
#include "engine/textures/texture.h"
#include "engine/math/vector3f.h"
#include "engine/math/vector2f.h"
#include "engine/sprites/abstract_sprite.h"
#include "engine/states/alpha_test_state.h"
#include "engine/states/blend_state.h"
#include "engine/states/color_state.h"
#include "engine/states/textures_state.h"
#include "engine/states/buffer_state.h"

namespace ve {

class Engine;

/**
    Sprite is an quad object with defined texture,
    texture coords and several other properties which makes
    it flexible for drawing game units, interface components and so on.

    Color filter (r, g, b, a) may be applied during rendering in this way:
    DestComponent = FilterComponent * SourceComponent, thus
    component values are multiplied on this filter.
    (1, 1, 1, 1) - default value for it. It may be used for effects like
    "active object selection". Set it to (1, 0, 0, 0) for example to
    draw only red component.
*/
class Sprite : public AbstractSprite {
private:
  /** Texture coordinates for 4 vertices of sprite */
  Vector2f texCoord[4];

  /** Sprite texture */
  TexturesState texturesState;

  /**
      Defines alpha test state which should be applied before rendering.
  */
  AlphaTestState alphaTestState;

  /**
      Defines blend state which should be applied before
      rendering.
  */
  BlendState blendState;

  /**
      Color filter (r, g, b, a) applies such transform during rendering:
      DestComponent = FilterComponent * SourceComponent, thus
      component values are multiplied on this filter.
      (1, 1, 1, 1) - default value for it.
  */
  ColorState colorState;

  /**
    It is used to set buffers for rendering.
  */
  BuffersState buffersState;

public:
  /**
      Sprite constructor. Sprite objects must be created only through
      Engine::createSprite() function.
      @param engine - engine which creates this sprite.
  */
  Sprite(Engine *engine);

  /**
      Renders sprite.
      @return OK if render operations succeeded.
      @return ERROR if engine error occurred.
  */
  virtual Outcome render();

  /**
      Set texture coordinates for vertex specified
      by index.
      @param index - specifies number of vertex to set texture
      coordinates. Must be from 0 to 3 inclusive.
      @param newTexCoord - new values for texture coordinates.
      @return OK if operation succeeded.
      @return ERROR if index is out of [0, 3] bounds.
  */
  Outcome setTexCoords(int index, Vector2f newTexCoord);

  /**
      Set texture coordinates for vertex specified
      by index.
      @param index - specifies number of vertex to set texture
      coordinates. Must be from 0 to 3 inclusive.
      @param s - S texture coordinate.
      @param t - T texture coordinate.
      @return OK if operation succeeded.
      @return ERROR if index is out of [0, 3] bounds.
  */
  Outcome setTexCoords(int index, float s, float t);

  /**
      Sets texture for this sprite.
@param newTexture - The texture that will be set to the first slot
of textures state that is used during rendering.
  */
  void setTexture(Texture* newTexture);

  /**
        Sets textures state that is used during rendering.
  @param state - Textures state that should be used during rendering.
    */
  void setTexturesState(TexturesState state);

  /**
      Returns texture coordinates for vertex specified by index.
      @param index - number of vertex. It must be from 0
      to 3 inclusive.
      @return texture coordinates for specified vertex
      if index is correct or (0, 0) in case of incorrect case.
  */
  Vector2f getTexCoords(int index);

  /**
      Return pointer to a texture which is used to render this sprite.
      @return pointer to a Texture class.
  */
  Texture* getTexture();

  /**
      Sets alpha test option for this sprite. Use this state to avoid rendering
      transparent pixels.
      @param newAlphaTestState - Alpha test state for the rendering.
  */
  virtual void setAlphaTestState(AlphaTestState newAlphaTestState);

  /**
      Sets blend state which should be applied before
      rendering.
      @param newBlendState - pointer to a blend state or
      NULL if there is no need in blending. NULL is default
      value for any sprite.
  */
  virtual void setBlendState(BlendState newBlendState);

  /**
      Returns blend state which is applied before rendering
      or NULL if sprite does not use blending.
      @return pointer to a blend state object or NULL if
      sprite does not use blending during rendering.
  */
  BlendState getBlendState();

  /**
      Enables transparency. Transparency of each pixel of the sprite depends on
      alpha component of the texture. Transparency is enabled by default.
      Both alpha test and blending will be enabled.
  */
  void enableTransparency();

  /**
      Disables transparency. It means that every pixel will be non-transparent. Alpha
      component of the texture is ignored. Transparency is enabled by default.
      Both alpha test and blending will be disabled.
  */
  void disableTransparency();

  /**
      Sets new color filter for this sprite.

      Color filter (r, g, b, a) applies such transform during rendering:
      DestComponent = FilterComponent * SourceComponent, thus
      component values are multiplied on this filter.
      (1, 1, 1, 1) - default value for it.
      @param newColorState - New value for color filter vector.
  */
  void setColorState(ColorState newColorState);

  /**
      Returns color filter for this sprite.
      @return Color filter vector that is used for rendering.
  */
  ColorState getColorState();
};

}

#endif // __VE_SPRITE_H__
