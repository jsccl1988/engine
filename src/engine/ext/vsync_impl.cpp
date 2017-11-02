// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "ext/vsync_impl.h"
#include "engines/gl_engine.h"

namespace ve {

/**
    Loads extension functions using GetProcAddress function of specified GLEngine object.
    @param engine - pointer to GLEngine object which wants to initialize
    extension.
    @return OK if all the functions were loaded correctly.
    @return NULL_POINTER if at least one function was not loaded successfully.
*/
Outcome VSyncImpl::initialize(GLEngine *engine) {
#ifdef VE_LINUX
  _glXGetVideoSyncSGI = (PFNGLXGETVIDEOSYNCSGI)engine->getProcAddress("glXGetVideoSyncSGI");
  CHECK_POINTER(_glXGetVideoSyncSGI);

  _glXWaitVideoSyncSGI = (PFNGLXWAITVIDEOSYNCSGI)engine->getProcAddress("glXWaitVideoSyncSGI");
  CHECK_POINTER(_glXWaitVideoSyncSGI);

  _glXSwapIntervalSGI = (PFNGLXSWAPINTERVALSGI)engine->getProcAddress("glXSwapIntervalSGI");
  CHECK_POINTER(_glXSwapIntervalSGI);
#endif // VE_LINUX

#ifdef VE_WINDOWS
  _wglSwapInterval = (PFNWGLSWAPINTERVALEXTPROC)engine->getProcAddress("wglSwapIntervalEXT");
#endif

  return OK;
}

/**
    Waits for vertical synchronization.
    @return 0 if functions succeeded.
*/
int VSyncImpl::waitForVSync() {
#ifdef VE_LINUX
  uint counter = 0;
  ERROR_IF(_glXGetVideoSyncSGI(&counter) != 0, L"glXGetVideoSyncSGI failed", -1);
  if (counter == 0 || counter == 1) {
    return 0;
  }
  return _glXWaitVideoSyncSGI(counter, (counter + 1) % 2, &counter);
#else 
  return 0;
#endif // VE_LINUX
}

/**
      Enables VSync.
  */
void VSyncImpl::enableVSync() {
#ifdef VE_LINUX
  ERROR_IF(_glXSwapIntervalSGI(1) != 0, L"glXSwapIntervalSGI failed", ;);
#endif // VE_LINUX
#ifdef VE_WINDOWS
  _wglSwapInterval(1);
#endif // VE_WINDOWS
}

/**
    Disables VSync.
*/
void VSyncImpl::disableVSync() {
#ifdef VE_LINUX
  ERROR_IF(_glXSwapIntervalSGI(0) != 0, L"glXSwapIntervalSGI failed", ;);
#endif // VE_LINUX
#ifdef VE_WINDOWS
  _wglSwapInterval(0);
#endif
}

}
