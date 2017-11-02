// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_DEVICE_CAPS_H__
#define __VE_DEVICE_CAPS_H__

#include "engine/common.h"

namespace ve {
class Engine;

/**
    Provides access for device capabilities. Use this class to check
    support of different features and to retrieve GPU constants like
    number of texture slots and so on.
*/
class DeviceCaps {
protected:
  Engine *engine;

public:
  /**
      Default constructor. Does nothing.
  */
  DeviceCaps(Engine *engine);

  /**
      Checks if vertical synchronization is supported by GPU.
      @return 'true' if vertical synchronization is supported and
      'false' otherwise.
  */
  virtual bool isVSyncSupported() = 0;

  /**
      Checks if anisotropic filtration is supported by GPU.
      @return true if anisotropic filtration is supported by GPU.
      @return false if anisotropic filtration is not supported by GPU.
  */
  virtual bool isAnisotropySupported() = 0;

  /**
      Returns number of available texture slots on this GPU.
      @return Number of available texture slots on this GPU.
  */
  virtual int getTextureSlotsCount() = 0;

  /**
      Returns maximal number of color attachments that can
      be attached to a frame buffer.
  */
  virtual int getMaxColorAttachments() = 0;

  /**
      Returns max level of anisotropic filtration that is supported by GPU.
      @return Max level of anisotropic filtration that is supported by GPU.
  */
  virtual float getMaxAnisotropy() = 0;

};

}

#endif // __VE_DEVICE_CAPS_H__
