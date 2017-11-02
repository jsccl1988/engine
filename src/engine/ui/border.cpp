// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "ui/border.h"
#include "ui/ui.h"
#include "engines/engine.h"
#include "tools/string_tool.h"

namespace ve {

Border::Border(UIContainer *parent) :UIControl(parent) {
  color = WHITE;
  lineWidth = 1;
  mask = ALL;

  buffersState.vertices = BufferDesc(3, FLOAT, 0, 0, false);
}

Border::Border(UIContainer *parent, int width, int height, Vector4f color) :UIControl(parent) {
  setSize(width, height);

  this->color = color;
  lineWidth = 1;
  mask = ALL;

  buffersState.vertices = BufferDesc(3, FLOAT, 0, 0, false);
}

Border::Border(UIContainer *parent, Vector4f color, int lineWidth) :UIControl(parent) {
  this->color = color;
  this->lineWidth = lineWidth;
  mask = ALL;

  buffersState.vertices = BufferDesc(3, FLOAT, 0, 0, false);
}

void Border::setLineWidth(int newWidth) {
  lineWidth = newWidth;
}

int Border::getLineWidth() {
  return lineWidth;
}

void Border::setColor(Vector4f newColor) {
  color = newColor;
}

Vector4f Border::getColor() {
  return color;
}

Outcome Border::render() {
  if (!isVisible()) {
    return OK;
  }

  GPUStateManager *stateManager = engine->getStateManager();
  int width = getWidth();
  int height = getHeight();
  float vertices[] = { 0, 0, 0, width, 0, 0, width, height, 0, 0, height, 0 };

  stateManager->pushStates(COLOR_STATE | BUFFERS_STATE);

  CHECK_RESULT(stateManager->setLineWidth(lineWidth), L"Line width: " + StringTool::intToStr(lineWidth));
  ASSERT(engine->beginTransform());
  ASSERT(engine->translate(getX(), getY(), getZ()));

  buffersState.vertices.data = vertices;

  ASSERT(stateManager->setColorState(ColorState(color[0], color[1], color[2])));
  ASSERT(stateManager->setBuffersState(buffersState));

  if (mask == ALL) {
    ASSERT(engine->drawPrimitives(LINE_LOOP, 0, 4));
  } else {
    vector<ushort> indices;

    if (mask & UP) {
      indices.push_back(0);
      indices.push_back(1);
    }

    if (mask & RIGHT) {
      indices.push_back(1);
      indices.push_back(2);
    }

    if (mask & LEFT) {
      indices.push_back(0);
      indices.push_back(3);
    }

    if (mask & DOWN) {
      indices.push_back(2);
      indices.push_back(3);
    }

    ASSERT(engine->drawIndexedPrimitives(LINES, indices.size(), UNSIGNED_SHORT, &indices[0]));
  }

  ASSERT(stateManager->setLineWidth(1.0));
  ASSERT(engine->endTransform());

  stateManager->popStates(COLOR_STATE | BUFFERS_STATE);

  return OK;
}

/**
    Sets border mask. Use constants defines in this class to define border mask.
    Only sides defines by this mask will be shown.
    For example: setMask(Border::UP + Border::LEFT) will show only upper and left side.
*/
void Border::setMask(uchar newMask) {
  mask = newMask;
}

/**
    Returns border sides mask.
    @return Side mask for this border.
*/
uchar Border::getMask() {
  return mask;
}

}
