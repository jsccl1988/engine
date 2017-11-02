// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "engine/windows/window_system_factory.h"
#include "engine/engines/gl_engine.h"
#include "engine/cameras/ortho_camera.h"
#include "engine/loaders/tga_loader.h"
#include "engine/tools/timer_factory.h"

/* Here we define window properties */
const int winX = 0;
const int winY = 0;
const int winWidth = 300;
const int winHeight = 300;

/* Frame size for sprite animation */
const int frameWidth = 41;
const int frameHeight = 72;

/* Sprite size */
const int spriteWidth = 80;
const int spriteHeight = 140;
const int spriteSpeed = 100;

using namespace ve;

/* Key objects of the application */
WindowSystem  *xwin = NULL;
ve::Window    *win = NULL;
Engine        *engine = NULL;

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

  /* 5. Create loader for TGA format and load texture */
  TGALoader *loader = new TGALoader();
  CHECK_RESULT(loader->loadFromFile(std::string("../../data/sprites.tga")), L"Loading failed");
  ASSERT(loader->applyColorKey(255, 255, 255));
  Texture *tex = loader->createTexture(engine);

  /* Set Linear filtering to avoid interpolation artefacts */
  TexturesState texState(tex, TextureSampler(NEAREST, NEAREST));

  /* Create font for label */
  ve::Font *font = NULL;
  font = xwin->createFont(engine, new FontDescriptor(COURIER_FONT_FAMILY, SLANT_ROMAN, SETWIDTH_ANY,
    14, SPACING_MONOSPACED, 75, 75));
  ASSERT(font->initialize(256));

  /* 6. Create animatied sprite with four animations */
  MovableSprite* walkingGuy = new MovableSprite(engine, spriteSpeed);
  walkingGuy->setAnimationListsCount(4);

  /* Compute frame size in texture coordinates */
  float du = frameWidth;
  float dv = frameHeight;

  /* Generate frames */
  for (int i = 0; i < 4; i++) {
    walkingGuy->genQuadFrames(i, Vector2f(0, tex->getDesc().height - (i + 1) * dv), Vector2f(du, dv), Vector2f(du, 0), 4);
  }

  /* Set sprite parameters */
  walkingGuy->setTexturesState(texState);
  walkingGuy->setAnimation(0);
  walkingGuy->setCurrentFrame(0);
  walkingGuy->setFPS(15);
  walkingGuy->setPosition(Vector3f((winWidth - spriteWidth) / 2, (winHeight - spriteHeight) / 2, 0.5));
  walkingGuy->setSize(spriteWidth, spriteHeight);
  walkingGuy->setAlphaTestState(AlphaTestState(true, GREATER, 0));

  /* Create interface and label to show FPS counter */
  UI *gui = new UI(engine);
  Label *fpsLabel = gui->createLabel(gui->getActiveDesktop(), L"", WHITE);
  fpsLabel->setFont(font);
  Label *hint = gui->createLabel(gui->getActiveDesktop(), L"Use arrows to animate sprite", WHITE);
  hint->setFont(font);
  hint->setPosition(0, 20, 0.5);

  bool finish = false;
  ve::uint move = 0;
  Vector3f direction;

  /* Use Timer class for time measurements */
  Timer* timer = TimerFactory::createTimer();
  timer->reset();

  while (!finish) {
    while (win->hasAvailableEvent()) {
      SystemEvent *ev = win->getNextEvent();
      if (ev != NULL) {
        KeyEvent *ke;
        int code;
        int curAnimation = walkingGuy->getAnimation();

        switch (ev->getType()) {
        case WINDOW_CLOSE:
          finish = true;
          break;

        case KEY_PRESS:
          ke = (KeyEvent*)ev;

          switch (ke->getKeyCode()) {
          case KEY_LEFT:
            if (curAnimation != 1) {
              walkingGuy->setAnimation(1);
              direction.set(-1, 0, 0);
            }

            move = 1;
            break;

          case KEY_RIGHT:
            if (curAnimation != 2) {
              walkingGuy->setAnimation(2);
              direction.set(1, 0, 0);
            }

            move = 1;
            break;

          case KEY_DOWN:
            if (curAnimation != 0) {
              walkingGuy->setAnimation(0);
              direction.set(0, 1, 0);
            }

            move = 1;
            break;

          case KEY_UP:
            if (curAnimation != 3) {
              walkingGuy->setAnimation(3);
              direction.set(0, -1, 0);
            }

            move = 1;
            break;

          default:
            break;
          }
          break;

        case KEY_RELEASE:
          ke = (KeyEvent*)ev;
          code = ke->getKeyCode();

          if (code == KEY_LEFT || code == KEY_RIGHT ||
            code == KEY_DOWN || code == KEY_UP) {
            move = 0;
          }
          break;

        default:
          break;
        }
      }
    }

    /* Clear back buffer color & depth buffer */
    ASSERT(engine->clear(ClearFlag(COLOR | DEPTH)));
    if (timer->getElapsedTime() > 0) {
      walkingGuy->move(move * timer->getElapsedTime(), move * direction);
      timer->reset();
    }
    ASSERT(walkingGuy->render());
    ASSERT(gui->render());

    /* Compute FPS (average value for 5 seconds) */
    fpsLabel->setText(L"FPS: " + StringTool::floatToStr(win->getFPS(), 2));

    /* Swap frame and back buffers */
    win->swap();
  }

  delete timer;
  delete engine;
  delete xwin;

  return 0;
}

