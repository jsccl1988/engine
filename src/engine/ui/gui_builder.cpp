// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "math/maths.h"
#include "ui/gui_builder.h"
#include "tools/texture_tool.h"
#include "engines/engine.h"

namespace ve {

Sprite* GUIBuilder::createSpriteFromFile(Engine *engine, std::string fileName) {
  Texture *texture = TextureTool::loadFromFile(engine, fileName, false);
  ERROR_IF(texture == NULL, L"Failed to create texture", NULL);

  Sprite *newSprite = new Sprite(engine);
  ERROR_IF(newSprite == NULL, L"NULL Pointer", NULL);

  newSprite->setTexture(texture);
  newSprite->setSize(texture->getDesc().width, texture->getDesc().height);

  return newSprite;
}

Button* GUIBuilder::createButtonFromFiles(Engine *engine, UI *gui, UIContainer *parent,
  std::string baseImage, std::string coveredImage, std::string pressedImage) {
  ve::uint width = 0;
  ve::uint height = 0;

  Sprite *base = createSpriteFromFile(engine, baseImage);
  ERROR_IF(base == NULL, L"NULL Pointer", NULL);

  Sprite *covered = NULL;
  if (coveredImage == baseImage) {
    covered = base;
  } else {
    covered = createSpriteFromFile(engine, coveredImage);
    ERROR_IF(covered == NULL, L"NULL Pointer", NULL);
  }

  Sprite *pressed = NULL;
  if (pressedImage == baseImage) {
    pressed = base;
  } else if (pressedImage == coveredImage) {
    pressed = covered;
  } else {
    pressed = createSpriteFromFile(engine, pressedImage);
    ERROR_IF(pressed == NULL, L"NULL Pointer", NULL);
  }

  width = Maths::max(base->getWidth(), covered->getWidth(), pressed->getWidth());
  height = Maths::max(base->getHeight(), covered->getHeight(), pressed->getHeight());

  Button *newButton = gui->createButton(parent, width, height);
  ERROR_IF(newButton == NULL, L"NULL Pointer", NULL);

  newButton->setSprites(base, pressed, covered);

  return newButton;
}

}
