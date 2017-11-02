// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "shaders/program.h"
#include "engines/engine.h"

namespace ve {

Program::Program(Engine* engine, Handle handle) {
  this->engine = engine;
  this->handle = handle;
}

Program::~Program() {
  engine->freeProgram(this);
}

Handle Program::getHandle() {
  return handle;
}

Outcome Program::setVertexShader(Shader *shader) {
  ASSERT(engine->setProgramVertexShader(this, shader));
  return OK;
}

Outcome Program::setPixelShader(Shader *shader) {
  ASSERT(engine->setProgramPixelShader(this, shader));
  return OK;
}

Outcome Program::link(ShaderCompilationFlag flags) {
  ASSERT(engine->linkProgram(this));

  /* Check if there is a need to check compilation */
  if (flags & SCF_CHECK_ERRORS) {
    Outcome result = isLinked();

    /* Check if there is a need to place errors in log file */
    if (result != OK && (flags & SCF_LOG_ERRORS)) {
      LOG_ERROR(StringTool::AsciiToWide(getLinkLog()));
    }

    return result;
  }

  return OK;
}

Outcome Program::isLinked() {
  ASSERT(engine->isProgramLinked(this));
  return OK;
}

char* Program::getLinkLog() {
  return engine->getProgramLinkLog(this);
}

Outcome Program::setFloat(string param, float value) {
  ASSERT(engine->setProgramFloat(this, param, value));
  return OK;
}

Outcome Program::getFloat(string param, float *value) {
  ASSERT(engine->getProgramFloat(this, param, value));
  return OK;
}

Outcome Program::setVector(string param, const Vector2f &value) {
  ASSERT(engine->setProgramVector(this, param, value));
  return OK;
}

Outcome Program::setVector(string param, const Vector3f &value) {
  ASSERT(engine->setProgramVector(this, param, value));
  return OK;
}

Outcome Program::setVector(string param, const Vector4f &value) {
  ASSERT(engine->setProgramVector(this, param, value));
  return OK;
}

Outcome Program::setTexture(string param, int texture) {
  ASSERT(engine->setProgramTexture(this, param, texture));
  return OK;
}

Outcome Program::setInt(string param, int value) {
  ASSERT(engine->setProgramInt(this, param, value));
  return OK;
}

}
