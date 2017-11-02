// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_VSYNC_IMPL_H__
#define __VE_VSYNC_IMPL_H__

#include "engine/ext/vsync_ext.h"

namespace ve {

class VSyncImpl : public VSyncExt {
private:
#ifdef VE_LINUX
  typedef int (APIENTRYP PFNGLXGETVIDEOSYNCSGI) (uint* counter);
  typedef int (APIENTRYP PFNGLXWAITVIDEOSYNCSGI) (int delimiter, int remainder, uint* counter);
  typedef int (APIENTRYP PFNGLXSWAPINTERVALSGI) (int interval);

  PFNGLXGETVIDEOSYNCSGI _glXGetVideoSyncSGI;
  PFNGLXWAITVIDEOSYNCSGI _glXWaitVideoSyncSGI;
  PFNGLXSWAPINTERVALSGI _glXSwapIntervalSGI;
#endif

#ifdef VE_WINDOWS
  PFNWGLSWAPINTERVALEXTPROC _wglSwapInterval;
#endif

public:

  /**
      Loads extension functions using GetProcAddress function of specified GLEngine object.
      @param engine - pointer to GLEngine object which wants to initialize
      extension.
      @return OK if all the functions were loaded correctly.
      @return NULL_POINTER if at least one function was not loaded successfully.
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

#endif // __VE_VSYNC_IMPL_H__
