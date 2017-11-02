// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_DESKTOP_H__
#define __VE_DESKTOP_H__

#include <vector>

#include "engine/ui/ui_container.h"
#include "engine/sprites/abstract_sprite.h"
#include "engine/events/key_listener.h"
#include "engine/events/mouse_listener.h"

namespace ve {

class UI;

/**
  Desktop is a set of Sprite objects. It represent an easy way to switch
  different menu screens in the game.
*/
class Desktop : public UIContainer {
protected:
  int id;

public:
  /**
    Constructor. Desktop will be attached to the GUI system in the constructor.
    @gui - UI this desktop should be attached to.
  */
  Desktop(UI *gui);

  /**
    Destructor.
  */
  virtual ~Desktop();

  /**
    All the components should be created and initialized here.
    @returns OK if initialization completed successfuly
    @returns non-OK if error occurred.
  */
  virtual Outcome init();

  /**
    Renders desktop.
    @return OK if rendering succeeded.
    @return non-OK if error occurred.
  */
  virtual Outcome render();
};

}

#endif // __VE_DESKTOP_H__