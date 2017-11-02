// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_CHECKBOX_H__
#define __VE_CHECKBOX_H__

#include "engine/ui/button.h"
#include "engine/ui/label.h"
#include "engine/ui/ui_container.h"
#include "engine/events/action_listener.h"

namespace ve {

class UI;

/**
    Checkbox is a standard interface component that can be used in many applications
    to handle user's choice. It consists of two components - button and a label.
    Relative position of button and label may be defined through label/button position coordiantes.
    Position for label/button is set relative coordinate system of this checkbox.
    "Fixed" style is used for button rendering.
*/
class Checkbox : public UIContainer, ActionListener {
private:
  Button *button;
  Label *label;

public:
  /**
      Simple Checkbox constructor.
      @param parent - UI component that will be the owner of this checkbox.
  */
  Checkbox(UIContainer *parent);

  /**
      Extended Checkbox constructor.
      @param parent - UI component that will be the owner of this checkbox.
      @param button - Button which will be used to handle user's input.
      @param label - Label to show description. May be NULL is no textual
      description is needed.
  */
  Checkbox(UIContainer *parent, Button* button, Label *label);

  /**
      Renders checkbox component.
      Simply renders button and label at their position.
      @return OK if rendering succeede.
      @return non-OK if engine error occurred.
  */
  virtual Outcome render();

  /**
      Used to handle button messages.
      @return OK everytime.
  */
  virtual Outcome processActionEvent(ActionEvent *event);

  /**
      Sets button for this checkbox. Sets its own "width" and "height" to
      the "width" and "height" of button respectively.
      @param button - Button to use in this checkbox.
  */
  Outcome setButton(Button *button);

  /**
      Sets label for this checkbox.
      @param label - Label to use in this checkbox or NULL
      if there is no need to show label.
  */
  void setLabel(Label *label);

  /**
      Sets state of this checkbox.
      @param value - true if checkbox should be on and false otherwise.
  */
  void setChecked(bool value);

  /**
      Returns label which is used in this checkbox.
      @return pointer to label object if it used in this checkbox
      and NULL if no label is used.
  */
  Label *getLabel();

  /**
      Returns button which is used in this chackbox.
      @return pointer to button object which is used in this checkbox.
  */
  Button *getButton();

  /**
      Checks if checkbox is on.
      @return 'true' if checkbox is on.
      @return 'false' if checkbox is off.
  */
  bool isChecked();
};

}

#endif // __VE_CHECKBOX_H__
