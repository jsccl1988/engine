// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "events/action_event_source.h"

namespace ve {

void ActionEventsSource::addActionListener(ActionListener *newListener) {
  actionListener.push_back(newListener);
}

void ActionEventsSource::clearActionListeners() {
  actionListener.clear();
}

Outcome ActionEventsSource::sendActionEvent(ActionEvent *event) {
  CHECK_POINTER(event);
  int len = actionListener.size();

  for (int i = 0; i < len; i++) {
    ASSERT(actionListener[i]->processActionEvent(event));
  }

  return OK;
}

}
