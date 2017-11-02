// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "common.h"
#include "ext/vsync_ext.h"

namespace ve {

/**
    Do nothing.
    @param engine - pointer to GLEngine object which wants to initialize
    extension.
    @return OK everytime.
*/
Outcome VSyncExt::initialize(GLEngine *engine) {
  return OK;
}

/**
    Waits for vertical synchronization.
    @return 0 if functions succeeded.
*/
int VSyncExt::waitForVSync() {
  return 0;
}

/**
    Enables VSync.
*/
void VSyncExt::enableVSync() {
  // Do nothing
}

/**
    Disables VSync.
*/
void VSyncExt::disableVSync() {
  // Do nothing
}

}
