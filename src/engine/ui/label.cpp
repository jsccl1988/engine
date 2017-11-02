// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "common.h"
#include "ui/label.h"
#include "engines/engine.h"

namespace ve {

Label::Label(UIContainer *parent) :
  UIControl(parent),
  text(L""),
  color(1.0, 1.0, 1.0, 1.0) {
  font = NULL;
  lengthBound = 0;
}

Label::Label(UIContainer *parent, std::wstring &theText, const Vector4f &theColor) :UIControl(parent) {
  font = NULL;
  text = theText;
  color = theColor;
  lengthBound = 0;
}

/* Inherited form VisibleObject */

Outcome Label::render() {
  if (!isVisible()) {
    return OK;
  }

  CHECK_POINTER(font);
  Vector3f position = getPosition();
  GPUStateManager *stateManager = engine->getStateManager();
  stateManager->pushStates(COLOR_STATE);
  ASSERT(stateManager->setColorState(ColorState(color[0], color[1], color[2], color[3])));

  uint firstLetter = 0;
  uint len = text.length();

  if (lengthBound != 0) {
    while (len > 0 && font->getTextWidth(text.substr(firstLetter, len)) > (uint)lengthBound) {
      firstLetter++;
      len--;
    }
  }

  ASSERT(font->drawString(position[0], position[1], position[2], text.substr(firstLetter, len)));

  stateManager->popStates(COLOR_STATE);
  return OK;
}

/* set functions */
void Label::setText(std::wstring newText) {
  text = newText;
}

void Label::setColor(Vector4f newColor) {
  color = newColor;
}

void Label::setFont(Font* newFont) {
  font = newFont;
}

void Label::setLengthBound(uint length) {
  lengthBound = length;
}

/* get functions */
std::wstring Label::getText() {
  return text;
}

Vector4f Label::getColor() {
  return color;
}

Font* Label::getFont() {
  return font;
}

}
