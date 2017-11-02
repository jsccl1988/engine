// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "common.h"
#include "ui/ui.h"
#include "ui/desktop.h"

namespace ve {

UI::UI(Engine *engine) {
  this->engine = engine;
  activeDesktop = 0;
  desktops.push_back(new Desktop(this));
}

UI::~UI() {
}

Desktop* UI::getDesktop(uint index) {
  ERROR_IF(index >= desktops.size(), L"Index is out of bounds", NULL);
  return desktops[index];
}

uint UI::addDesktop(Desktop *desktop) {
  desktops.push_back(desktop);
  return desktops.size() - 1;
}

void UI::setActiveDesktop(uint index) {
  ERROR_IF(index >= desktops.size(), L"Index is out of bounds", );
  activeDesktop = index;
}

Desktop* UI::getActiveDesktop() {
  return desktops[activeDesktop];
}

Form* UI::createForm(UIContainer *parent) {
  Form *newForm = new Form(parent);
  CHECK_ALLOC_EX(newForm, NULL);
  return newForm;
}

Button* UI::createButton(UIContainer *parent, int width, int height) {
  Button *newButton = new Button(parent, width, height);
  CHECK_ALLOC_EX(newButton, NULL);
  return newButton;
}

Label* UI::createLabel(UIContainer *parent) {
  Label *newLabel = new Label(parent);
  CHECK_ALLOC_EX(newLabel, NULL);
  return newLabel;
}

Label* UI::createLabel(UIContainer *parent, std::wstring text, Vector4f color) {
  Label *newLabel = new Label(parent, text, color);
  CHECK_ALLOC_EX(newLabel, NULL);
  return newLabel;
}

Checkbox* UI::createCheckbox(UIContainer *parent) {
  Checkbox *newCheckbox = new Checkbox(parent);
  CHECK_ALLOC_EX(newCheckbox, NULL);
  return newCheckbox;
}

Border* UI::createBorder(UIContainer *parent) {
  Border *newBorder = new Border(parent);
  CHECK_ALLOC_EX(newBorder, NULL);
  return newBorder;
}

Border* UI::createBorder(UIContainer *parent, Vector4f color, int lineWidth) {
  Border *newBorder = new Border(parent, color, lineWidth);
  CHECK_ALLOC_EX(newBorder, NULL);
  return newBorder;
}

Panel* UI::createPanel(UIContainer *parent) {
  Panel *newPanel = new Panel(parent);
  CHECK_ALLOC_EX(newPanel, NULL);
  return newPanel;
}

Gauge* UI::createGauge(UIContainer *parent) {
  Gauge *newGauge = new Gauge(parent);
  CHECK_ALLOC_EX(newGauge, NULL);
  return newGauge;
}

Editbox* UI::createEditbox(UIContainer *parent) {
  Editbox *newEditbox = new Editbox(parent);
  CHECK_ALLOC_EX(newEditbox, NULL);
  return newEditbox;
}

Engine* UI::getEngine() {
  return engine;
}

/* Inherited from VisibleObject */
Outcome UI::render() {
  ASSERT(getActiveDesktop()->render());
  return OK;
}

Outcome UI::processMessage(SystemEvent *event) {
  if (event == NULL) {
    return OK;
  }

  switch (event->getType()) {
  case MOUSE_PRESS:
  case MOUSE_RELEASE:
  case MOUSE_MOTION:
    ASSERT(getActiveDesktop()->processMouseEvent(static_cast<MouseEvent*>(event)));
    break;

  case KEY_PRESS:
  case KEY_RELEASE:
    ASSERT(getActiveDesktop()->processKeyEvent(static_cast<KeyEvent*>(event)));
    break;

  case WINDOW_RESIZE:
  case WINDOW_CLOSE:
    break;

  default:
    UNIMPLEMENTED();
    break;
  }

  return OK;
}

/* Handled messages */
Handle UI::registerControl(UIControl *control) {
  static uint id = 0;
  registered.push_back(control);
  return id++;
}

uint UI::countControls() {
  return registered.size();
}

UIControl* UI::getControl(uint index) {
  ERROR_IF(index > registered.size(), L"Index is out of bounds", NULL);
  return registered[index];
}

}
