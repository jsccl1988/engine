// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "engine/windows/window_system_factory.h"
#include "engine/engines/gl_engine.h"
#include "engine/cameras/ortho_camera.h"
#include "engine/ui/ui.h"

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
  stateManager->setClearDepthValue(1.0);

  /* 2. Clearing color will be black */
  stateManager->setClearColorValue(0.0, 0.0, 0.0, 0.0);

  /* 3. Camera settings */
  /* 'Usual' coorinate system will be used. (0, 0) at the left-topmost corner, */
  /* x-Axis goes from left to right and y-Axis from top to bottom              */
  OrthoCamera *camera = new OrthoCamera(engine, win->getClientViewport(), false, true);
  ASSERT(camera->apply());

  /* 4. Create main interface class and form */
  UI *gui = new UI(engine);

  /* Get active desktop */
  Desktop *desktop = gui->getActiveDesktop();

  Form* form = gui->createForm(desktop);

  /* 5. Set form caption, border and background */
  SimpleSprite *background = new SimpleSprite(engine, Vector4f(0.3f, 0.0f, 0.0f, 1.0f));
  form->setBackground(background);

  SimpleSprite *caption = new SimpleSprite(engine, Vector4f(0.4f, 0.0f, 0.0f, 1.0f));
  ve::Font *font = xwin->createFont(engine, new FontDescriptor());
  CHECK_POINTER(font);
  ASSERT(font->initialize(256));

  Label *fpsLabel = gui->createLabel(desktop, L"", WHITE);
  fpsLabel->setPosition(Vector3f(0, 0, 0));
  fpsLabel->setFont(font);

  Label *label = gui->createLabel(NULL, L"Caption [Drag me]", WHITE);
  label->setFont(font);
  label->setPosition(Vector3f(35, 2, 0));
  caption->setLabel(label);
  form->setCaption(caption);

  Border *formBorder = gui->createBorder(NULL, RED, 1);
  form->setBorder(formBorder);
  caption->setBorder(formBorder);

  form->setPosition(Vector3f(10, 10, 0.5));
  form->setSize(200, 200);
  form->setMovable(true);

  /* Create and configure button */
  SimpleSprite *buttonSprite = new SimpleSprite(engine, Vector4f(0.5, 0.0, 0.0, 1.0));
  buttonSprite->setBorder(formBorder);
  Label *buttonCaption = gui->createLabel(NULL, L"Press Me", WHITE);
  buttonCaption->setPosition(Vector3f(20, 2, 0));
  buttonCaption->setFont(font);
  buttonSprite->setLabel(buttonCaption);

  SimpleSprite *onCoverSprite = new SimpleSprite(engine, Vector4f(0.8f, 0.0f, 0.0f, 1.0f));
  onCoverSprite->setBorder(formBorder);
  Label *onCoverCaption = gui->createLabel(NULL, L"It works", WHITE);
  onCoverCaption->setPosition(Vector3f(20, 2, 0));
  onCoverCaption->setFont(font);
  onCoverSprite->setLabel(onCoverCaption);

  Button *button = gui->createButton(form, 100, 20);
  button->setPosition(Vector3f(50, 140, 0));
  button->setSprites(buttonSprite, onCoverSprite, onCoverSprite);

  /* Prepare checkbox */
  Checkbox *checkbox = gui->createCheckbox(form);
  Button *checkboxButton = gui->createButton(checkbox, 15, 15);

  SimpleSprite *checkboxSprite = new SimpleSprite(engine, WHITE);
  Border *checkboxBorder = gui->createBorder(checkbox, BLACK, 3);
  checkboxSprite->setBorder(checkboxBorder);

  SimpleSprite *checkboxPressedSprite = new SimpleSprite(engine, GRAY);
  checkboxPressedSprite->setBorder(checkboxBorder);
  checkboxButton->setSprites(checkboxSprite, checkboxPressedSprite, checkboxSprite);

  Label *checkboxLabel = gui->createLabel(checkbox, L"Checkbox", WHITE);
  checkboxLabel->setFont(font);
  checkboxLabel->setPosition(Vector3f(15, 1, 0));
  checkbox->setLabel(checkboxLabel);
  checkbox->setButton(checkboxButton);
  checkbox->setPosition(Vector3f(30, 30, 0));

  /* Prepare gauge */
  Gauge *gauge = gui->createGauge(form);
  SimpleSprite *gaugeBackground = new SimpleSprite(engine, Vector4f(0.5, 0.0, 0.0, 1.0));
  gauge->setBackgroundSprite(gaugeBackground);
  SimpleSprite *gaugeBar = new SimpleSprite(engine, WHITE);
  Border *gaugeBorder = gui->createBorder(gauge, BLACK, 1);
  gaugeBar->setBorder(gaugeBorder);
  gauge->setBarSprite(gaugeBar);
  gauge->setSize(140, 20);
  gauge->setPosition(Vector3f(30, 60, 0));
  gauge->setValue(50);
  gauge->getLabel()->setFont(font);
  gauge->getLabel()->setColor(BLACK);
  gauge->getLabel()->setPosition(Vector3f(30, 2, 0));
  gauge->setLabel(true);

  /* Prepare editbox */
  Editbox *editbox = gui->createEditbox(form);
  editbox->setBackgroundSprite(gaugeBar);
  SimpleSprite *activeBackground = new SimpleSprite(engine, Vector4f(0.8f, 0.8f, 0.8f, 1.0f));
  Border *activeBorder = gui->createBorder(editbox, WHITE, 2);
  activeBackground->setBorder(activeBorder);
  editbox->setActiveBackgroundSprite(activeBackground);
  editbox->getLabel()->setColor(BLACK);
  editbox->getLabel()->setFont(font);
  editbox->getLabel()->setText(L"Edit Me");
  editbox->setSize(140, 20);
  editbox->setPosition(Vector3f(30, 90, 0));

  bool finish = false;
  time_t lastUpdate = 0;
  time(&lastUpdate);
  while (!finish) {
    while (win->hasAvailableEvent()) {
      SystemEvent *ev = win->getNextEvent();
      gui->processMessage(ev);
      if (ev != NULL && ev->getType() == WINDOW_CLOSE) {
        finish = true;
      }
    }
    /* Clear back buffer color & depth buffer */
    ASSERT(engine->clear((ClearFlag)((int)COLOR | (int)DEPTH)));

    ASSERT(gui->render());

    time_t curTime = 0;
    time(&curTime);

    if (curTime > lastUpdate + 2) {
      gauge->setValue(gauge->getValue() + 3);
      if (gauge->getValue() == 100) {
        gauge->setValue(0);
      }
      lastUpdate = curTime;
    }

    fpsLabel->setText(L"FPS: " + StringTool::floatToStr(win->getFPS(), 2));

    /* Swap frame and back buffers */
    CHECK_RESULT(win->swap(), L"Swap failed");
  }

  delete engine;
  delete xwin;

  return 0;
}
