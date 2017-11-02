// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_SHADERS_STATE_H__
#define __VE_SHADERS_STATE_H__

namespace ve {

class Program;

/**
  Defines shaders that should be bound to the pipeline during rendering.
*/
struct ShadersState {
  Program *program;

  /**
    Default constructor. Sets program to NULL, thus disables shaders.
  */
  ShadersState() {
    program = NULL;
  }

  ShadersState(Program *program) {
    this->program = program;
  }
};

}

#endif // __VE_SHADERS_STATE_H__