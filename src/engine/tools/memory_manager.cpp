// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "common.h"
#include "tools/memory_manager.h"

namespace ve {
MemoryManager *MemoryManager::instance = NULL;

/**
  Returns instance of this singleton class.
  @return Instance of MemoryManager class.
*/
MemoryManager* MemoryManager::getInstance() {
  if (instance == NULL) {
    instance = new MemoryManager();
  }

  return instance;
}

MemoryManager::MemoryManager() {
}

MemoryManager::~MemoryManager() {
  free();
}

void MemoryManager::registerPointer(void *newPointer) {
  allocatedObjects.push_back(newPointer);
}

void MemoryManager::unregisterPointer(void *newPointer) {
  uint len = allocatedObjects.size();
  int found = -1;

  for (uint i = 0; i < len; i++) {
    if (allocatedObjects[i] == newPointer) {
      found = i;
      break;
    }
  }

  if (found != -1) {
    allocatedObjects.erase(allocatedObjects.begin() + found);
  } else {
    LOG_ERROR(L"Strange pointer to unregister");
  }
}

void MemoryManager::free() {
  while (!allocatedObjects.empty()) {
    delete allocatedObjects[0];
  }

  allocatedObjects.clear();
}

}
