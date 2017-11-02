// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "tools/string_tool.h"
#include "engines/engine.h"
#include "ui/gauge.h"
#include "ui/ui.h"

namespace ve {

static int GAUGE_MIN = 0;
static int GAUGE_MAX = 100;

/**
    Sole Gauge constructor. By default it assumes that
    texture coords for Bar-sprite are defined in the following order:
    (3)---------(2)
      |           |  Interpolation by default is done through vectors:
      |           |  (zero point -> 1st point)
      |           |  (3-rd point -> 2nd point)
    (0)---------(1)
*/
Gauge::Gauge(UIContainer *parent) :UIContainer(parent) {
  background = NULL;
  bar = NULL;
  label = new Label(this);
  firstBasisVector = make_pair(0, 1);
  secondBasisVector = make_pair(3, 2);
  value = 0;
  labelEnabled = false;
}

Gauge::~Gauge() {
  delete label;
}

void Gauge::normalize() {
  if (value < GAUGE_MIN) {
    value = GAUGE_MIN;
  }
  if (value > GAUGE_MAX) {
    value = GAUGE_MAX;
  }
}

Outcome Gauge::render() {
  if (!isVisible()) {
    return OK;
  }

  ERROR_IF(background == NULL && bar == NULL, L"Nothing to render", ERROR);

  ASSERT(engine->beginTransform());
  ASSERT(engine->translate(getX(), getY(), getZ()));
  if (background != NULL) {
    background->setSize(getWidth(), getHeight());
    ASSERT(background->render());
  }

  if (bar != NULL) {
    /* Apply texture coords interpolation */
    float t = (float)(value - GAUGE_MIN) / (GAUGE_MAX - GAUGE_MIN);

    Vector2f startCoords1 = bar->getTexCoords(firstBasisVector.first);
    Vector2f endCoords1 = bar->getTexCoords(firstBasisVector.second);
    bar->setTexCoords(firstBasisVector.second, startCoords1 + (endCoords1 - startCoords1) * t);

    Vector2f startCoords2 = bar->getTexCoords(secondBasisVector.first);
    Vector2f endCoords2 = bar->getTexCoords(secondBasisVector.second);
    bar->setTexCoords(secondBasisVector.second, startCoords2 + (endCoords2 - startCoords2) * t);

    /* Resize bar sprite */
    bar->setSize(t * getWidth(), getHeight());

    /* Render bar */
    ASSERT(bar->render());

    /* Restore texture coordinates */
    bar->setTexCoords(firstBasisVector.second, endCoords1);
    bar->setTexCoords(secondBasisVector.second, endCoords2);
  }

  if (labelEnabled) {
    Vector3f position = label->getPosition();
    label->setText(StringTool::intToStr((int)(100.0 * ((float)value - GAUGE_MIN) / (GAUGE_MAX - GAUGE_MIN))) + L" %");

    ASSERT(engine->beginTransform());
    ASSERT(engine->translate(position[0], position[1], position[2]));
    ASSERT(label->render());
    ASSERT(engine->endTransform());
  }
  ASSERT(engine->endTransform());

  return OK;
}

void Gauge::setBackgroundSprite(AbstractSprite *backgroundSprite) {
  background = backgroundSprite;
}

AbstractSprite* Gauge::getBackgroundSprite() {
  return background;
}

void Gauge::setBarSprite(Sprite *barSprite) {
  bar = barSprite;
}

Sprite* Gauge::getBarSprite() {
  return bar;
}

Label* Gauge::getLabel() {
  return label;
}

void Gauge::setLabel(bool isEnabled) {
  labelEnabled = isEnabled;
}

void Gauge::setValue(int newValue) {
  value = newValue;
  normalize();
}

int Gauge::getValue() {
  return value;
}

void Gauge::setBasisVector(uint index, pair<int, int> texCoordsPair) {
  if (index == 0) {
    firstBasisVector = texCoordsPair;
  } else
    if (index == 1) {
      secondBasisVector = texCoordsPair;
    } else {
      LOG_ERROR(L"Index " + StringTool::intToStr(index) + L" is out of bounds");
    }
}

pair<int, int> Gauge::getBasisVector(uint index) {
  if (index == 0) {
    return firstBasisVector;
  } else
    if (index == 1) {
      return secondBasisVector;
    } else {
      EPIC_FAIL(L"Index " + StringTool::intToStr(index) + L" is out of bounds");
    }
}

}
