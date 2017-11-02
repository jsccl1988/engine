// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "common.h"
#include "ui/panel.h"

namespace ve {

Panel::Panel(UIContainer *parent) :UIControl(parent) {
}

Outcome Panel::render() {
  if (!isVisible()) {
    return OK;
  }

  UNIMPLEMENTED();
  return OK;
}

Outcome Panel::processMouseEvent(MouseEvent *event) {
  CHECK_POINTER(event);
  return OK;
}

Outcome Panel::processKeyEvent(KeyEvent *event) {
  CHECK_POINTER(event);
  return OK;
}

}
