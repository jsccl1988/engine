// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "common.h"
#include "engines/gl_engine.h"
#include "ui/ui_control.h"
#include "ui/ui.h"

namespace ve {

UIControl::UIControl(UIContainer *parent) :AbstractSprite(GLEngine::getInstance()) {
  this->parent = parent;
  /* Add this control to the parent */
  if (parent) {
    parent->addObject(this);
  }
  enabled = true;
}

Outcome UIControl::processMouseEvent(MouseEvent *event) {
  ASSERT(AbstractSprite::processMouseEvent(event));

  return OK;
}

/* set functions */
void UIControl::setEnabled(bool value) {
  enabled = value;
}

/* get functions */
bool UIControl::isEnabled() {
  return enabled;
}

}
