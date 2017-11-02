// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "engine/windows/window_system_factory.h"
#include "engine/engines/gl_engine.h"
#include "engine/cameras/ortho_camera.h"
#include "engine/ui/slot.h"
#include "engine/ui/slot_item.h"

/* Here we define window properties */
const int winX      = 0;
const int winY      = 0;
const int winWidth  = 400;
const int winHeight = 400;
const int GRID = 6;

using namespace ve;

/* Key objects of the application */
WindowSystem  *xwin   = NULL;
ve::Window    *win    = NULL;
GLEngine      *engine = NULL;

class MySlotItem : public SlotItem {
public:
  MySlotItem(UIContainer *parent, Sprite *sprite) :SlotItem(parent, sprite) {
  }

  virtual void onStartDragging() {
    setPosition(getX(), getY(), getZ() - 0.1f);
  }

  virtual void onStopDragging() {
    setPosition(getX(), getY(), getZ() + 0.1f);
  }
};

int main() {
  /* The first class to be created */
  /* Create window system class. It is key point to access window functions */
  xwin = WindowSystemFactory::createWindowSystem();

  /* Now, you can create window defining caption, position ans size */
  win = xwin->createWindow(L"Inventory", winX, winY, winWidth, winHeight);
  xwin->show(win);

  /* And finally an engine can be created to use power of OpenGL renderer */
  engine = GLEngine::getInstance();
  ASSERT(engine->initialize(win));
  GPUStateManager *stateManager = engine->getStateManager();

  /* Configuring the first application */
  /* 1. Depth test                     */
  // Enable depth test to correcly show geometry
  stateManager->setDepthTestState(DepthTestState(LEQUAL));
  // We will clear depth buffer using 1.0 value
  stateManager->setClearDepthValue(1.0);

  /* 2. Clearing color will be black */
  stateManager->setClearColorValue(0.0, 0.0, 0.0, 0.0);

  /* 3. Camera settings */
  /* 'Usual' coorinate system will be used. (0, 0) at the left-topmost corner, */
  /* x-Axis goes from left to right and y-Axis from top to bottom              */
  OrthoCamera *camera = new OrthoCamera(engine, win->getClientViewport(), false, true);
  camera->apply();

  /* Create font for label */
  ve::Font *font = NULL;
  font = xwin->createFont(engine, new FontDescriptor(COURIER_FONT_FAMILY, SLANT_ROMAN, SETWIDTH_ANY,
    14, SPACING_MONOSPACED, 75, 75));
  ASSERT(font->initialize(256));

  UI *gui = new UI(engine);
  Label *fpsLabel = gui->createLabel(gui->getActiveDesktop(), L"", WHITE);
  fpsLabel->setFont(font);

  /* Create slots */
  std::vector<Slot*> slots;
  float x = 70;
  float y = 70;
  float w = 40;
  float h = 40;

  for (int i = 0; i < GRID; i++) {
    for (int j = 0; j < GRID; j++) {
      Border *border = gui->createBorder(gui->getActiveDesktop(), GRAY, 3);
      Slot *slot = new Slot(gui->getActiveDesktop(), border);

      slot->setPosition(x + w * j, y + h * i);
      slot->setSize(w - 5, h - 5);

      slots.push_back(slot);
    }
  }

  /* Create slot items */
  std::vector<SlotItem*> items;

  for (int i = 0; i < GRID; i++) {
    SimpleSprite *sprite = new SimpleSprite(engine
      , Vector4f(float(i - 1) / GRID, 1.0f - float(i - 1) / GRID, 0.0f, 1.0f));
    SlotItem *item = new MySlotItem(gui->getActiveDesktop(), sprite);

    item->setPosition(x + w * i + 3, y + 3);
    item->setSize(w - 10, h - 10);

    for (ve::uint j = 0; j < slots.size(); j++) {
      item->addSlot(slots[j]);
    }

    item->setSlot(slots[i]);
    slots[i]->assign(item);

    items.push_back(item);
  }

  bool finish = false;
  while (!finish) {
    while (win->hasAvailableEvent()) {
      SystemEvent *ev = win->getNextEvent();
      if (ev != NULL && ev->getType() == WINDOW_CLOSE) {
        finish = true;
      }

      gui->processMessage(ev);
    }

    /* Clear back buffer color & depth buffer */
    ASSERT(engine->clear(ClearFlag(COLOR | DEPTH)));

    for (ve::uint i = 0; i < slots.size(); i++) {
      ASSERT(slots[i]->render());
    }
    ASSERT(gui->render());

    /* Compute FPS (average value for 5 seconds) */
    fpsLabel->setText(L"FPS: " + StringTool::floatToStr(win->getFPS(), 2));

    /* Swap frame and back buffers */
    win->swap();
  }

  delete engine;
  delete xwin;

  return 0;
}

