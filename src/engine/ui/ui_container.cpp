// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include <algorithm>

#include "common.h"
#include "ui/ui_container.h"

namespace ve {

UIContainer::UIContainer(UIContainer *parent) :UIControl(parent) {
}

Outcome UIContainer::addObject(AbstractSprite *newControl) {
  CHECK_POINTER(newControl);
  objects.push_back(newControl);
  addMouseListener(newControl);
  addKeyListener(newControl);
  return OK;
}

void UIContainer::removeObject(AbstractSprite *object) {
  std::vector<AbstractSprite*>::iterator it = std::find(objects.begin(), objects.end(), object);
  if (it != objects.end()) {
    objects.erase(it);
  }
  removeMouseListener(object);
  removeKeyListener(object);
}

Outcome UIContainer::clearObjects() {
  objects.clear();
  clearMouseListeners();
  clearKeyListeners();
  return OK;
}

uint UIContainer::getObjectsCount() {
  return objects.size();
}

AbstractSprite* UIContainer::getObject(uint index) {
  ERROR_IF(index >= objects.size(), L"Index is out of bounds", NULL);
  return objects[index];
}

Outcome UIContainer::processMouseEvent(MouseEvent *event) {
  ASSERT(UIControl::processMouseEvent(event));

  switch (event->getType()) {
  case MOUSE_MOTION:
  {
    int x = ((MouseEvent*)event)->getX();
    int y = ((MouseEvent*)event)->getY();
    uint len = objects.size();

    for (uint i = 0; i < len; i++) {
      AbstractSprite *iControl = objects[i];

      if (x >= iControl->getX() && x <= iControl->getX() + iControl->getWidth() &&
        y >= iControl->getY() && y <= iControl->getY() + iControl->getHeight()) {
        if (!iControl->isCovered()) {
          MouseEvent *me = new MouseEvent(MOUSE_ENTER, (MouseButton)0, x, y, x - (int)iControl->getX(),
            y - (int)iControl->getY());
          ASSERT(iControl->processMouseEvent(me));
          delete me;
        }
      } else {
        if (iControl->isCovered()) {
          MouseEvent *me = new MouseEvent(MOUSE_LEAVE, (MouseButton)0, x, y, x - (int)iControl->getX(),
            y - (int)iControl->getY());
          ASSERT(iControl->processMouseEvent(me));
          delete me;
        }
      }
    }
  }
  default:
    break;
  }

  ASSERT(sendMouseEvent(event));
  return OK;
}

Outcome UIContainer::processKeyEvent(KeyEvent *event) {
  ASSERT(sendKeyEvent(event));
  return OK;
}

}
