// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_BLEND_STATE_H__
#define __VE_BLEND_STATE_H__

#include "engine/common.h"

namespace ve {

/**
    Represents pipeline's blend state. It will be implemented
    as separate class in beta version of the library.
*/
struct BlendState {
  /**
      Specifies if blend stage is enabled.
  **/
  bool isEnabled;

  /**
      Blend stage operation for source fragment.
  */
  BlendFactor sourceFactor;

  /**
      Blend stage operation for destination fragment.
  */
  BlendFactor destFactor;

  /**
      Default constructor.
      Source operation: ONE
      Destination operation: ZERO
  */
  BlendState() {
    isEnabled = false;
    sourceFactor = ONE;
    destFactor = ZERO;
  }

  /**
      Extended constructor. Sets blend stage operations for source
      and destination.
      @param theSourceFactor - Blend stage operation applied to source fragment.
      @param theDestFactor - Blend stage operation applied to destination fragment.
  */
  BlendState(BlendFactor theSourceFactor, BlendFactor theDestFactor) {
    isEnabled = true;
    sourceFactor = theSourceFactor;
    destFactor = theDestFactor;
  }
};

}

#endif // __VE_BLEND_STATE_H__
