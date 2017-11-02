// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "engine/windows/window_system_factory.h"
#include "engine/engines/gl_engine.h"
#include "engine/cameras/ortho_camera.h"
#include "engine/ui/gui_builder.h"
#include "engine/tools/texture_tool.h"

/* Here we define window properties */
const int winX = 0;
const int winY = 0;
const int winWidth = 1000;
const int winHeight = 700;

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
  win = xwin->createWindow(L"Splatting sample", winX, winY, winWidth, winHeight);
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
  // ve::Font *font = NULL;
  // font = xwin->createFont(engine
  //   , new FontDescriptor(COURIER_FONT_FAMILY, SLANT_ROMAN, SETWIDTH_ANY,
  //   14, SPACING_MONOSPACED, 75, 75));
  // ASSERT(font->initialize(256));

  /* 4. Create sprite object, border object and FPS label */
  Texture *grass1 = TextureTool::loadFromFile(engine, "../../data/dirt1.png");
  Texture *grass2 = TextureTool::loadFromFile(engine, "../../data/dry_grass.png");
  Texture *grass3 = TextureTool::loadFromFile(engine, "../../data/grass_mossy.png");
  Texture *grassMap = TextureTool::loadFromFile(engine, "../../data/splatting_map.png");

  Sprite *sprite = new Sprite(engine);
  CHECK_POINTER(sprite);

  TexturesState texturesState;
  TextureSampler sampler;
  sampler.sTexture = REPEAT;
  sampler.tTexture = REPEAT;

  texturesState.slots[0] = grass1;
  texturesState.samplers[0] = sampler;
  texturesState.slots[1] = grass2;
  texturesState.samplers[1] = sampler;
  texturesState.slots[2] = grass3;
  texturesState.samplers[2] = sampler;
  texturesState.slots[3] = grassMap;
  texturesState.samplers[3] = sampler;

  float w = (winWidth * 0.8f) / grass1->getDesc().width;
  float h = (winHeight * 0.8f) / grass1->getDesc().height;

  sprite->setTexturesState(texturesState);
  sprite->setTexCoords(0, Vector2f(0, 0));
  sprite->setTexCoords(1, Vector2f(w, 0));
  sprite->setTexCoords(2, Vector2f(w, h));
  sprite->setTexCoords(3, Vector2f(0, h));

  UI *gui = new UI(engine);
  // Label *fpsLabel = gui->createLabel(gui->getActiveDesktop(), L"", WHITE);
  // fpsLabel->setFont(font);
  Border *border = gui->createBorder(gui->getActiveDesktop());

  /* Set sprite parameters */
  sprite->setSize(winWidth * 0.8f, winHeight * 0.8f);

  /* Set border parameters */
  border->setSize(winWidth * 0.8f, winHeight * 0.8f);

  /* Create shaders for splatting */
  Shader *vShader = engine->createVertexShader();
  ASSERT(vShader->load("../../data/splatting.vsh", true, SCF_LOG_ERRORS));

  Shader *pShader = engine->createPixelShader();
  ASSERT(pShader->load("../../data/splatting.fsh", true, SCF_LOG_ERRORS));

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

    /* Set positions and render with shaders */
    border->setPosition(Vector3f(winWidth * .1f, winHeight * .1f, 0.4f));
    sprite->setPosition(Vector3f(winWidth * .1f, winHeight * .1f, 0.4f));

    stateManager->pushStates(SHADERS_STATE);
    ASSERT(stateManager->setShadersState(ShadersState(program)));
    ASSERT(program->setTexture("grass1", 0));
    ASSERT(program->setTexture("grass2", 1));
    ASSERT(program->setTexture("grass3", 2));
    ASSERT(program->setTexture("map", 3));
    ASSERT(program->setFloat("w_scale", w));
    ASSERT(program->setFloat("h_scale", h));
    ASSERT(sprite->render());
    stateManager->popStates(SHADERS_STATE);

    /* Compute FPS (average value for 5 seconds) */
    // fpsLabel->setText(L"FPS: " + StringTool::floatToStr(win->getFPS(), 2));

    ASSERT(gui->render());

    /* Swap frame and back buffers */
    win->swap();
  }

  delete engine;
  delete xwin;

  return 0;
}
