// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_EDITBOX_H__
#define __VE_EDITBOX_H__

#include "engine/ui/ui_container.h"
#include "engine/ui/label.h"
#include "engine/ui/editbox_filter.h"

namespace ve {

/**
    GUI component that provides ability to edit Unicode
    strings. It is a simple version of Editbox component, because
    it has no cursor. Only typing and using Backspace is allowed
    in this component.
    Editbox consist of three components:
    <ul>
    <li>Background sprite - Used for rendering when this component is not active.</li>
    <li>Active Background sprite - Used for rendering when this component is active. </li>
    <li>Label component to store & render %Editbox text.</li>
    </ul>
    <b>Note:</b> Create Editbox components only through UI::createEditbox()
    function.
*/
class Editbox : public UIContainer {
private:
  /** Sprite which is used for rendering when Editbox is not active */
  AbstractSprite *background;

  /** Sprite which is used for rendering when Editbox is active */
  AbstractSprite *activeBackground;

  /** Label component which is used to store & render text */
  Label *label;

  /** Flag which defines if Editbox is active */
  bool isActive;

  /** Filter to control label content */
  EditboxFilter *filter;

public:
  /**
      Simple %Editbox constructor.
      @param parent - UI object that will be the owner of this %Editbox.
  */
  Editbox(UIContainer *parent);

  /**
    Destructor.
  */
  virtual ~Editbox();

  /**
      Renders component. Render algorithm is very simple:
      At first, render appropriate sprite (depends on if component
      is active). At second, renders label.
      @return OK if render succeeded.
      @return non-OK if engine error occurred.
  */
  virtual Outcome render();

  /**
      Handles mouse events. Here, Editbox decides when it is
      active or not-active. After every mouse press message it
      looks if mouse is above its area or not to decide if it active
      or not.
      @return OK if processing succeeded.
      @return non-OK if engine error occurred.
  */
  virtual Outcome processMouseEvent(MouseEvent *event);

  /**
      Handles keyboard events. Here, Editbox handles keyboard input
      and refresh Label according to this input.
      @return OK if processing succeeded.
      @return non-OK if engine error occurred.
  */
  virtual Outcome processKeyEvent(KeyEvent *event);

  /**
      Sets background sprite for this editbox.
      @param background - new background sprite for this editbox.
  */
  void setBackgroundSprite(AbstractSprite *background);

  /**
      Returns background sprite which is currently in use.
      @return Current background sprite.
  */
  AbstractSprite *getBackgroundSprite();

  /**
      Sets active background sprite for this editbox.
      @param activeBackground - new active background sprite for this editbox.
  */
  void setActiveBackgroundSprite(AbstractSprite *activeBackground);

  /**
      Returns active background sprite which is currently in use.
      @return Current active background sprite.
  */
  AbstractSprite *getActiveBackgroundSprite();

  /**
      Returns label component which holds text for this editbox.
      Use this to set font, color and position for text inside this
      editbox.
      @return Label component which is used to store & render text inside this editbox.
  */
  Label *getLabel();

  /**
      Sets filter for content.
      @param newFilter - new Editbox filter for content.
  */
  void setFilter(EditboxFilter *newFilter);
};

}

#endif // __VE_EDITBOX_H__
