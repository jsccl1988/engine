// Copyright (c) 2017 The Smart Authors.
// All rights reserved.
#ifndef __VE_INTERFACE_H__
#define __VE_INTERFACE_H__

#include <vector>
#include "engine/visible_object.h"
#include "engine/events/mouse_event_source.h"
#include "engine/events/key_event_source.h"
#include "engine/ui/button.h"
#include "engine/ui/form.h"
#include "engine/ui/label.h"
#include "engine/ui/checkbox.h"
#include "engine/sprites/simple_sprite.h"
#include "engine/ui/gauge.h"
#include "engine/ui/editbox.h"
#include "engine/ui/panel.h"
#include "engine/ui/desktop.h"
#include "engine/tools/memory_manager.h"
#include "engine/ui/desktop.h"

namespace ve {

/**
    Main class for interface system in <b>VR %Engine</b> library. It is only one class
    which should be used for creation of interface components. All created components are registered
    by this class.

    In its destructor it destroy all the objects it creates, so there is no need to destroy them
    manually. MemoryManager class is used for these purposes.

    UI class renders only components registered in the active Desktop. The only one desktop
exists at the beginning (Main Desktop). It may be retrieved via getDesktop(0) function.
Any other Desktop object may be registered in the interface system using addDesktop() function.
To make desktop active you should call setActiveDesktop(<index of the desktop>).
Zero is passed to make the main desktop active or other value returned by addDektop() fucntion.
Main desktop is active by default.

    This class is the highest level for all mouse & keyboard events which are passed across
    all the components. Call processMessage() spead event across components.
*/
class UI : public VisibleObject {
protected:
  /** Engine which created this interface. */
  Engine *engine;

  /** List of registered interface components. */
  std::vector<UIControl*> registered;

  /** Desktops */
  std::vector<Desktop*> desktops;
  uint activeDesktop;

public:
  /**
      UI class constructor.
      @param engine - Engine which creates this interface. All interface
      components will use it for rendering.
  */
  UI(Engine *engine);

  virtual ~UI();

  /**
    Returns desktop by its index. If there is no Desktop object for a given
    index NULL will be returned.
    @return Desktop object associated with the index.
    @return NULL if index is out of bounds.
  */
  Desktop* getDesktop(uint index);

  /**
    Adds Desktop to the interface. Nothing will be done if NULL is passed
    or such desktop already added.
    @param desktop - Desktop to add to the interface system.
    @param index - Index of the desktop. Use it to make desktop active.
  */
  uint addDesktop(Desktop *desktop);

  /**
    Makes a desktop active.
    @param index - Index of the desktop returned by addDesktop() or 0
    to make main desktop active.
  */
  void setActiveDesktop(uint index);

  /**
    Returns active desktop.
    @return pointer to the active Desktop.
  */
  Desktop* getActiveDesktop();

  /**
          Creates form component.
          @return Newly-created Form object.
  */
  Form* createForm(UIContainer *parent);

  /**
      Creates button component.
      @param width - width of the button.
      @param height - height of the button.
      @return pointer to a new button component.
      @return NULL in case of engine error.
  */
  Button* createButton(UIContainer *parent, int width, int height);

  /**
      Creates label component.
      @return pointer to a new label component.
      @return NULL in case of engine error.
  */
  Label* createLabel(UIContainer *parent);

  /**
      Creates label component.
      @param text - Text string for label.
      @param color - Color of label's text.
      @return pointer to a new label component.
      @return NULL in case of engine error.
  */
  Label* createLabel(UIContainer *parent, std::wstring text, Vector4f color);

  /**
      Creates checkbox component.
      @return pointer to a new checkbox component.
      @return NULL in case of engine error.
  */
  Checkbox* createCheckbox(UIContainer *parent);

  /**
      Creates Border component.
      @return pointer to a new border component.
      @return NULL in case of engine error.
  */
  Border* createBorder(UIContainer *parent);

  /**
      Creates Border component.
      @param color - Line color for the border.
      @param lineWidth - Line width for the border.
      @return pointer to a new border component.
      @return NULL in case of engine error.
  */
  Border* createBorder(UIContainer *parent, Vector4f color, int lineWidth);

  /**
      Creates Panel component.
      @return pointer to a new panel component.
      @return NULL in case of engine error.
  */
  Panel* createPanel(UIContainer *parent);

  /**
      Creates Gauge component.
      @return pointer to a new gauge component.
      @return NULL in case of engine error.
  */
  Gauge* createGauge(UIContainer *parent);

  /**
      Creates Editbox component.
      @return pointer to a new editbox component.
      @return NULL in case of engine error.
  */
  Editbox* createEditbox(UIContainer *parent);

  /**
      Returns Engine object which was used to create this UI object.
      @return Engine class which created this UI object.
  */
  Engine *getEngine();

  /**
      Renders active desktop.
      @return OK if rendering of desktop succeeded.
      @return non-OK if error occurred.
  */
  virtual Outcome render();

  /**
      Entry point for all messages in the interface system.
      Use this function to transfer events to interface components.
      @param event - SystemEvent to process by <b>VR Engine</b> interface system.
      @return OK if processing succeeded.
      @return non-OK if error occurred.
  */
  Outcome processMessage(SystemEvent *event);

  /**
      Registers control in the interface system.
      @return Control id.
  */
  Handle registerControl(UIControl *control);

  /**
      Returns number of registered controls.
      @return Number of registered controls.
  */
  uint countControls();

  /**
      Returns control by its index.
      @return UI Control by specified index (from 0 till countControls() - 1).
  */
  UIControl* getControl(uint index);
};

}

#endif // __VE_INTERFACE_H__
