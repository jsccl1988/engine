// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "fonts/font.h"
#include "windows/window_system.h"
#include "fonts/font_cache.h"

namespace ve {

Font::Font(WindowSystem *owner, Engine *engine) {
  windowSystem = owner;
  this->engine = engine;
  cache = new FontCache();
}

Font::~Font() {
  delete cache;
  windowSystem->freeFont(this);
}

Outcome Font::initialize(uint cacheSize) {
  return cache->initialize(engine, this, cacheSize);
}

uint Font::getTextWidth(std::string s) {
  return windowSystem->getTextWidth(this, s);
}

uint Font::getTextWidth(std::wstring ws) {
  return windowSystem->getTextWidth(this, ws);
}

FontCache* Font::getCache() {
  return cache;
}

}
