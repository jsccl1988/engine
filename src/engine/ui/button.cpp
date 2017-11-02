// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "common.h"
#include "events/system_event.h"
#include "ui/button.h"
#include "engines/engine.h"

namespace ve {

Button::Button(UIContainer *parent) :UIControl(parent),
  shiftVector(1, 1, 0) {
  pressed = false;
  style = BS_DEFAULT;
  baseSprite = NULL;
  onCoverSprite = NULL;
  onPressSprite = NULL;

}

Button::Button(UIContainer *parent, int width, int height) :UIControl(parent),
  shiftVector(1, 1, 0) {
  setSize(width, height);
  pressed = false;
  style = BS_DEFAULT;
  baseSprite = NULL;
  onCoverSprite = NULL;
  onPressSprite = NULL;
}

/* Inherited from VisibleObject */
Outcome Button::render() {
  if (!isVisible()) {
    return OK;
  }

  int width = getWidth();
  int height = getHeight();

  CHECK_POINTER(baseSprite);
  baseSprite->setSize(width, height);

  if (onCoverSprite != NULL) {
    onCoverSprite->setSize(width, height);
  }
  if (onPressSprite != NULL) {
    onPressSprite->setSize(width, height);
  }

  ASSERT(engine->beginTransform());
  ASSERT(engine->translate(getX(), getY(), getZ()));

  if (style == BS_FIXED) {
    if (pressed == true && onPressSprite != NULL) {
      ASSERT(onPressSprite->render());
    } else
      if (isCovered() == true && onCoverSprite != NULL) {
        ASSERT(onCoverSprite->render());
      } else {
        ASSERT(baseSprite->render());
      }
  } else
    if (style == BS_DEFAULT) {
      if (pressed == true) {
        ASSERT(engine->beginTransform());
        ASSERT(engine->translate(shiftVector[0], shiftVector[1], shiftVector[2]));
        if (onPressSprite == NULL) {
          ASSERT(baseSprite->render());
        } else {
          ASSERT(onPressSprite->render());
        }
        ASSERT(engine->endTransform());
      } else {
        if (isCovered() == true && onCoverSprite != NULL) {
          ASSERT(onCoverSprite->render());
        } else {
          ASSERT(baseSprite->render());
        }
      }
    } else {
      UNIMPLEMENTED();
    }

  ASSERT(engine->endTransform());

  return OK;
}

/* Inherited from MouseListener */
Outcome Button::processMouseEvent(MouseEvent *event) {
  CHECK_RESULT(UIControl::processMouseEvent(event), L"Failed to perform mouse message");

  if (!isVisible()) {
    return OK;
  }

  int x = event->getX();
  int y = event->getY();

  switch (event->getType()) {
  case MOUSE_PRESS:
    if (style == BS_FIXED && isCovered()) {
      Outcome result = OK;
      pressed = pressed ^ true;
      if (pressed == true) {
        result = sendActionEvent(new ActionEvent(BUTTON_PRESS, this));
      } else {
        result = sendActionEvent(new ActionEvent(BUTTON_RELEASE, this));
      }
      CHECK_RESULT(result, L"Message processing failed");
    } else {
      if (style == BS_DEFAULT && pressed == false && isCovered() == true) {
        pressed = true;
      }
    }
    break;

  case MOUSE_RELEASE:
    if (pressed == true && style != BS_FIXED) {
      pressed = false;
      CHECK_RESULT(sendActionEvent(new ActionEvent(BUTTON_RELEASE, this)), L"Message processing failed");
    }
    break;
  default:
    //FIXME:Not Implemented
    break;
  }

  return OK;
}

/* General */
void Button::release() {
  if (style == BS_FIXED) {
    pressed = false;
  }
}

void Button::press() {
  if (style == BS_FIXED) {
    pressed = true;
  }
}

/* Set functions */
void Button::setBaseSprite(AbstractSprite *baseSprite) {
  this->baseSprite = baseSprite;
}

AbstractSprite* Button::getBaseSprite() {
  return baseSprite;
}

void Button::setOnPressSprite(AbstractSprite *onPressSprite) {
  this->onPressSprite = onPressSprite;
}

void Button::setOnCoverSprite(AbstractSprite *onCoverSprite) {
  this->onCoverSprite = onCoverSprite;
}

void Button::setSprites(AbstractSprite *baseSprite, AbstractSprite *onPressSprite, AbstractSprite *onCoverSprite) {
  setBaseSprite(baseSprite);
  setOnPressSprite(onPressSprite);
  setOnCoverSprite(onCoverSprite);
}


void Button::setShiftVector(Vector3f newShiftVector) {
  shiftVector = newShiftVector;
}

void Button::setStyle(ButtonStyle newStyle) {
  style = newStyle;
}

/* Get functions */

bool Button::isPressed() {
  return pressed;
}

ButtonStyle Button::getStyle() {
  return style;
}

void Button::setAlphaTestState(AlphaTestState newAlphaTestState) {
  if (baseSprite) {
    baseSprite->setAlphaTestState(newAlphaTestState);
  }

  if (onCoverSprite) {
    onCoverSprite->setAlphaTestState(newAlphaTestState);
  }

  if (onPressSprite) {
    onPressSprite->setAlphaTestState(newAlphaTestState);
  }
}

void Button::setBlendState(BlendState newBlendState) {
  if (baseSprite) {
    baseSprite->setBlendState(newBlendState);
  }

  if (onCoverSprite) {
    onCoverSprite->setBlendState(newBlendState);
  }

  if (onPressSprite) {
    onPressSprite->setBlendState(newBlendState);
  }
}

}
