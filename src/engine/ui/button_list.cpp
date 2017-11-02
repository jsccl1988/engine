// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "common.h"
#include "events/system_event.h"
#include "ui/button_list.h"
#include "math/maths.h"

namespace ve {

static const uint DEFAULT_ARROW_BUTTONS_MARGIN = 10;
static const uint DEFAULT_BUTTONS_MARGIN = 5;
static const uint DEFAULT_DISTANCE_BETWEEN_BUTTONS = 10;

ButtonList::ButtonList(UIContainer *parent) :UIControl(parent) {
  buttonMargin = DEFAULT_ARROW_BUTTONS_MARGIN;
  firstButton = 0;
  maxWidth = 0;
  maxHeight = 0;
  buttonsToShow = 0;
  style = BLS_DEFAULT;
  activeButton = -1;
}

/* Inherited from ActionListener */
Outcome ButtonList::processActionEvent(ActionEvent *event) {
  UIControl *sender = event->getSender();

  switch (event->getType()) {
  case MOUSE_PRESS:
    if (sender == btLeft && firstButton > 0)
      firstButton--;

    if (sender == btRight && firstButton + buttonsToShow <= (int)button.size())
      firstButton++;

    if (sender != btLeft && sender != btRight && style == BLS_EXCLUSIVE) {
      int len = button.size();
      for (int i = 0; i < len; i++) {
        if (button[i] != sender) {
          button[i]->release();
        } else {
          activeButton = i;
        }
      }
    }

    break;
  default:
    //FIXME:Not implemented
    break;
  }

  return OK;
}

/* Inherited from MouseListener */
Outcome ButtonList::processMouseEvent(MouseEvent *event) {
  int i, len = button.size();

  ASSERT(btLeft->processMouseEvent(event));
  ASSERT(btRight->processMouseEvent(event));

  for (i = 0; i < len; i++) {
    ASSERT(button[i]->processMouseEvent(event));
  }

  return OK;
}

/* General */
void ButtonList::addButton(Button *newButton) {
  //newButton->setParent(this);
  newButton->addActionListener(this);
  if (activeButton == -1 && style == BLS_EXCLUSIVE) {
    activeButton = 0;
    newButton->press();
  }
  button.push_back(newButton);
}

void ButtonList::clear() {
  button.clear();
}

Outcome ButtonList::setLeftButton(Button *leftButton) {
  CHECK_POINTER(leftButton);

  btLeft = leftButton;
  btLeft->addActionListener(this);
  //btLeft->setParent(this);

  return OK;
}

Outcome ButtonList::setRightButton(Button *rightButton) {
  CHECK_POINTER(rightButton);

  btRight = rightButton;
  btRight->addActionListener(this);
  //btRight->setParent(this);

  return OK;
}

void ButtonList::setBorder(Border *border) {
  this->border = border;
}

Border* ButtonList::getBorder() {
  return border;
}

Outcome ButtonList::setBackground(AbstractSprite *backgroundSprite) {
  this->background = backgroundSprite;
  return OK;
}

AbstractSprite* ButtonList::getBackground() {
  return background;
}

void ButtonList::setButtonMargin(int newMargin) {
  buttonMargin = newMargin;
}

void ButtonList::setStyle(ButtonListStyle newStyle) {
  style = newStyle;
}

/* get functions */
Button* ButtonList::getLeftButton() {
  return btLeft;
}

Button* ButtonList::getRightButton() {
  return btRight;
}

int ButtonList::getActiveButton() {
  return activeButton;
}

}
