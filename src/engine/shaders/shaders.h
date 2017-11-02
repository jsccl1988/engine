// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_SHADER_H__
#define __VE_SHADER_H__

#include "engine/common.h"
#include "engine/math/vector2f.h"
#include "engine/math/vector3f.h"
#include "engine/math/vector4f.h"

/** @file eeShader.h */

namespace ve {

/**
    Defines additional actions for shader compilation and program linking process.
*/
enum ShaderCompilationFlag {
  SCF_NOTHING = 0,
  SCF_CHECK_ERRORS = 1,
  SCF_LOG_ERRORS = SCF_CHECK_ERRORS | 2,
};

class Engine;

/**
    Abstract class which represents shaders functionality
    in VR Engine library. Shaders are mean to
    use GPU computing resources instead of CPU's. Redistribution
    of computing resources to GPU side and calculation on shaders
    is a good way to improve performance of application.

    <b>Note</b>: Should be created only using Engine::createVertexShader() or
    Engine::createPixelShader() functions.

    @note Following extensions must be supported by GPU to create
    Shader objects:
    <ul>
    <li>GL_ARB_shading_language_100</li>
    <li>GL_ARB_shader_objects</li>
    <li>GL_ARB_vertex_shader</li>
    <li>GL_ARB_fragment_shader</li>
    </ul>
    Use 'glxinfo' command to check support.
*/
class Shader {
private:
  /** Used in Engine classes to contain shader instance specific informnation. */
  Handle handle;

protected:
  /** Reference to engine which created this shader */
  Engine *engine;

public:
  /**
      Shader constructor. It is used only by Engine classes.
      Create shader instances only through invocation of
      createVertexShader and createPixelShader.
      @see Engine::createVertexShader()
      @see Engine::createPixelShader()
  */
  Shader(Engine* engine, Handle handle);

  /**
      Shader destructors. Calls engine's function freeShader() to
      free allocated memory resources.
      @see Engine::freeShader()
  */
  virtual ~Shader();

  /**
      This function returns handle specific to a shader instance.
      Handle is used to store instance specific information in
      the Engine class.
      @return instance specific handle.
  */
  Handle getHandle();

  /**
      Loads shader which is written in GLSL language.
      There is no compilation in this function if needToCompile flag is 'false' and
      if needToCompile is 'true' then compilation occurred right after loading.
      @param fileName - file to load shader source form.
      @param needToCimpile - flag which defines if compilation should be done
      in this function.
      @param flags - Flags which will be used for compilation process.
      @return OK in case if shader code loaded from file.
      @return NULL_POINTER if file was not found.
      @return ERROR in case of common error.
      @see compile()
  */
  virtual Outcome load(std::string fileName, bool needToCompile = false,
    ShaderCompilationFlag flags = SCF_NOTHING);

  /**
      Compiles shader.
      @param flags - Shader compilation flag which defines which actions also should be done after
      compilation. Possible flags:
      <ul>
      <li>SCF_CHECK_ERRORS flag defines that compilation success will be checked, i.e. if compilation
      errors were found. </li>
      <li>SCF_LOG_ERRORS flag implicitly includes SCF_CHECK_ERRORS flag. If this flag is set and
      compilation errors were found then they will placed at log file using LOG_ERROR macro. </li>
      </ul>
      If SCF_NOTHING is used as flags value then manual check of compilation is needed (isCompile() function).
      @return OK if no engine's error occurred during compilation.
      @return if flags is set to 0, ERROR is returned only in case of engine error.
      if SCF_CHECK_ERRORS flag is set, ERROR is also returned if compilation error was found.
      @see isCompiled()
  */
  virtual Outcome compile(ShaderCompilationFlag flags = SCF_LOG_ERRORS);

  /**
      Check if previous compile() call succeeded.
      @return OK if shader compilation succeded.
      @return ERROR if errors occurred (in engine or during compilation).
      Use getCompiledLog() function to get compilation log.
      @see getCompileLog()
  */
  virtual Outcome isCompiled();

  /**
      Returns compilation log.
      @return NULL-terminated string which contains compilation log.
      @return NULL if no log available.
  */
  virtual char* getCompileLog();
};

}

#endif // __VE_SHADER_H__
