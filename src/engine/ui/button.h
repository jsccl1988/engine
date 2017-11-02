// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_BUTTON_H__
#define __VE_BUTTON_H__

#include "engine/types.h"
#include "engine/math/maths.h"
#include "engine/ui/ui_control.h"
#include "engine/events/action_event_source.h"
#include "engine/events/mouse_event_source.h"
#include "engine/events/mouse_listener.h"

/** @file eeButton.h */

namespace ve {

class UI;

enum ButtonStyle {
  BS_DEFAULT = 0,
  BS_FIXED = 1
};

/**
    Button is an interface component which is used to place several kind of buttons
    on your forms.

    Every button has three sprites for rendering:
    <ul>
    <li>Base sprite - must be set, because it is a main view of the button.</li>
    <li>onCover sprite - optional sprite. If it was set up and mouse pointer is above
    this button, it will be rendered as this sprite. If not, button rendered
    as Base sprite.</li>
    <li>onPress sprite - optional sprite. It is shown in pressed state of the button.</li>
    </ul>

    Note that all these sprite may be the same.
    Two button styles are currently supported:
    <ul>
    <li>Default - usual button with Base/onCover/onPress sprites as described before.</li>
    <li>Fixed - The same as Default style, but no button shift occurred during button press.</li>
    </ul>

    <b>Note:</b> Button classes must be created only through UI::createButton() function.
*/
class Button : public UIControl, public ActionEventsSource {
private:
  /** Flag that defines if button is pressed now */
  bool pressed;

  /** Sprite for Base/onCover/onPress states     */
  AbstractSprite *baseSprite;
  AbstractSprite *onCoverSprite;
  AbstractSprite *onPressSprite;

  /** Shift vector - vector which contains offset for pressed button */
  Vector3f shiftVector;

  /** Defines button style */
  ButtonStyle style;

public:
  /**
      Button constructor.
      @param parent - UI container that will be the owner of this button.
  */
  Button(UIContainer *parent);

  /**
      Extended version of button constructor.
      @param owner - UI which creates this button.
      @param width - Width for this button.
      @param height - Height for this button.
  */
  Button(UIContainer *parent, int width, int height);

  /**
      Renders button sprite.
      Following rendering logic is applied to decide what sprite
      should be used:
      <ol>
      <li>If button is pressed and onPress sprite pointer is not NULL than it is used.</li>
      <li>If button is covered by mouse pointer and onCover sprite pointer is not NULL than it is used. </li>
      <li>In all other cases Base sprite is used. </li>
      </ol>

      It is important thing to know that button component (and many other
      interface components) resizes all sprite components before rendering.
      Their width and height will be the same as this button has.

      @return OK if render succeeded.
      @return NULL_POINTER returned if baseSprite was not set.
      @return non-OK if engine error occurred.
  */
  virtual Outcome render();

  /**
      Mouse event processing function. It is used to change button's state.
      ActionEvent is send from this function if it is occurred.
      @param event - Mouse event object for processing.
      @return OK if function succeeded.
      @return non-OK if ActionEvent occurred and some of the listeners
      failed during processing of this event.
  */
  virtual Outcome processMouseEvent(MouseEvent *event);

  /**
      Releases this button if it is pressed.
  */
  void release();

  /**
      Sets this button to a pressed state.
  */
  void press();

  /**
      Sets Base sprite.
      @param baseSprite - new base sprite for this button.
  */
  void setBaseSprite(AbstractSprite *baseSprite);

  /**
      Returns base sprite of this button.
      @return Base sprite of this button.
  */
  AbstractSprite *getBaseSprite();

  /**
      Sets onPress sprite.
      @param onPressSprite - new onPressSprite for this button.
  */
  void setOnPressSprite(AbstractSprite *onPressSprite);

  /**
      Sets onCover sprite.
      @param onCoverSprite - new onCover sprite for this button.
  */
  void setOnCoverSprite(AbstractSprite *onCoverSprite);

  /**
      Sets all three sprites for this button.
      @param baseSprite - new base sprite for this button.
      @param onPressSprite - new onPressSprite for this button.
      @param onCoverSprite - new onCover sprite for this button.
  */
  void setSprites(AbstractSprite *baseSprite, AbstractSprite *onPressSprite,
    AbstractSprite *onCoverSprite);

  /**
      Sets shift vector which is used for pressed button state.
      @param newShiftVector - new value of shift vector for this button.
  */
  void setShiftVector(Vector3f newShiftVector);

  /**
      Sets this button style.
      @param newStyle - new style for this button.
  */
  void setStyle(ButtonStyle newStyle);

  /**
      Returns if button is in pressed state now.
      @return true - button is pressed.
      @return false - button is not pressed.
  */
  bool isPressed();

  /**
      Returns button style.
      @return Style of this button.
  */
  ButtonStyle getStyle();

  /**
  */
  virtual void setAlphaTestState(AlphaTestState newAlphaTestState);

  /**
  */
  virtual void setBlendState(BlendState newBlendState);
};

}

#endif // __VE_BUTTON_H__
