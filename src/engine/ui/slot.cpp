// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "ui/slot.h"
#include "ui/slot_item.h"

namespace ve {

Slot::Slot(UIContainer *parent) :UIControl(parent) {
  sprite = NULL;
  item = NULL;
}

Slot::Slot(UIContainer *parent, AbstractSprite *sprite) : UIControl(parent) {
  this->sprite = sprite;
  item = NULL;
}

Slot::~Slot() {
}

void Slot::setSprite(AbstractSprite *sprite) {
  this->sprite = sprite;
}

bool Slot::isAvaialble() {
  return item == NULL;
}

SlotItem* Slot::getItem() {
  return item;
}

void Slot::assign(SlotItem *item) {
  if (this->item == item) {
    return;
  }

  if (this->item != NULL) {
    this->item->drop();
  }

  this->item = item;
}

Outcome Slot::render() {
  CHECK_POINTER(sprite);

  sprite->setPosition(getPosition());
  sprite->setSize(getWidth(), getHeight());

  return sprite->render();
}

}