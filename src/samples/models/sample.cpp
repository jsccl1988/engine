// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "engine/windows/window_system_factory.h"
#include "engine/engines/gl_engine.h"
#include "engine/cameras/camera.h"
#include "engine/loaders/3ds_loader.h"

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

float angle = 0;

int main() {
  /* The first class to be created */
  /* Create window system class. It is key point to access window functions */
  xwin = WindowSystemFactory::createWindowSystem();

  /* Now, you can create window defining caption, position ans size */
  CHECK_POINTER(win = xwin->createWindow(L"Model", winX, winY, winWidth, winHeight));
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
  Camera *camera = new Camera(engine, win->getClientViewport());
  camera->setPosition(Vector3f(-10, -60, 40));
  camera->setUp(Vector3f(0, 0, 1));
  camera->setLook(Vector3f(0, 1, -1));
  ASSERT(camera->apply());

  /* 4. Create loader for 3ds models format and load model */
  _3dsLoader *loader = new _3dsLoader();
  CHECK_RESULT(loader->loadFromFile(std::string("../../data/elf.3ds")), L"Loading failed");
  Model *model = new Model(engine);
  CHECK_RESULT(model->update(loader->getMeshList()), L"Update failed");

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

    //ASSERT(stateManager->setPolygonMode(FRONT_AND_BACK, FILL));
    //ASSERT(stateManager->setColorState(ColorState(GREEN)));

    //for (uint i = 0; i < model->getMeshesCount(); i++) {
    //  Vector3f center = model->getMeshCenter(i);
    //  ASSERT(engine->beginTransform());
    //  ASSERT(engine->rotate(angle, 0.0, 0.0, 1.0));
    //  ASSERT(engine->translate(-center[0], -center[1], -center[2]));
    //  ASSERT(model->renderMesh(i));
    //  ASSERT(engine->endTransform());
    //}

    ASSERT(stateManager->setPolygonMode(FRONT_AND_BACK, LINE));
    ASSERT(stateManager->depthOffsetParams(-.1f, -.1f));
    ASSERT(stateManager->enableDepthOffset(LINE, true));
    ASSERT(stateManager->setColorState(ColorState(1.0f, 1.0f, 0.0f)));
    for (uint i = 0; i < model->getMeshesCount(); i++) {
      Vector3f center = model->getMeshCenter(i);
      ASSERT(engine->beginTransform());
      ASSERT(engine->rotate(angle, 0.0, 0.0, 1.0));
      ASSERT(engine->translate(-center[0], -center[1], -center[2]));
      ASSERT(model->renderMesh(i));
      ASSERT(engine->endTransform());
    }
    ASSERT(stateManager->enableDepthOffset(LINE, false));

    /* Animation */
    angle = angle + 0.1;

    /* Swap frame and back buffers */
    CHECK_RESULT(win->swap(), L"Swap failed");
  }

  delete engine;
  delete xwin;

  return 0;
}
