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

  /* 4. Create interface */
  UI *gui = new UI(engine);

  /* 5. Create fonts */
  ve::Font *font = NULL;

  font = xwin->createFont(engine, new FontDescriptor(COURIER_FONT_FAMILY, SLANT_ROMAN, SETWIDTH_ANY,
    14, SPACING_MONOSPACED, 75, 75));

  CHECK_POINTER(font);
  CHECK_RESULT(font->initialize(256), L"Font initializtion failed");

  /* Create label to show FPS */
  Desktop *desktop = gui->getActiveDesktop();
  Label *fpsLabel = gui->createLabel(desktop, L"FPS: -", WHITE);
  fpsLabel->setFont(font);
  fpsLabel->setPosition(Vector3f(0, 0, 0.3f));

  Label *mouseCoordsLabel = gui->createLabel(desktop, L"Mouse: -", WHITE);
  mouseCoordsLabel->setFont(font);
  mouseCoordsLabel->setPosition(Vector3f(0, 20, 0.3f));

  Label *keysLabel = gui->createLabel(desktop, L"Last letter pressed: -", WHITE);
  keysLabel->setFont(font);
  keysLabel->setPosition(Vector3f(0, 40, 0.3f));

  Label* mouseEventLabel = gui->createLabel(desktop, L"Mouse Event: -", WHITE);
  mouseEventLabel->setFont(font);
  mouseEventLabel->setPosition(Vector3f(0, 60, 0.3f));

  Label* winSizeLabel = gui->createLabel(desktop, L"Window Size: -", WHITE);
  winSizeLabel->setFont(font);
  winSizeLabel->setPosition(Vector3f(0, 80, 0.3f));

  bool finish = false;
  while (!finish) {
    while (win->hasAvailableEvent()) {
      SystemEvent *ev = win->getNextEvent();
      if (ev != NULL) {
        MouseEvent *me = NULL;
        KeyEvent *ke = NULL;
        WindowEvent *we = NULL;
        std::wstring key = L"";
        int keyCode = 0;

        switch (ev->getType()) {
        case MOUSE_MOTION:
          me = (MouseEvent*)ev;
          mouseCoordsLabel->setText(L"Mouse: (" + StringTool::intToStr(me->getX()) + L", " +
            StringTool::intToStr(me->getY()) + L")");
          break;

        case MOUSE_PRESS:
          me = (MouseEvent*)ev;
          mouseEventLabel->setText(L"Mouse Event: Mouse Press, Button #" + StringTool::intToStr(me->getButton()));
          break;

        case MOUSE_RELEASE:
          me = (MouseEvent*)ev;
          mouseEventLabel->setText(L"Mouse Event: Mouse Release, Button #" + StringTool::intToStr(me->getButton()));
          break;

        case KEY_PRESS:
          ke = (KeyEvent*)ev;
          keyCode = ke->getKeyCode();
          if ((keyCode >= L'a' && keyCode <= L'z') || (keyCode >= L'A' && keyCode <= L'Z')) {
            key = key + (wchar_t)ke->getKeyCode();
          }
          keysLabel->setText(L"Last letter pressed: " + key);
          break;

        case WINDOW_CLOSE:
          finish = true;
          break;

        case WINDOW_RESIZE:
          we = (WindowEvent*)ev;
          winSizeLabel->setText(L"Window Size: " + StringTool::intToStr(we->getWidth()) + L"x" +
            StringTool::intToStr(we->getHeight()));
          /* Reset camera with new settings */
          camera->setViewport(ViewportState(0, 0, we->getWidth(), we->getHeight()));
          ASSERT(camera->apply());
          break;

        default:
          break;
        }
      }
    }
    /* Clear back buffer color & depth buffer */
    ASSERT(engine->clear(ClearFlag(COLOR | DEPTH)));

    /* Compute FPS (average value for 5 seconds) */
    fpsLabel->setText(L"FPS: " + StringTool::floatToStr(win->getFPS(), 2));

    /* Show labels */
    ASSERT(gui->render());

    /* Swap frame and back buffers */
    CHECK_RESULT(win->swap(), L"Swap failed");
  }

  /* Free memory */
  delete engine;
  delete xwin;

  return 0;
}
