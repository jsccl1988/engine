// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_SLOT_H__
#define __VE_SLOT_H__

#include "engine/ui/ui_control.h"

namespace ve {

class SlotItem;

/*
  Slot for slot items. It is used to imlement slot system (like inventory in games).
*/
class Slot : public UIControl {
private:
  SlotItem *item;
  AbstractSprite *sprite;

public:
  /**
    Default constructor.
    @param parent - UI container that will be the owner of this Slot object.
  */
  Slot(UIContainer *parent);

  /**
    Constructor.
    @param parent - UI container that will be the owner of this Slot object.
    @param sprite - appearance of this slot item.
  */
  Slot(UIContainer *parent, AbstractSprite *sprite);

  /**
    Destructor.
  */
  virtual ~Slot();

  /**
    Sets appearance of this item.
    @param sprite - appearance of this slot item.
  */
  void setSprite(AbstractSprite *sprite);

  /**
    Checks if slot is available.
    @return true if slot is available.
  */
  bool isAvaialble();

  /**
    Returns item that was assigned to this slot or NULL
    if no item was assigned.
    @return Item that was assigned to this slot or NULL
    if no item was assigned.
  */
  SlotItem *getItem();

  /**
    Assigns item to this slot. Pass NULL to make
    slot available. If this slot is occuppied by another
    item then it will be removed.
    @param item - slot item to assign to this slot.
  */
  void assign(SlotItem *item);

  /**
      Renders sprite.
      @return OK if rendering succeeded.
      @return non-OK if error occurred.
  */
  virtual Outcome render();
};

}

#endif // __VE_SLOT_H__