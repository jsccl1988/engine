// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "common.h"
#include "ui/form.h"
#include "math/matrix3f.h"
#include "math/maths.h"
#include "ui/ui_container.h"
#include "events/system_event.h"
#include "events/mouse_event.h"
#include "engines/engine.h"

namespace ve {

Form::Form(UIContainer *parent) :UIContainer(parent) {
  movable = false;
  isLeftMouseButtonPressed = false;
  captionSprite = NULL;
  backgroundSprite = NULL;
  border = NULL;
}

/* Inherited from VisibleObject */
Outcome Form::render() {
  if (!isVisible()) {
    return OK;
  }

  ERROR_IF(captionSprite == NULL && backgroundSprite == NULL && border == NULL,
    L"Nothing to render. Is this an intend?", ERROR);

  Vector3f pos = getPosition();
  int width = getWidth();
  int height = getHeight();

  if (captionSprite != NULL) {
    captionSprite->setSize(width, 20); ///FIXME: Define caption size
    ASSERT(engine->beginTransform());
    ASSERT(engine->translate(pos[0], pos[1], pos[2]));
    ASSERT(captionSprite->render());
    ASSERT(engine->endTransform());
  }

  if (backgroundSprite != NULL) {
    backgroundSprite->setSize(width, height - 20);
    ASSERT(engine->beginTransform());
    ASSERT(engine->translate(pos[0], pos[1] + 20, pos[2])); ///FIXME: Define caption size
    ASSERT(backgroundSprite->render());
    ASSERT(engine->endTransform());
  }

  if (border != NULL) {
    border->setSize(width, height);
    ASSERT(engine->beginTransform());
    ASSERT(engine->translate(pos[0], pos[1], pos[2]));
    ASSERT(border->render());
    ASSERT(engine->endTransform());
  }

  ASSERT(engine->beginTransform());
  ASSERT(engine->translate(getX(), getY() + 20, getZ())); /// FIXME: Caption size
  int len = getObjectsCount();
  for (int i = 0; i < len; i++) {
    ASSERT(getObject(i)->render());
  }

  ASSERT(engine->endTransform());

  return OK;
}

/* Inherited from MouseListener */
Outcome Form::processMouseEvent(MouseEvent *event) {
  int x = event->getX();
  int y = event->getY();

  ///FIX THIS DIRTY CODE!!!
  event->setY(event->getY() - 20);
  ASSERT(UIContainer::processMouseEvent(event));
  event->setY(event->getY() + 20);

  bool isInside = x >= 0 && y >= 0 && x < getWidth() && y < getHeight();

  switch (event->getType()) {
  case MOUSE_RELEASE:
    isLeftMouseButtonPressed = false;
    break;

  case MOUSE_PRESS:
    if (isInside && y < 20)     ///FIXME:: Caption size
    {
      isLeftMouseButtonPressed = true;
      oldX = event->getMouseX();
      oldY = event->getMouseY();
    }
    break;

  case MOUSE_MOTION:
    if (isLeftMouseButtonPressed == true && movable == true) {
      setPosition(getPosition() + Vector3f(event->getMouseX() - oldX, event->getMouseY() - oldY, 0));
      oldX = event->getMouseX();
      oldY = event->getMouseY();
    }
    break;

  case MOUSE_ENTER:
  case MOUSE_LEAVE:
    break;

  default:
    UNIMPLEMENTED();
    break;
  }

  return OK;
}

/* Set functions */
void Form::setBackground(AbstractSprite* background) {
  backgroundSprite = background;
}

void Form::setCaption(AbstractSprite* caption) {
  captionSprite = caption;
}

bool Form::onCanMove(int x, int y) {
  return false;
}

AbstractSprite* Form::getCaptionSprite() {
  return captionSprite;
}

AbstractSprite* Form::getBackgroundSprite() {
  return backgroundSprite;
}

void Form::setBorder(Border *border) {
  this->border = border;
}

void Form::setMovable(bool isEnabled) {
  movable = isEnabled;
}

}
