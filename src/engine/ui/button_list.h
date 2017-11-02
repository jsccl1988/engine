// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_BUTTON_LIST_H__
#define __VE_BUTTON_LIST_H__

#include <vector>

#include "ui/button.h"
#include "events/action_listener.h"
#include "events/mouse_listener.h"
#include "ui/ui_control.h"
#include "ui/border.h"

namespace ve {

enum ButtonListStyle {
  BLS_DEFAULT = 0,
  BLS_EXCLUSIVE = 1
};

/**
    Do not use this class, need redesign.
*/
class ButtonList : public UIControl, private ActionListener {
private:
  Border *border;
  AbstractSprite *background;
  Button *btLeft;
  Button *btRight;
  int buttonMargin;
  int topMargin;
  int firstButton;
  int buttonsToShow;
  int maxWidth, maxHeight;
  std::vector<Button*> button;
  ButtonListStyle style;
  int activeButton;

public:
  ButtonList(UIContainer *parent);

  /* Inherited from ActionListener */
  virtual Outcome processActionEvent(ActionEvent *event);

  /* Inherited from MouseListener */
  virtual Outcome processMouseEvent(MouseEvent *event);

  void addButton(Button *newButton);
  void clear();
  Outcome setLeftButton(Button *leftButton);
  Button *getLeftButton();
  Outcome setRightButton(Button *rightButton);
  Button *getRightButton();
  void setBorder(Border *border);
  Border *getBorder();
  Outcome setBackground(AbstractSprite *backgroundSprite);
  AbstractSprite *getBackground();

  void setButtonMargin(int newMargin);
  void setStyle(ButtonListStyle newStyle);
  int getActiveButton();
};

}

#endif // __VE_BUTTON_LIST_H__
