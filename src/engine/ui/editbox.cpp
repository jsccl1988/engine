// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "ui/ui.h"
#include "ui/editbox.h"
#include "tools/string_tool.h"
#include "engines/engine.h"

namespace ve {

Editbox::Editbox(UIContainer *parent) :UIContainer(parent) {
  background = NULL;
  activeBackground = NULL;
  isActive = false;
  label = new Label(this);
  filter = NULL;
}

Editbox::~Editbox() {
  delete label;
}

Outcome Editbox::render() {
  if (!isVisible()) {
    return OK;
  }

  ASSERT(engine->beginTransform());
  ASSERT(engine->translate(getX(), getY(), getZ()));

  if (isActive == true && activeBackground != NULL) {
    activeBackground->setSize(getWidth(), getHeight());
    ASSERT(activeBackground->render());
  } else {
    if (background != NULL) {
      background->setSize(getWidth(), getHeight());
      ASSERT(background->render());
    }
  }

  if (label->getFont() != NULL) {
    ASSERT(engine->beginTransform());
    ASSERT(engine->translate(5, (getHeight() - label->getFont()->getHeight()) / 2, 0));
    ASSERT(label->render());
    ASSERT(engine->endTransform());
  }

  ASSERT(engine->endTransform());

  return OK;
}

Outcome Editbox::processMouseEvent(MouseEvent *event) {
  CHECK_RESULT(UIControl::processMouseEvent(event), L"Mouse event processing failed");

  if (event->getType() == MOUSE_PRESS) {
    isActive = isCovered();
  }

  return OK;
}

Outcome Editbox::processKeyEvent(KeyEvent *event) {
  if (isActive && event->getType() == KEY_PRESS) {
    wchar_t code = event->getKeyCode();
    int len = label->getText().length();

    if ((filter != NULL && filter->accept(label->getText(), code)) ||
      (filter == NULL && StringTool::isPrintable(code))
      ) {
      label->setLengthBound(getWidth() - 5);
      label->setText(label->getText() + (wchar_t)code);
    }

    /// FIXME: Ugly code
    if ((code & 0xFF) == 8 && len > 0) {
      label->setText(label->getText().substr(0, len - 1));
    }
  }
  return OK;
}

void Editbox::setBackgroundSprite(AbstractSprite *background) {
  this->background = background;
}

AbstractSprite* Editbox::getBackgroundSprite() {
  return background;
}

void Editbox::setActiveBackgroundSprite(AbstractSprite *activeBackground) {
  this->activeBackground = activeBackground;
}

AbstractSprite* Editbox::getActiveBackgroundSprite() {
  return activeBackground;
}

Label* Editbox::getLabel() {
  return label;
}

/**
    Sets filter for content.
    @param newFilter - new Editbox filter for content.
*/
void Editbox::setFilter(EditboxFilter *newFilter) {
  filter = newFilter;
}

}
