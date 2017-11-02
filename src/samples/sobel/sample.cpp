// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "engine/windows/window_system_factory.h"
#include "engine/engines/gl_engine.h"
#include "engine/cameras/ortho_camera.h"
#include "engine/ui/gui_builder.h"

/* Here we define window properties */
const int winX = 0;
const int winY = 0;
const int winWidth = 300;
const int winHeight = 300;

using namespace ve;

/* Key objects of the application */
WindowSystem  *xwin = NULL;
ve::Window    *win = NULL;
GLEngine      *engine = NULL;

int main() {
  /* The first class to be created */
  /* Create window system class. It is key point to access window functions */
  xwin = WindowSystemFactory::createWindowSystem();

  /* Now, you can create window defining caption, position ans size */
  win = xwin->createWindow(L"NewWindow", winX, winY, winWidth, winHeight);
  xwin->show(win);

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
  camera->apply();

  /* Create font for label */
  ve::Font *font = NULL;
  font = xwin->createFont(engine, new FontDescriptor(COURIER_FONT_FAMILY, SLANT_ROMAN, SETWIDTH_ANY,
    14, SPACING_MONOSPACED, 75, 75));
  ASSERT(font->initialize(256));

  /* 4. Create sprite object, border object and FPS label */
  Sprite *sprite = GUIBuilder::createSpriteFromFile(engine, "../../data/logo.png");
  CHECK_POINTER(sprite);
  UI *gui = new UI(engine);
  Label *fpsLabel = gui->createLabel(gui->getActiveDesktop(), L"", WHITE);
  fpsLabel->setFont(font);
  Border *border = gui->createBorder(gui->getActiveDesktop());

  /* Set sprite parameters */
  sprite->setSize(winWidth / 2, winHeight / 2);

  /* Set border parameters */
  border->setSize(winWidth / 2, winHeight / 2);

  /* Create shaders with Sobel operator */
  Shader *vShader = engine->createVertexShader();
  ASSERT(vShader->load("../../data/sobel.vsh", true, SCF_LOG_ERRORS));

  Shader *pShader = engine->createPixelShader();
  ASSERT(pShader->load("../../data/sobel.fsh", true, SCF_LOG_ERRORS));

  Program *program = engine->createProgram();
  ASSERT(program->setVertexShader(vShader));
  ASSERT(program->setPixelShader(pShader));
  ASSERT(program->link(SCF_LOG_ERRORS));

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

    /* Set positions for left image and render without shaders */
    border->setPosition(Vector3f(0.0f, winHeight / 4.0f, 0.4f));
    sprite->setPosition(Vector3f(0.0f, winHeight / 4.0f, 0.4f));
    ASSERT(sprite->render());
    ASSERT(gui->render());

    /* Set positions for right image and render with shaders */
    border->setPosition(Vector3f(winWidth / 2.0f, winHeight / 4.0f, 0.4f));
    sprite->setPosition(Vector3f(winWidth / 2.0f, winHeight / 4.0f, 0.4f));

    stateManager->pushStates(SHADERS_STATE);
    ASSERT(stateManager->setShadersState(ShadersState(program)));
    ASSERT(program->setTexture("sampler", 0));
    ASSERT(sprite->render());
    stateManager->popStates(SHADERS_STATE);

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
