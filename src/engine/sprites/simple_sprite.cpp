// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "sprites/simple_sprite.h"
#include "engines/engine.h"

namespace ve {

SimpleSprite::SimpleSprite(Engine *engine) :Sprite(engine) {
  border = NULL;
  label = NULL;
  buffersState.vertices = BufferDesc(2, FLOAT, 0, 0, false);
}

SimpleSprite::SimpleSprite(Engine *engine, Vector4f theColor) :Sprite(engine) {
  colorState = ColorState(theColor);
  border = NULL;
  label = NULL;
  buffersState.vertices = BufferDesc(2, FLOAT, 0, 0, false);
}

void SimpleSprite::setBorder(Border *border) {
  this->border = border;
}

/**
    Returns border for this sprite.
    @return Border that is used in this sprite.
*/
Border* SimpleSprite::getBorder() {
  return border;
}

void SimpleSprite::setLabel(Label *label) {
  this->label = label;
}

void SimpleSprite::setBackgroundColor(Vector4f color) {
  colorState = ColorState(color);
}

Outcome SimpleSprite::render() {
  float width = getWidth();
  float height = getHeight();
  float vertices[] = { 0, 0, 0, height, width, height, width, 0 };
  GPUStateManager *stateManager = engine->getStateManager();

  ASSERT(engine->beginTransform());
  ASSERT(engine->translate(getX(), getY(), getZ()));

  stateManager->pushStates(COLOR_STATE | BUFFERS_STATE);

  buffersState.vertices.data = vertices;
  ASSERT(stateManager->setColorState(colorState));
  ASSERT(stateManager->setBuffersState(buffersState));
  ASSERT(engine->drawPrimitives(QUADS, 0, 4));

  stateManager->popStates(COLOR_STATE | BUFFERS_STATE);

  if (border != NULL) {
    border->setSize(width, height);
    ASSERT(border->render());
  }

  if (label != NULL) {
    label->setSize(width, height);
    ASSERT(label->render());
  }

  ASSERT(engine->endTransform());

  return OK;
}

}
