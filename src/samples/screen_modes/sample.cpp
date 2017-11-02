// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "engine/windows/window_system_factory.h"
#include "engine/engines/gl_engine.h"
#include "engine/cameras/ortho_camera.h"
#include "engine/ui/ui.h"
#include "engine/tools/string_tool.h"
#include "engine/events/window_event.h"

using namespace ve;

/* Here we define window properties */
const int winX = 0;
const int winY = 0;
const int winWidth = 350;
const int winHeight = 200;

/* Key objects of the application */
WindowSystem  *xwin = NULL;
ve::Window    *win = NULL;
GLEngine      *engine = NULL;

int main() {
  /* The first class to be created */
  /* Create window system class. It is key point to access window functions */
  xwin = WindowSystemFactory::createWindowSystem();
  std::vector<ScreenMode> modes = xwin->getAvailableResolutions();

  int oldWidth, oldHeight;
  xwin->getScreenResolution(oldWidth, oldHeight);

  if (modes.size() > 0) {
    xwin->setScreenResolution(ScreenMode(1024, 768));
  }

  /* Now, you can create window defining caption, position ans size */
  CHECK_POINTER(win = xwin->createWindow(L"NewWindow", winX, winY, winWidth, winHeight, true));
  ASSERT(xwin->show(win));

  /* Show available resolutions in the console */
  printf("Supported screen resolutions:\n");
  for (ve::uint i = 0; i < modes.size(); i++) {
    printf("%d x %d\n", modes[i].width, modes[i].height);
  }
  printf("Current resolution: %d x %d\n", oldWidth, oldHeight);

  /* And finally an engine can be created to use power of OpenGL renderer */
  engine = GLEngine::getInstance();
  ASSERT(engine->initialize(win));
  GPUStateManager* stateManager = engine->getStateManager();

  /* Configuring the first application */
  /* 1. Depth test                     */
  stateManager->setDepthTestState(DepthTestState(LEQUAL));      // Enable depth test to correcly show geometry
  stateManager->setClearDepthValue(1.0);     // We will clear depth buffer using 1.0 value

  /* 2. Clearing color will be black */
  stateManager->setClearColorValue(0.0, 0.0, 0.0, 0.0);

  /* 3. Camera settings */
  /* 'Usual' coorinate system will be used. (0, 0) at the left-topmost corner, */
  /* x-Axis goes from left to right and y-Axis from top to bottom              */
  OrthoCamera *camera = new OrthoCamera(engine, win->getClientViewport(), false, true);
  ASSERT(camera->apply());

  /* 4. Create interface */
  UI *gui = new UI(engine);

  /* 5. Create fonts */
  ve::Font *font = NULL;

  font = xwin->createFont(engine, new FontDescriptor(COURIER_FONT_FAMILY, SLANT_ROMAN, SETWIDTH_ANY,
    14, SPACING_MONOSPACED, 75, 75));

  CHECK_POINTER(font);
  CHECK_RESULT(font->initialize(256), L"Font initializtion failed");

  /* Create label to show FPS */
  Label *fpsLabel = gui->createLabel(gui->getActiveDesktop(), L"FPS: -", WHITE);
  fpsLabel->setFont(font);
  fpsLabel->setPosition(Vector3f(0, 0, 0.3f));

  bool finish = false;
  while (!finish) {
    while (win->hasAvailableEvent()) {
      SystemEvent *ev = win->getNextEvent();
      if (ev != NULL && (ev->getType() == WINDOW_CLOSE || ev->getType() == KEY_PRESS)) {
        finish = true;
      }
    }
    /* Clear back buffer color & depth buffer */
    ASSERT(engine->clear(ClearFlag(COLOR | DEPTH)));

    /* Compute FPS (average value for 5 seconds) */
    fpsLabel->setText(L"FPS: " + StringTool::floatToStr(win->getFPS(), 2) + L" [Press any key to close window]");

    /* Show labels */
    ASSERT(gui->render());

    /* Swap frame and back buffers */
    CHECK_RESULT(win->swap(), L"Swap failed");
  }

  /* Restore screen resolution */
  if (modes.size() > 0) {
    xwin->setScreenResolution(ScreenMode(oldWidth, oldHeight));
  }

  /* Free memory */
  delete engine;
  delete xwin;

  return 0;
}

