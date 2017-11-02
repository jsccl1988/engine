// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "visible_object.h"

namespace ve {

VisibleObject::VisibleObject() {
  visible = true;
}

void VisibleObject::setVisible(bool value) {
  visible = value;
}

bool VisibleObject::isVisible() {
  return visible;
}

}
