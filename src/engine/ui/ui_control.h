// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_INTERFACE_CONTROL_H__
#define __VE_INTERFACE_CONTROL_H__

#include "engine/sprites/abstract_sprite.h"

namespace ve {

class UIContainer;

/**
    Base class for all interface controls in <b>VR %Engine</b>.
    It contains only basic info about control:
    <ul>
    <li>Flag which defines if it is enabled. Disabled components have do not react
    on user input and sometimes are rendered in a different way.</li>
    </ul>
*/
class UIControl : public AbstractSprite {
private:
  bool enabled;

protected:
  /**
      UIContainer that owns this component.
  */
  UIContainer *parent;

public:
  /**
      UIControl constructor. Registers control by obtaining free Id from
      UI object.
      @param parent - UI object which creates this control.
  */
  UIControl(UIContainer *parent);

  /**
      Handles mouse events.
      @param event - Mouse event to process.
      @return OK if event was processed successfully.
      @return non-OK if error occurred.
  */
  virtual Outcome processMouseEvent(MouseEvent *event);

  /**
      Enables/Disables this component.
      @param value - New value for 'enabled' flag. To turn component
      on set 'true', to turn it off to 'false'.
  */
  void setEnabled(bool value);

  /**
      Checks if component is enabled.
      @return 'true' if component is enabled and 'false' if disabled.
  */
  bool isEnabled();
};

}

#endif // __VE_INTERFACE_CONTROL_H__
