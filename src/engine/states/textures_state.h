// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_TEXTURES_STATE_H__
#define __VE_TEXTURES_STATE_H__

#include <memory.h>
#include "engine/textures/texture.h"

namespace ve {
class Texture;

const int SLOTS_IN_TEXTURE_STATE = 8;

/**
  GPUState item that contains data to set into texture slots. NULL value in some slot means that
  this slot won't be set.
*/
struct TexturesState {
  Texture* slots[SLOTS_IN_TEXTURE_STATE];
  TextureSampler samplers[SLOTS_IN_TEXTURE_STATE];
  TextureEnvMode texEnv[SLOTS_IN_TEXTURE_STATE];

  /**
    Default constructor. Set all the slots to NULL.
  */
  TexturesState() {
    memset(slots, 0, sizeof(slots));
    memset(&samplers, 0, sizeof(samplers));
    memset(&texEnv, 0, sizeof(texEnv));
  }

  /**
    Sets the texture to the first slot and all the rest slots are NULL.
  */
  TexturesState(Texture *texture) {
    memset(slots, 0, sizeof(slots));

    slots[0] = texture;
  }

  /**
    Sets the texture and its texture environment to the first slot and all the rest slots are NULL.
  */
  TexturesState(Texture *texture, TextureEnvMode envMode) {
    memset(slots, 0, sizeof(slots));

    slots[0] = texture;
    texEnv[0] = envMode;
  }

  /**
    Sets the texture and its sampler to the first slot and all the rest slots are NULL.
  */
  TexturesState(Texture *texture, TextureSampler sampler) {
    memset(slots, 0, sizeof(slots));

    slots[0] = texture;
    samplers[0] = sampler;
  }
};

}

#endif // __VE_TEXTURES_STATE_H__
