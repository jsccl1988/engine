// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "common.h"
#include "windows/window_system.h"
#include "windows/window.h"

//FIXME::
#include "engines/gl_engine.h"

namespace ve {

Window::Window(WindowSystem *windowSystem) {
  this->engine = windowSystem;
  time(&lastMoment);
  framesCount = 0;
  fps = 0;
}

Window::~Window() {
  engine->freeWindow(this);
}

/* General functions */
Outcome Window::show() {
  ASSERT(engine->show(this));
  return OK;
}

Outcome Window::swap() {
  time_t curMoment = 0;

  time(&curMoment);
  framesCount++;

  if (curMoment >= lastMoment + 2) {
    fps = framesCount / 2.0f;
    lastMoment = curMoment;
    framesCount = 0;
  }

  ASSERT(engine->swap(this));
  GLEngine::getInstance()->onSwapBuffers();
  return OK;
}

float Window::getFPS() {
  return fps;
}

/* Set functions */
Outcome Window::setCaption(std::wstring &newCaption) {
  ASSERT(engine->setCaption(this, newCaption));
  return OK;
}

Outcome Window::setPosition(double newX, double newY) {
  ASSERT(engine->setPosition(this, newX, newY));
  return OK;
}

Outcome Window::setWindowMode(WindowMode newMode) {
  ASSERT(engine->setMode(this, newMode));
  return OK;
}

Outcome Window::setWindowState(const WindowState newState) {
  ASSERT(engine->setState(this, newState));
  return OK;
}

Outcome Window::setWidth(double newWidth) {
  ASSERT(engine->setWidth(this, newWidth));
  return OK;
}

Outcome Window::setHeight(double newHeight) {
  ASSERT(engine->setHeight(this, newHeight));
  return OK;
}

Outcome Window::setSize(double newWidth, double newHeight) {
  ASSERT(engine->setSize(this, newWidth, newHeight));
  return OK;
}

int Window::getWidth() {
  UNIMPLEMENTED();
  return 0;
}

int Window::getHeight() {
  UNIMPLEMENTED();
  return 0;
}

/**
  Returns viewport of the window. Viewport contains whole area that is available
  for rendering.
  @return ViewportState object that contains bounds of client area.
*/
ViewportState Window::getClientViewport() {
  return engine->getClientViewport(this);
}

/**
    Returns the next window system event if there is any in the queue. If there are
    no events function blocks waits till next event happens.
    @return Window system event.
    @return NULL if event is not supported.
*/
SystemEvent* Window::getNextEvent() {
  return engine->getNextEvent(this);
}

/**
    Checks if there is an available event for this window.
    @return 'true' if there is an event for this window from the window system.
@return 'false' if there are no available events for this window.
*/
bool Window::hasAvailableEvent() {
  return engine->hasAvailableEvent(this);
}

}
