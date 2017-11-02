// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "engine/windows/window_system_factory.h"
#include "engine/engines/gl_engine.h"
#include "engine/cameras/ortho_camera.h"
#include "engine/tools/texture_tool.h"

/* Here we define window properties */
const int winX = 0;
const int winY = 0;
const int winWidth = 512;
const int winHeight = 512;

/* Namespace of the engine */
using namespace ve;

/* Key objects of the application */
WindowSystem  *xwin = NULL;
ve::Window    *win = NULL;
GLEngine      *engine = NULL;

int main() {
  /* The first class to be created - Window System */
  /* It is a key point to access window functions  */
  xwin = WindowSystemFactory::createWindowSystem();

  /* Now, we can create window defining caption, position and its size */
  win = xwin->createWindow(L"NewWindow", winX, winY, winWidth, winHeight);
  xwin->show(win);

  /* And finally an engine could be created to use OpenGL renderer */
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

  /* 5. Load texture */
  Texture *tex = TextureTool::loadFromFile(engine, "../../data/chess_board.png");
  CHECK_POINTER(tex);

  /* Set texture sampler that is used for tiling: repeat texture coordinates when they exceed 1.0 */
  TexturesState texState;

  TextureSampler sampler;
  sampler.sTexture = REPEAT;
  sampler.tTexture = REPEAT;

  texState.slots[0] = tex;
  texState.samplers[0] = sampler;

  /* Create font for label */
  ve::Font *font = NULL;
  font = xwin->createFont(engine, new FontDescriptor(COURIER_FONT_FAMILY, SLANT_ROMAN, SETWIDTH_ANY,
    14, SPACING_MONOSPACED, 75, 75));
  ASSERT(font->initialize(256));

  /* 6. Create sprite object, border object and FPS label */
  Sprite *sprite = new Sprite(engine);
  UI *gui = new UI(engine);
  Label *fpsLabel = gui->createLabel(gui->getActiveDesktop(), L"", WHITE);
  fpsLabel->setFont(font);
  Border *border = gui->createBorder(gui->getActiveDesktop());

  /* Set sprite parameters */
  sprite->setTexturesState(texState);
  sprite->setPosition(Vector3f(winWidth / 4, winHeight / 4, 0.5));
  sprite->setSize(winWidth / 2, winHeight / 2);

  /* Compute number of tiles in the sprite */
  float tilesCountInWidth = (float)sprite->getWidth() / sprite->getTexture()->getDesc().width;
  float tilesCountInHeight = (float)sprite->getHeight() / sprite->getTexture()->getDesc().height;

  /* Set texture coordinates */
  sprite->setTexCoords(0, Vector2f(0, 0));
  sprite->setTexCoords(1, Vector2f(tilesCountInWidth, 0));
  sprite->setTexCoords(2, Vector2f(tilesCountInWidth, tilesCountInHeight));
  sprite->setTexCoords(3, Vector2f(0, tilesCountInHeight));

  /* Set border parameters */
  border->setPosition(Vector3f(winWidth / 4.f, winHeight / 4.f, 0.4f));
  border->setSize(winWidth / 2, winHeight / 2);

  bool finish = false;
  while (!finish) {
    /* Loop that waits for WINDOW_CLOSE message to finish processing */
    while (win->hasAvailableEvent()) {
      SystemEvent *ev = win->getNextEvent();
      if (ev != NULL && ev->getType() == WINDOW_CLOSE) {
        finish = true;
      }
    }

    /* Clear back buffer color & depth buffer */
    ASSERT(engine->clear(ClearFlag(COLOR | DEPTH)));

    /* Render sprite */
    ASSERT(sprite->render());

    /* Render label */
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

