// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "common.h"
#include "sprites/sprite.h"
#include "math/maths.h"
#include "engines/engine.h"
#include "tools/texture_tool.h"
#include "states/gpu_state_manager.h"

namespace ve {

Sprite::Sprite(Engine *engine) :AbstractSprite(engine) {
  texCoord[0] = Vector2f(0, 0);
  texCoord[1] = Vector2f(1, 0);
  texCoord[2] = Vector2f(1, 1);
  texCoord[3] = Vector2f(0, 1);

  enableTransparency();
  colorState.set(1, 1, 1, 1);

  buffersState.indices.data = NULL;
  buffersState.normals.data = NULL;
  buffersState.texCoords = BufferDesc(2, FLOAT, 0, NULL, false);
  buffersState.vertices = BufferDesc(3, FLOAT, 0, NULL, false);
}

/* Inherited from VisibleObject */
Outcome Sprite::render() {
  if (isVisible() == false) {
    return OK;
  }

  float x = getX();
  float y = getY();
  float z = getZ();
  float w = getWidth();
  float h = getHeight();

  float vertices[] = { 0, h, 0,
                        w, h, 0,
                        w, 0, 0,
                        0, 0, 0
  };

  float tCoords[] = { texCoord[0][0], texCoord[0][1],
                      texCoord[1][0], texCoord[1][1],
                      texCoord[2][0], texCoord[2][1],
                      texCoord[3][0], texCoord[3][1]
  };

  GPUStateManager *stateManager = engine->getStateManager();

  ASSERT(engine->beginTransform());
  ASSERT(engine->translate(x, y, z));

  buffersState.vertices.data = vertices;
  buffersState.texCoords.data = tCoords;

  stateManager->pushStates(ALPHA_TEST_STATE | BLEND_STATE | COLOR_STATE | TEXTURES_STATE | BUFFERS_STATE);

  ASSERT(stateManager->setBuffersState(buffersState));
  ASSERT(stateManager->setAlphaTestState(alphaTestState));
  ASSERT(stateManager->setBlendState(blendState));
  ASSERT(stateManager->setColorState(colorState));
  ASSERT(stateManager->setTexturesState(texturesState));
  ASSERT(engine->drawPrimitives(QUADS, 0, 4));

  stateManager->popStates(ALPHA_TEST_STATE | BLEND_STATE | COLOR_STATE | TEXTURES_STATE | BUFFERS_STATE);

  ASSERT(engine->endTransform());

  return OK;
}

Outcome Sprite::setTexCoords(int index, Vector2f newTexCoord) {
  ERROR_IF(index < 0 || index >= 4, L"Index is out of bounds", ERROR);
  texCoord[index] = newTexCoord;
  return OK;
}

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
Outcome Sprite::setTexCoords(int index, float s, float t) {
  ERROR_IF(index < 0 || index >= 4, L"Index is out of bounds", ERROR);
  texCoord[index] = Vector2f(s, t);
  return OK;
}

void Sprite::setTexture(Texture *newTexture) {
  texturesState.slots[0] = newTexture;
  TextureDesc desc = newTexture->getDesc();
  if (TextureTool::isNPOTSTexture(newTexture)) {
    texCoord[0] = Vector2f(0, 0);
    texCoord[1] = Vector2f(desc.width, 0);
    texCoord[2] = Vector2f(desc.width, desc.height);
    texCoord[3] = Vector2f(0, desc.height);
  } else {
    texCoord[0] = Vector2f(0, 0);
    texCoord[1] = Vector2f(1, 0);
    texCoord[2] = Vector2f(1, 1);
    texCoord[3] = Vector2f(0, 1);
  }
}

/**
      Sets textures state that is used during rendering.
  @param state - Textures state that should be used during rendering.
  */
void Sprite::setTexturesState(TexturesState state) {
  texturesState = state;
}

Vector2f Sprite::getTexCoords(int index) {
  ERROR_IF(index < 0 || index >= 4, L"Index is out of bounds", Vector2f(0, 0));
  return texCoord[index];
}

Texture* Sprite::getTexture() {
  return texturesState.slots[0];
}

void Sprite::setAlphaTestState(AlphaTestState alphaTestState) {
  this->alphaTestState = alphaTestState;
}

void Sprite::setBlendState(BlendState newBlendState) {
  blendState = newBlendState;
}

BlendState Sprite::getBlendState() {
  return blendState;
}

/**
    Sets new color filter for this sprite.

    Color filter (r, g, b, a) applies such transform during rendering:
    DestComponent = FilterComponent * SourceComponent, thus
    component values are multiplied on this filter.
    (1, 1, 1, 1) - default value for it.
    @param newColorState - New value for color filter vector.
*/
void Sprite::setColorState(ColorState newColorState) {
  this->colorState = newColorState;
}

/**
    Returns color filter for this sprite.
    @return Color filter vector that is used for rendering.
*/
ColorState Sprite::getColorState() {
  return colorState;
}

void Sprite::enableTransparency() {
  alphaTestState.isEnabled = true;
  alphaTestState.func = GREATER;
  alphaTestState.refValue = 0;

  blendState.isEnabled = true;
  blendState.sourceFactor = SRC_ALPHA;
  blendState.destFactor = ONE_MINUS_SRC_ALPHA;
}

void Sprite::disableTransparency() {
  /* Both alpha test and blending will be disabled */
  alphaTestState.isEnabled = false;
  blendState.isEnabled = false;
}

}
