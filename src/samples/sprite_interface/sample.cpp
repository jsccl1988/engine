// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "engine/windows/window_system_factory.h"
#include "engine/engines/gl_engine.h"
#include "engine/cameras/ortho_camera.h"
#include "engine/tools/string_tool.h"
#include "engine/ui/gui_builder.h"

using namespace ve;

/* Here we define window properties */
const int winX = 0;
const int winY = 0;
const int winWidth = 500;
const int winHeight = 500;

/* Key objects of the application */
WindowSystem  *xwin = NULL;
ve::Window    *win = NULL;
GLEngine      *engine = NULL;

int main() {
  /* The first class to be created */
  /* Create window system class. It is key point to access window functions */
  xwin = WindowSystemFactory::createWindowSystem();

  /* Now, you can create window defining caption, position ans size */
  CHECK_POINTER(win = xwin->createWindow(L"NewWindow", winX, winY, winWidth, winHeight));
  ASSERT(xwin->show(win));

  /* And finally an engine can be created to use power of OpenGL renderer */
  engine = GLEngine::getInstance();
  ASSERT(engine->initialize(win));
  GPUStateManager* stateManager = engine->getStateManager();

  /* Configuring the first application */
  /* 1. Depth test                     */
  // Enable depth test to correcly show geometry
  stateManager->setDepthTestState(DepthTestState(LEQUAL));
  // We will clear depth buffer using 1.0 value
  stateManager->setClearDepthValue(1.0f);

    /* 2. Clearing color will be black */
  stateManager->setClearColorValue(0.3f, 0.3f, 0.3f, 0.0f);

  /* 3. Camera settings */
  /* 'Usual' coorinate system will be used. (0, 0) at the left-topmost corner, */
  /* x-Axis goes from left to right and y-Axis from top to bottom              */
  OrthoCamera *camera = new OrthoCamera(engine, win->getClientViewport(), false, true);
  ASSERT(camera->apply());

  /* 4. Create main interface class and form */
  UI *gui = new UI(engine);
  Form* form = gui->createForm(gui->getActiveDesktop());

  /* 5. Set form caption, border and background */
  Sprite *background = GUIBuilder::createSpriteFromFile(engine, "../../data/form.tga");
  CHECK_POINTER(background);

  form->setBackground(background);

  ve::Font *font = xwin->createFont(engine, new FontDescriptor());
  CHECK_POINTER(font);
  ASSERT(font->initialize(256));

  form->setPosition(Vector3f(0, 0, 0.5));
  form->setSize(250, 250);

  /* Create and configure button */
  Sprite *btSprite = GUIBuilder::createSpriteFromFile(engine, "../../data/button.tga");
  CHECK_POINTER(btSprite);

  Sprite *btOnHoverSprite = GUIBuilder::createSpriteFromFile(engine, "../../data/buttonOnHover.tga");
  CHECK_POINTER(btOnHoverSprite);

  Button *button = gui->createButton(form, 120, 50);
  button->setPosition(Vector3f(60, 150, 0));
  button->setSprites(btSprite, btOnHoverSprite, btOnHoverSprite);

  /* Prepare checkbox */
  Checkbox *checkbox = gui->createCheckbox(form);
  Button *checkboxButton = gui->createButton(checkbox, 30, 30);

  Sprite *cbOffSprite = GUIBuilder::createSpriteFromFile(engine, "../../data/cbOff.tga");
  CHECK_POINTER(cbOffSprite);

  Sprite *cbOnSprite = GUIBuilder::createSpriteFromFile(engine, "../../data/cbOn.tga");
  CHECK_POINTER(cbOnSprite);

  checkboxButton->setSprites(cbOffSprite, cbOnSprite, cbOffSprite);

  Label *checkboxLabel = gui->createLabel(checkbox, L"Checkbox", BLACK);
  checkboxLabel->setFont(font);
  checkboxLabel->setPosition(Vector3f(checkboxButton->getWidth(), 10, 0.0));
  checkbox->setLabel(checkboxLabel);
  checkbox->setButton(checkboxButton);
  checkbox->setPosition(Vector3f(50, 40, 0));

  /* Prepare gauge */
  Gauge *gauge = gui->createGauge(form);
  SimpleSprite *gaugeBackground = new SimpleSprite(engine);
  gaugeBackground->setBackgroundColor(Vector4f(0.3f, 0.3f, 0.3f, 1.0f));
  gauge->setBackgroundSprite(gaugeBackground);

  Sprite *gSprite = GUIBuilder::createSpriteFromFile(engine, "../../data/bar.tga");
  CHECK_POINTER(gSprite);

  gauge->setBarSprite(gSprite);
  gauge->setSize(160, 20);
  gauge->setPosition(Vector3f(40, 80, 0));
  gauge->setValue(50);
  gauge->getLabel()->setFont(font);
  gauge->getLabel()->setColor(BLACK);
  gauge->getLabel()->setPosition(Vector3f(35, 2, 0));
  gauge->setLabel(true);

  /* Prepare editbox */
  Editbox *editbox = gui->createEditbox(form);

  SimpleSprite *edBackground = new SimpleSprite(engine);
  edBackground->setBackgroundColor(Vector4f(0.8f, 0.8f, 0.8f, 1.0f));
  Border *edBorder = gui->createBorder(editbox);
  edBorder->setColor(BLACK);
  edBorder->setLineWidth(2.5);
  edBackground->setBorder(edBorder);
  editbox->setBackgroundSprite(edBackground);

  SimpleSprite *activeBackground = new SimpleSprite(engine);
  activeBackground->setBackgroundColor(Vector4f(0.8f, 0.8f, 0.8f, 1.0f));
  Border *activeBorder = gui->createBorder(editbox);
  activeBorder->setColor(Vector4f(1.0f, 1.0f, 0.0f, 1.0f));
  activeBorder->setLineWidth(2.5);
  activeBackground->setBorder(activeBorder);
  editbox->setActiveBackgroundSprite(activeBackground);
  editbox->getLabel()->setColor(BLACK);
  editbox->getLabel()->setFont(font);
  editbox->getLabel()->setText(L"Edit Me");
  editbox->setSize(160, 20);
  editbox->setPosition(Vector3f(40.f, 110.f, 0.f));

  /* Create label to show FPS */
  Label *fpsLabel = gui->createLabel(gui->getActiveDesktop(), L"FPS: -", WHITE);
  fpsLabel->setFont(font);
  fpsLabel->setPosition(Vector3f(0, 0, 0));

  time_t lastUpdate = 0;
  time(&lastUpdate);
  bool finish = false;
  while (!finish) {
    while (win->hasAvailableEvent()) {
      SystemEvent *ev = win->getNextEvent();
      gui->processMessage(ev);
      if (ev != NULL && ev->getType() == WINDOW_CLOSE) {
        finish = true;
      }
    }
    /* Clear back buffer color & depth buffer */
    ASSERT(engine->clear(ClearFlag(COLOR | DEPTH)));

    fpsLabel->setText(L"FPS: " + StringTool::floatToStr(win->getFPS(), 2));
    ASSERT(gui->render());

    /* Set gauge value */
    time_t curMoment = 0;
    time(&curMoment);

    if (curMoment >= lastUpdate + 2) {
      lastUpdate = curMoment;

      gauge->setValue(gauge->getValue() + 3);
      if (gauge->getValue() == 100) {
        gauge->setValue(0);
      }
    }

    /* Swap frame and back buffers */
    CHECK_RESULT(win->swap(), L"Swap failed");
  }

  return 0;
}

