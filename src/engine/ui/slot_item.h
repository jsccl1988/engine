// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_SLOT_ITEM_H__
#define __VE_SLOT_ITEM_H__

#include "engine/math/maths.h"
#include "engine/ui/ui_control.h"
#include "engine/ui/slot.h"

namespace ve {

/**
  It is used to make slots in GUI system (inventory, for example).
  To render slot item, sprite object and slot should be set. Each slot item
  has the list of possible slots it may contain. Use addSlot(),
  clearSlots() and removeSlot() functions to manage slots of this item.

  Workflow is the following:
  <ul>
  <li>Create slot item</li>
  <li>Set sprite (how it looks like)</li>
  <li>Add possible slots</li>
  <li>Set some slot for this item (one from the list above)</li>
  </ul>
*/
class SlotItem : public UIControl {
private:
  AbstractSprite *sprite;
  std::vector<Slot*> slots;
  Slot *currentSlot;
  bool dragging;
  Vector2f oldMousePos;

public:
  /**
    Default constructor.
    @param parent - UI container that will be the owner of this SlotItem object.
  */
  SlotItem(UIContainer *parent);

  /**
    Constructor.
    @param parent - UI container that will be the owner of this SlotItem object.
    @param sprite - appearance of this slot item.
  */
  SlotItem(UIContainer *parent, AbstractSprite *sprite);

  /**
    Destructor.
  */
  virtual ~SlotItem();

  /**
    Sets appearance of this item.
    @param sprite - appearance of this slot item.
  */
  void setSprite(AbstractSprite *sprite);

  /**
    Sets GUI slot for this item.
    @param slot - slot of this item.
    @return OK if item was successfully bound to the slot.
    @return NULL_POINTER if the given pointer is NULL.
  */
  Outcome setSlot(Slot *slot);

  /**
    Adds slot to the list of available slots for this item.
    @param slot - slot to add to the list of available slots for this item..
  */
  void addSlot(Slot *slot);

  /**
    Clears list of available slots for this item.
  */
  void clearSlots();

  /**
    Removes slot from the list of available slots for this item.
    @param slot - slot to remove from the list.
  */
  void removeSlot(Slot *slot);

  /**
    Called by occuppied Slot object when this item removed from it.
  */
  void drop();

  /**
    Renders sprite.
    @return OK if rendering succeeded.
    @return non-OK if error occurred.
  */
  virtual Outcome render();

  /**
   Handles mouse events to implement drag & drop functionality.
   @param event - mouse event to process.
   @return OK if event was successfully processed.
   @return ERROR if error occurred.
  */
  virtual Outcome processMouseEvent(MouseEvent *event);

  /**
    Callback that is called when dragging started.
  */
  virtual void onStartDragging() {}

  /**
    Callback that is called when dragging stopped.
  */
  virtual void onStopDragging() {}
};

}

#endif // __VE_SLOT_ITEM_H__