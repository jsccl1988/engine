// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_FORM_H__
#define __VE_FORM_H__

#include "engine/common.h"
#include "engine/events/mouse_event.h"
#include "engine/events/mouse_listener.h"
#include "engine/events/key_listener.h"
#include "engine/events/mouse_event_source.h"
#include "engine/events/key_event_source.h"
#include "engine/ui/ui_container.h"
#include "engine/ui/ui_control.h"
#include "engine/ui/border.h"
#include "engine/math/vector4f.h"
#include "engine/ui/border.h"

namespace ve {

class UI;

/**
    Form interface component. It is an interface container for other objects.
    Forms may be movable, thus they can be easily moved across screen by user.
    Form consists of three main components: Caption sprite, Background sprite
    and Border object. They are optional. All the components inside this form
    is rendered on background sprite which represents form's client area.

    <b>Note:</b> Form components must be created only through UI::createForm()
    function.
*/
class Form : public UIContainer {
private:
  AbstractSprite *captionSprite;
  AbstractSprite *backgroundSprite;
  Border *border;

  /** Flag which defines if mouse is pressed on a caption. */
  bool isLeftMouseButtonPressed;

  /** These coords are used to track form movements. */
  float oldX;
  float oldY;

  /** Defines if form can be moved by user. */
  bool movable;

public:
  /**
      Form constructor.
      @param parent - UI object that will be the owner this form.
  */
  Form(UIContainer *parent);

  /**
      Renders this form.
      Render algorithm:
      <ol>
      <li>Render caption using cpation sprite.</li>
      <li>Render client area using background sprite.</li>
      <li>Render border using Border object.</li>
      <li>Render interface componets inside client area.</li>
      </ol>
      @return OK if rendering succeeded.
      @return non-OK if engine error occurred.
  */
  virtual Outcome render();

  /**
      Process mouse events, form movements, generates mouse messages for
      interface components inside this form.
      @param event - mouse event to process.
      @return OK if processing succeeded.
      @return non-OK if engine error occurred.
  */
  virtual Outcome processMouseEvent(MouseEvent *event);

  /**
      For future usage.
  */
  bool onCanMove(int x, int y);

  /**
      Sets background sprite for this form. Passing NULL
      will disable background sprite rendering.
      @param background - sprite to use as background.
  */
  void setBackground(AbstractSprite *background);

  /**
      Returns background sprite.
      @return Sprite which is used for background rendering.
  */
  AbstractSprite *getBackgroundSprite();

  /**
      Sets caption sprite for this form. Passing NULL will
      disable caption rendering.
      @param caption - sprite to use for caption rendering.
  */
  void setCaption(AbstractSprite* caption);

  /**
      Returns caption sprite.
      @return Sprite which is used for caption rendering.
  */
  AbstractSprite *getCaptionSprite();

  /**
      Sets border for this form. Passing NULL will disable
      border rendering.
      @param border - Border object to render boundaries.
  */
  void setBorder(Border *border);

  /**
      Returns object which specifies borders of this form.
      @return Border object.
  */
  Border* getBorder();

  /**
      Enables or disables user's ability to move this form by
      caption dragging.
      @param isEnabled - pass 'true' to allow user move this form
      and 'false' to deny.
  */
  void setMovable(bool isEnabled);
};

}

#endif // __VE_FORM_H__
