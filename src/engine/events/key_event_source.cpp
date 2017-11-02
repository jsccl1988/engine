// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include <algorithm>

#include "events/key_event_source.h"

namespace ve {

Outcome KeyEventsSource::addKeyListener(KeyListener *newListener) {
  // Check that pointer is a valid pointer
  CHECK_POINTER(newListener);

  // Check that there are no duplications
  std::vector<KeyListener*>::iterator it = std::find(keyListener.begin(), keyListener.end(), newListener);
  ERROR_IF(it != keyListener.end(), L"Duplication", ERROR);

  // It looks that we may add a new listener
  keyListener.push_back(newListener);
  return OK;
}

void KeyEventsSource::removeKeyListener(KeyListener *listener) {
  std::vector<KeyListener*>::iterator it = std::find(keyListener.begin(), keyListener.end(), listener);
  if (it != keyListener.end()) {
    keyListener.erase(it);
  }
}

void KeyEventsSource::clearKeyListeners() {
  keyListener.clear();
}

Outcome KeyEventsSource::sendKeyEvent(KeyEvent *keyEvent) {
  CHECK_POINTER(keyEvent);
  int len = keyListener.size();

  for (int i = 0; i < len; i++) {
    ASSERT(keyListener[i]->processKeyEvent(keyEvent));
  }

  return OK;
}

}
