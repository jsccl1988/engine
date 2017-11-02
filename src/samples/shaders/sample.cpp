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
  CHECK_POINTER(win = xwin->createWindow(L"Shaders", winX, winY, winWidth, winHeight));
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

  OrthoCamera *camera2D = new OrthoCamera(engine, win->getClientViewport(), false, true);

  /* 4. Create shaders */
  Shader *vShader = engine->createVertexShader();
  CHECK_POINTER(vShader);
  ASSERT(vShader->load("../../data/source.vsh", true, SCF_LOG_ERRORS));

  Shader *fShader = engine->createPixelShader();
  CHECK_POINTER(fShader);
  ASSERT(fShader->load("../../data/source.fsh", true, SCF_LOG_ERRORS));

  Program *program = engine->createProgram();
  CHECK_POINTER(program);
  ASSERT(program->setVertexShader(vShader));
  ASSERT(program->setPixelShader(fShader));
  ASSERT(program->link(SCF_LOG_ERRORS));

  /* 5. Create loader for 3ds models format and load model */
  _3dsLoader *loader = new _3dsLoader();
  CHECK_RESULT(loader->loadFromFile(std::string("../../data/elf.3ds")), L"Loading failed");
  Model *model = new Model(engine);
  CHECK_RESULT(model->update(loader->getMeshList()), L"Update failed");

  // /* Create font for label */
  // ve::Font *font = NULL;
  // font = xwin->createFont(engine, new FontDescriptor(COURIER_FONT_FAMILY, SLANT_ROMAN, SETWIDTH_ANY,
  //   14, SPACING_MONOSPACED, 75, 75));
  // ASSERT(font->initialize(256));

  UI *gui = new UI(engine);

  // Label *fpsLabel = gui->createLabel(gui->getActiveDesktop(), L"", WHITE);
  // fpsLabel->setPosition(Vector3f(0, 0, 0));
  // fpsLabel->setFont(font);

  bool finish = false;
  while (!finish) {
    while (win->hasAvailableEvent()) {
      SystemEvent *ev = win->getNextEvent();
      if (ev != NULL && ev->getType() == WINDOW_CLOSE) {
        finish = true;
      }
    }

    ASSERT(camera->apply());
    /* Clear back buffer color & depth buffer */
    ASSERT(engine->clear(ClearFlag(COLOR | DEPTH)));
    ASSERT(stateManager->setColorState(ColorState(BLACK)));

    stateManager->pushStates(SHADERS_STATE);
    ASSERT(stateManager->setShadersState(program));
    for (ve::uint i = 0; i < model->getMeshesCount(); i++) {
      Vector3f center = model->getMeshCenter(i);
      ASSERT(engine->beginTransform());
      ASSERT(engine->rotate(angle, 0.0, 0.0, 1.0));
      ASSERT(engine->translate(-center[0], -center[1], -center[2]));
      ASSERT(model->renderMesh(i));
      ASSERT(engine->endTransform());
    }
    stateManager->popStates(SHADERS_STATE);

    /* Animation */
    angle = angle + 0.1f;

    /* Set usual for GUI coordiante system */
    ASSERT(camera2D->apply());

    /* Show FPS */
    // fpsLabel->setText(L"FPS: " + StringTool::floatToStr(win->getFPS(), 2));
    ASSERT(gui->render());

    /* Swap frame and back buffers */
    CHECK_RESULT(win->swap(), L"Swap failed");
  }

  delete engine;
  delete xwin;

  return 0;
}
