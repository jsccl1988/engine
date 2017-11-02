// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "shaders/shaders.h"
#include "engines/engine.h"

namespace ve {

Shader::Shader(Engine* engine, Handle handle) {
  this->engine = engine;
  this->handle = handle;
}

Shader::~Shader() {
  engine->freeShader(this);
}

Handle Shader::getHandle() {
  return handle;
}

Outcome Shader::load(std::string fileName, bool needToCompile, ShaderCompilationFlag flags) {
  std::vector<GLchar> data;

  FILE* sFile = fopen(fileName.c_str(), "rb");
  CHECK_POINTER(sFile);

  char buf[1024];
  while (!feof(sFile)) {
    int readBytes = fread(buf, 1, sizeof(buf), sFile);
    for (int i = 0; i < readBytes; i++) {
      data.push_back(buf[i]);
    }
  }
  fclose(sFile);

  data.push_back(0); // To get NULL-terminated string from vector
  CHECK_RESULT(engine->loadShaderSource(this, (char*)&data[0]), L"Load source failed");

  if (needToCompile) {
    ASSERT(compile(flags));
  }

  return OK;
}

Outcome Shader::compile(ShaderCompilationFlag flags) {
  ASSERT(engine->compileShader(this));

  /* Check if there is a need to check compilation */
  if (flags & SCF_CHECK_ERRORS) {
    Outcome result = isCompiled();

    /* Check if there is a need to place errors in log file */
    if (result != OK && (flags & SCF_LOG_ERRORS)) {
      LOG_ERROR(StringTool::AsciiToWide(getCompileLog()));
    }

    return result;
  }

  return OK;
}

Outcome Shader::isCompiled() {
  ASSERT(engine->isShaderCompiled(this));
  return OK;
}

char* Shader::getCompileLog() {
  return engine->getShaderLog(this);
}

}
