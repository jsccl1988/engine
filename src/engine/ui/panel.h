// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_PANEL_H__
#define __VE_PANEL_H__

#include "engine/ui/ui_control.h"

namespace ve {

class UI;

/**
    Still unimplemented Panel component.
*/
class Panel : public UIControl {
public:
  Panel(UIContainer *parent);

  virtual Outcome render();
  virtual Outcome processMouseEvent(MouseEvent *event);
  virtual Outcome processKeyEvent(KeyEvent *event);

};

}

#endif // __VE_PANEL_H__
