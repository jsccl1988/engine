// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "windows/thread_factory.h"

namespace ve {

struct ThreadInfo {
  ThreadEntry entry;
  void *parameter;

  ThreadInfo(ThreadEntry theEntry, void *theParameter) {
    entry = theEntry;
    parameter = theParameter;
  }
};

ThreadFactory* ThreadFactory::instance = NULL;

#ifdef VE_WINDOWS
unsigned long __stdcall win_entry(void *parameter) {
  ThreadInfo *info = (ThreadInfo*)parameter;
  unsigned long result = info->entry(info->parameter);
  delete info;
  return result;
}
#endif // VE_WINDOWS

#ifdef VE_LINUX
void* linux_entry(void *parameter) {
  ThreadInfo *info = (ThreadInfo*)parameter;
  unsigned long result = info->entry(info->parameter);
  delete info;
  return (void*)result;
}
#endif // VE_LINUX

ThreadFactory::ThreadFactory() {
}

ThreadFactory* ThreadFactory::getInstance() {
  if (instance == NULL) {
    instance = new ThreadFactory();
  }

  return instance;
}

Outcome ThreadFactory::spawn(ThreadEntry entry, void* parameter) {
#ifdef VE_WINDOWS
  HANDLE hr = CreateThread(NULL, 0, win_entry, new ThreadInfo(entry, parameter), 0, NULL);

  if (hr == NULL) {
    LOG_WIN_ERROR();
    return ERROR;
  }

  return OK;
#endif // VE_WINDOWS
#ifdef VE_LINUX
  pthread_t threadId;
  int thread = pthread_create(&threadId, NULL, linux_entry, new ThreadInfo(entry, parameter));

  if (thread != 0) {
    LOG_ERROR(L"pthead_create() failed with code: " + StringTool::intToStr(thread));
    return ERROR;
  }

  return OK;
#endif // VE_LINUX
}

}
