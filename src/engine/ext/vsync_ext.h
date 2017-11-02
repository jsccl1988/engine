// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_VSYNC_EXT_H__
#define __VE_VSYNC_EXT_H__

#include "engine/common.h"

namespace ve {

class GLEngine;

class VSyncExt {
public:

  /**
      Do nothing.
      @param engine - pointer to GLEngine object which wants to initialize
      extension.
      @return OK everytime.
  */
  virtual Outcome initialize(GLEngine *engine);

  /**
      Waits for vertical synchronization.
      @return 0 if functions succeeded.
  */
  virtual int waitForVSync();

  /**
      Enables VSync.
  */
  virtual void enableVSync();

  /**
      Disables VSync.
  */
  virtual void disableVSync();
};

}

#endif // __VE_VSYNC_EXT_H__
