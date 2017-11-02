// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "common.h"
#include "ui/checkbox.h"
#include "engines/engine.h"

namespace ve {

static const unsigned DEFAULT_BUTTON_MARGIN = 5;

Checkbox::Checkbox(UIContainer *parent) :UIContainer(parent) {
  label = NULL;
  button = NULL;
}

Checkbox::Checkbox(UIContainer *parent, Button *button, Label *label) : UIContainer(parent) {
  setButton(button);
  button->release();
  setLabel(label);
}

/* Inherited from VisibleObject */
Outcome Checkbox::render() {
  if (!isVisible()) {
    return OK;
  }

  CHECK_POINTER(button);
  ASSERT(engine->beginTransform());
  ASSERT(engine->translate(getX(), getY(), getZ()));
  ASSERT(button->render());

  if (label != NULL) {
    Vector3f pos = label->getPosition();
    ASSERT(label->render());
  }

  ASSERT(engine->endTransform());

  return OK;
}

/* Inherited from ActionListener */
Outcome Checkbox::processActionEvent(ActionEvent *event) {
  return OK;
}

/* set functions */
Outcome Checkbox::setButton(Button *button) {
  CHECK_POINTER(button);

  this->button = button;
  button->setPosition(Vector3f(0, 0, getPosition()[2]));
  button->addActionListener(this);
  button->setStyle(BS_FIXED);

  setSize(button->getWidth(), button->getHeight());

  return OK;
}

void Checkbox::setLabel(Label *label) {
  this->label = label;
}

void Checkbox::setChecked(bool value) {
  if (value == true) {
    button->press();
  } else {
    button->release();
  }
}

/* get functions */
Label* Checkbox::getLabel() {
  return label;
}

Button* Checkbox::getButton() {
  return button;
}

bool Checkbox::isChecked() {
  return button->isPressed();
}

}
