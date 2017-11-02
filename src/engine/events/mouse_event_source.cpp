// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include <algorithm>

#include "events/mouse_event_source.h"

namespace ve {

Outcome MouseEventsSource::addMouseListener(AbstractSprite *newListener) {
  // Check that pointer is a valid pointer
  CHECK_POINTER(newListener);

  // Check that there are no duplications
  std::vector<AbstractSprite*>::iterator it = std::find(mouseListener.begin(), mouseListener.end(), newListener);
  ERROR_IF(it != mouseListener.end(), L"Duplication", ERROR);

  // It looks that we may add a new listener
  mouseListener.push_back(newListener);
  return OK;
}

void MouseEventsSource::removeMouseListener(AbstractSprite *listener) {
  std::vector<AbstractSprite*>::iterator it = std::find(mouseListener.begin(), mouseListener.end(), listener);
  if (it != mouseListener.end()) {
    mouseListener.erase(it);
  }
}

void MouseEventsSource::clearMouseListeners() {
  mouseListener.clear();
}

Outcome MouseEventsSource::sendMouseEvent(MouseEvent *mouseEvent) {
  CHECK_POINTER(mouseEvent);
  int len = mouseListener.size();
  int x = mouseEvent->getX();
  int y = mouseEvent->getY();

  for (int i = 0; i < len; i++) {
    AbstractSprite *l = mouseListener[i];
    int newX = floor(x - l->getX());
    int newY = floor(y - l->getY());

    mouseEvent->setX(newX);
    mouseEvent->setY(newY);
    ASSERT(mouseListener[i]->processMouseEvent(mouseEvent));
  }

  return OK;
}

AbstractSprite* MouseEventsSource::getListener(uint index) {
  ERROR_IF(index >= mouseListener.size(), L"Index is out of bound", NULL);
  return mouseListener[index];
}

uint MouseEventsSource::count() {
  return mouseListener.size();
}

}
