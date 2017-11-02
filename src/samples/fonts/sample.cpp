// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "engine/windows/window_system_factory.h"
#include "engine/engines/gl_engine.h"
#include "engine/cameras/ortho_camera.h"
#include "engine/ui/ui.h"
#include "engine/tools/string_tool.h"
#include "engine/fonts/font_cache.h"

using namespace ve;

/* Here we define window properties */
const int winX = 0;
const int winY = 0;
const int winWidth = 300;
const int winHeight = 450;

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
  stateManager->setClearColorValue(0.5, 0.5, 0.5, 1.0);

  /* 3. Camera settings */
  /* 'Usual' coorinate system will be used. (0, 0) at the left-topmost corner, */
  /* x-Axis goes from left to right and y-Axis from top to bottom              */
  OrthoCamera *camera = new OrthoCamera(engine, xwin->getClientViewport(win), false, true);
  ASSERT(camera->apply());

  /* 4. Create interface */
  UI *gui = new UI(engine);

  /* 5. Create fonts */
  const int FONTS_COUNT = 5;
  ve::Font **fonts = new ve::Font*[FONTS_COUNT];

  fonts[0] = xwin->createFont(engine, new FontDescriptor(COURIER_FONT_FAMILY, SLANT_ROMAN, SETWIDTH_ANY,
    14, SPACING_MONOSPACED, 100, 100));
  fonts[1] = xwin->createFont(engine, new FontDescriptor(COURIER_FONT_FAMILY, SLANT_ROMAN, SETWIDTH_ANY,
    14, SPACING_MONOSPACED, 75, 75));
  fonts[2] = xwin->createFont(engine, new FontDescriptor(TIMES_FONT_FAMILY, SLANT_ITALIC, SETWIDTH_ANY,
    14, SPACING_PROPORTIONAL, 100, 100));
  fonts[3] = xwin->createFont(engine, new FontDescriptor(HELVETICA_FONT_FAMILY, SLANT_OBLIQUE, SETWIDTH_ANY,
    14, SPACING_PROPORTIONAL, 100, 100));
  fonts[4] = xwin->createFont(engine, new FontDescriptor(TIMES_FONT_FAMILY, SLANT_ROMAN, SETWIDTH_ANY,
    14, SPACING_PROPORTIONAL, 100, 100));

  for (int i = 0; i < FONTS_COUNT; i++) {
    CHECK_POINTER(fonts[i]);
    CHECK_RESULT(fonts[i]->initialize(256), L"Font initializtion failed");
  }

  /* Retrieve active desktop */
  Desktop *desktop = gui->getActiveDesktop();

  /* Create label to show FPS */
  Label *fpsLabel = gui->createLabel(desktop, L"FPS: -", WHITE);
  fpsLabel->setFont(fonts[0]);
  fpsLabel->setPosition(Vector3f(0.0f, 0.0f, 0.3f));

  /* Create labels to show fonts */
  Label **labels = new Label*[FONTS_COUNT];
  for (int i = 0; i < FONTS_COUNT; i++) {
    labels[i] = gui->createLabel(desktop, L"VR Engine 'Font sample'", WHITE);
    labels[i]->setFont(fonts[i]);
    labels[i]->setPosition(Vector3f(30.0f, 50.0f + 20.0f * i, 0.3f));
  }

  /* Create sprite to show FontCache */
  Sprite *sprite = new Sprite(engine);
  sprite->setSize(256, 256);
  sprite->setPosition(Vector3f(20, 170, 0));
  sprite->setTexture(fonts[0]->getCache()->getTexture());
  sprite->disableTransparency();

  bool finish = false;
  while (!finish) {
    while (win->hasAvailableEvent()) {
      SystemEvent *ev = win->getNextEvent();
      if (ev != NULL && ev->getType() == WINDOW_CLOSE) {
        finish = true;
      }
    }
    /* Clear back buffer color & depth buffer */
    ASSERT(engine->clear(ClearFlag(COLOR | DEPTH)));

    /* Show labels */
    ASSERT(gui->render());
    ASSERT(sprite->render());

    /* Compute FPS (average value for 5 seconds) */
    fpsLabel->setText(L"FPS: " + StringTool::floatToStr(win->getFPS(), 2));

    /* Swap frame and back buffers */
    CHECK_RESULT(win->swap(), L"Swap failed");
  }

  /* Free memory */
  delete engine;
  delete xwin;

  return 0;
}
