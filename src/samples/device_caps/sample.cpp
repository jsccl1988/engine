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
const int winWidth = 450;
const int winHeight = 300;

/* Key objects of the application */
WindowSystem  *xwin = NULL;
ve::Window    *win = NULL;
GLEngine      *engine = NULL;

int main() {
  /* The first class to be created */
  /* Create window system class. It is key point to access window functions */
  xwin = WindowSystemFactory::createWindowSystem();

  /* Now, you can create window defining caption, position ans size */
  CHECK_POINTER(win = xwin->createWindow(L"Device Caps Sample", winX, winY, winWidth, winHeight));
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

  font = xwin->createFont(engine
    , new FontDescriptor(COURIER_FONT_FAMILY, SLANT_ROMAN, SETWIDTH_ANY
    , 14, SPACING_MONOSPACED, 75, 75));

  CHECK_POINTER(font);
  CHECK_RESULT(font->initialize(256), L"Font initializtion failed");

  /* Get active desktop */
  Desktop *mainDesktop = gui->getActiveDesktop();

  /* Create label to show FPS */
  Label *fpsLabel = gui->createLabel(mainDesktop, L"FPS: -", WHITE);
  fpsLabel->setFont(font);
  fpsLabel->setPosition(Vector3f(0, 0, 0.3f));

  /* Create labels to show GPU-specific information */
  GLDeviceCaps *devCaps = (GLDeviceCaps*)engine->getDeviceCaps();
  std::wstring tmpStr = L"";
  Label *label1;
  Label *label2;
  std::vector< std::pair<Label*, Label*> > list;

  /* Texture slots */
  label1 = gui->createLabel(mainDesktop, L"Texture slots", WHITE);
  label2 = gui->createLabel(mainDesktop
    , L"[" + StringTool::intToStr(devCaps->getTextureSlotsCount()) + L"]"
    , GREEN);
  list.push_back(make_pair(label1, label2));

  /* Anisotropy */
  label1 = gui->createLabel(mainDesktop, L"Anisotropy", WHITE);
  if (devCaps->isAnisotropySupported()) {
    label2 = gui->createLabel(mainDesktop
      , L"[" + StringTool::floatToStr(devCaps->getMaxAnisotropy(), 2) + L"x]"
      , GREEN);
  } else {
    label2 = gui->createLabel(mainDesktop
      , L"[NO]"
      , RED);
  }
  list.push_back(make_pair(label1, label2));

  /* Color Attachments */
  label1 = gui->createLabel(mainDesktop, L"Color Attachments", WHITE);
  label2 = gui->createLabel(mainDesktop
    , L"[" + StringTool::intToStr(devCaps->getMaxColorAttachments()) + L"]"
    , GREEN);
  list.push_back(make_pair(label1, label2));

  /* VSync */
  label1 = gui->createLabel(mainDesktop, L"VSync", WHITE);
  if (devCaps->isVSyncSupported()) {
    label2 = gui->createLabel(mainDesktop, L"[OK]", GREEN);
  } else {
    label2 = gui->createLabel(mainDesktop, L"[NO]", RED);
  }
  list.push_back(make_pair(label1, label2));

  /* Frame buffer objects */
  label1 = gui->createLabel(mainDesktop, L"Frame Buffers", WHITE);
  if (devCaps->isFBOSupported()) {
    label2 = gui->createLabel(mainDesktop, L"[OK]", GREEN);
  } else {
    label2 = gui->createLabel(mainDesktop, L"[NO]", RED);
  }
  list.push_back(make_pair(label1, label2));

  /* GLSL */
  label1 = gui->createLabel(mainDesktop, L"GLSL", WHITE);
  if (devCaps->isGLSLSupported()) {
    label2 = gui->createLabel(mainDesktop, L"[OK]", GREEN);
  } else {
    label2 = gui->createLabel(mainDesktop, L"[NO]", RED);
  }
  list.push_back(make_pair(label1, label2));

  /* MipMaps */
  label1 = gui->createLabel(mainDesktop, L"MipMap Generation", WHITE);
  if (devCaps->isMipMapsSupported()) {
    label2 = gui->createLabel(mainDesktop, L"[OK]", GREEN);
  } else {
    label2 = gui->createLabel(mainDesktop, L"[NO]", RED);
  }
  list.push_back(make_pair(label1, label2));

  /* Multitexturing */
  label1 = gui->createLabel(mainDesktop, L"Multitexturing", WHITE);
  if (devCaps->isMultiTextureSupported()) {
    label2 = gui->createLabel(mainDesktop, L"[OK]", GREEN);
  } else {
    label2 = gui->createLabel(mainDesktop, L"[NO]", RED);
  }
  list.push_back(make_pair(label1, label2));

  /* Video Buffer Objects */
  label1 = gui->createLabel(mainDesktop, L"Video Buffers", WHITE);
  if (devCaps->isVBOSupported()) {
    label2 = gui->createLabel(mainDesktop, L"[OK]", GREEN);
  } else {
    label2 = gui->createLabel(mainDesktop, L"[NO]", RED);
  }
  list.push_back(make_pair(label1, label2));

  /* Set font and position */
  for (ve::uint i = 0; i < list.size(); i++) {
    list[i].first->setFont(font);
    list[i].first->setPosition(0.0f, (i + 1) * 20.0f, 0.3f);

    list[i].second->setFont(font);
    list[i].second->setPosition(300.0f, (i + 1) * 20.0f, 0.3f);
  }

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
