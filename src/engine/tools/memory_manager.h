// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_MEMORY_MANAGER_H__
#define __VE_MEMORY_MANAGER_H__

#include <vector>

namespace ve {

#define REGISTER_POINTER(x) MemoryManager::getInstance()->registerPointer(x);
#define UNREGISTER_POINTER(x) MemoryManager::getInstance()->unregisterPointer(x);

/**
    Memory manager is a very simple class to control
    allocated memory. This class is collection of pointers
    which should be disposed in destructor or free() function.
    Usually it used in classes which are able
    to allocate numerous objects with different types.
*/
class MemoryManager {
protected:
  /** The only one instance of this class */
  static MemoryManager *instance;

  /** List of allocated objects */
  std::vector<void*> allocatedObjects;

  /**
    Private constructor. Does nothing.
  */
  MemoryManager();

  /**
    Private copy-constructor.
  */
  MemoryManager(MemoryManager &ref);

  /**
    Private operator =
  */
  MemoryManager operator = (MemoryManager &ref);

public:
  /**
    Returns instance of this singleton class.
    @return Instance of MemoryManager class.
  */
  static MemoryManager* getInstance();

  /**
      MemoryManager destructor. Free all the objects it contains.
  */
  virtual ~MemoryManager();

  /**
      Register pointer to free in destructor or free() function.
      @param newPointer - pointer which should be released by this Manager.
  */
  virtual void registerPointer(void *newPointer);

  /**
      Unregister pointer. It means that this pointer will not be disposed
      during destructor or free() function.
  */
  virtual void unregisterPointer(void *newPointer);

  /**
      Free all the pointers it owns.
  */
  virtual void free();
};

}

#endif // __VE_MEMORY_MANAGER_H__
