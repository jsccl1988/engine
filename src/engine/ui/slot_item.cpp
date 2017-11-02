// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include <algorithm>
#include <limits>

#include "ui/slot_item.h"

namespace ve {

SlotItem::SlotItem(UIContainer *parent) :UIControl(parent) {
  sprite = NULL;
  currentSlot = NULL;
  dragging = false;
}

SlotItem::SlotItem(UIContainer *parent, AbstractSprite *sprite) :UIControl(parent) {
  this->sprite = sprite;
  currentSlot = NULL;
  dragging = false;
}

SlotItem::~SlotItem() {
}

void SlotItem::setSprite(AbstractSprite *sprite) {
  this->sprite = sprite;
}

Outcome SlotItem::setSlot(Slot *slot) {
  /* Check pointer */
  CHECK_POINTER(slot);

  currentSlot = slot;
  setPosition(slot->getX() + (slot->getWidth() - getWidth()) / 2,
    slot->getY() + (slot->getHeight() - getHeight()) / 2);

  return OK;
}

void SlotItem::addSlot(Slot *slot) {
  slots.push_back(slot);
}

void SlotItem::clearSlots() {
  currentSlot = 0;
  slots.clear();
}

void SlotItem::removeSlot(Slot *slot) {
  std::vector<Slot*>::iterator i = std::find(slots.begin(), slots.end(), slot);
  if (i != slots.end()) {
    slots.erase(i);

    if (slot == currentSlot) {
      currentSlot = 0;
    }
  }
}

void SlotItem::drop() {
  currentSlot = NULL;
}

Outcome SlotItem::render() {
  CHECK_POINTER(sprite);

  if (currentSlot != NULL) {
    sprite->setPosition(getPosition());
    sprite->setSize(getWidth(), getHeight());
    return sprite->render();
  }

  return OK;
}

Outcome SlotItem::processMouseEvent(MouseEvent *event) {
  ASSERT(UIControl::processMouseEvent(event));

  switch (event->getType()) {
  case MOUSE_MOTION:
    if (dragging) {
      setPosition(getX() + event->getMouseX() - oldMousePos[0],
        getY() + event->getMouseY() - oldMousePos[1]);
      oldMousePos[0] = static_cast<float>(event->getMouseX());
      oldMousePos[1] = static_cast<float>(event->getMouseY());
    }
    break;

  case MOUSE_PRESS:
    if (isCovered()) {
      dragging = true;
      oldMousePos[0] = static_cast<float>(event->getMouseX());
      oldMousePos[1] = static_cast<float>(event->getMouseY());

      onStartDragging();
    }
    break;

  case MOUSE_RELEASE:
    if (dragging) {
      int x = event->getX();
      int y = event->getY();

      dragging = false;

      /* Look for appropriate slot */
      Slot *bestSlot = NULL;
      float bestDistance = std::numeric_limits<float>::max();
      float centerX = getX() + getWidth() / 2;
      float centerY = getY() + getHeight() / 2;
      uint count = slots.size();

      for (uint i = 0; i < count; i++) {
        Slot *slot = slots[i];

        float cX = slot->getX() + slot->getWidth() / 2;
        float cY = slot->getY() + slot->getHeight() / 2;
        float dist = (cX - centerX) * (cX - centerX) + (cY - centerY) * (cY - centerY);

        if (dist < bestDistance) {
          bestDistance = dist;
          bestSlot = slot;
        }
      }

      if (bestSlot == NULL) {
        bestSlot = currentSlot;
      }

      if (bestSlot != currentSlot) {
        Slot *slot = currentSlot;
        SlotItem *dropped = bestSlot->getItem();

        bestSlot->assign(this);
        slot->assign(dropped);
        if (dropped) {
          dropped->setSlot(slot);
          dropped->setCovered(false);
        }
      }

      setSlot(bestSlot);
      setCovered(x >= 0 && y >= 0 && x < getWidth() && y < getHeight());

      onStopDragging();
      break;
    }

  default:
    // Do nothing
    break;
  }

  return OK;
}

}