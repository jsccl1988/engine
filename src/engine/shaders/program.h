// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_PROGRAM_H__
#define __VE_PROGRAM_H__

#include "engine/shaders/shaders.h"

namespace ve {

class Engine;

/**
    Class which represent pair of vertex and pixel shaders.
    It is used to link vertex and fragment shaders and then it
    may be bound to graphics pipeline by calling of bind()
    function.

    Note: It should be created only through call to createProgram()
    function of Engine class.
    @see Engine::createProgram()
    @see bind()
*/
class Program {
private:
  /** Used by Engine classes to store instance specific information */
  Handle handle;

protected:
  /** Used as reference to engine which created this program */
  Engine *engine;

public:
  /**
      Constructor for program. It is used only by Engine classes.
      Use createProgram() function of Engine classes to create object.
      @see Engine::createProgram()
  */
  Program(Engine *engine, Handle handle);

  /**
      Destructor for program. It calls freeProgram() function of Engine
      class which created it to free allocated resources.
  */
  virtual ~Program();

  /**
      Sets vertex shader for this program.
      @param shader - pointer to vertex shader which should
      be attached to this program.
      @return OK if function succeeded.
      @return NULL_POINTER if shader pointer in NULL
      @return ERROR if OpenGL functions failed for some reason.
      In this case check log file to understand a problem.
  */
  virtual Outcome setVertexShader(Shader *shader);

  /**
      Sets pixel shader for this program.
      @param shader - pointer to pixel shader which should
      be attached to this program.
      @return OK if function succeeded.
      @return NULL_POINTER if shader pointer in NULL
      @return ERROR if OpenGL functions failed for some reason.
      In this case check log file to understand a problem.
  */
  virtual Outcome setPixelShader(Shader *shader);

  /**
      Links program using vertex shader and pixel shader.
      @param flags - Shader compilation flag which defines which actions also should be done after
      linking. Possible flags:
      <ul>
      <li>SCF_CHECK_ERRORS flag defines that success of linking will be checked, i.e. if linker
      errors were found. </li>
      <li>SCF_LOG_ERRORS flag implicitly includes SCF_CHECK_ERRORS flag. If this flag is set and
      linker errors were found then they will placed at log file using LOG_ERROR macro. </li>
      </ul>
      If SCF_NOTHING is used as flags value then manual check of linking status is needed (isLinked() function).
      @return OK if no engine's error occurred during compilation.
      @return if flags is set to 0, ERROR is returned only in case of engine error.
      if SCF_CHECK_ERRORS flag is set, ERROR is also returned if linker error was found.
      @see isLinked()
  */
  virtual Outcome link(ShaderCompilationFlag flags = SCF_LOG_ERRORS);

  /**
      Checks linking status.
      @return OK if linking succeeded.
      @return ERROR in case of linking error or engine's error.
      Check log file or call getLinkLog() to clarify.
      @see getLinkLog()
  */
  virtual Outcome isLinked();

  /**
      Returns linking log.
      @return zero-terminated string which contains log file for linking process.
      @return NULL in case of engine's error.
  */
  virtual char* getLinkLog();

  /**
      Sets a uniform float4 value of shader.
      @param param - name of parameter in GLSL source code.
      @param value - value which should be stored in uniform variable.
      @return OK in case of success
      @return ERROR if parameter with given name was not found in GLSL code.
  */
  virtual Outcome setVector(std::string param, const Vector4f &value);

  /**
      Sets a uniform float3 value of shader.
      @param param - name of parameter in GLSL source code.
      @param value - value which should be stored in uniform variable.
      @return OK in case of success
      @return ERROR if parameter with given name was not found in GLSL code.
  */
  virtual Outcome setVector(std::string param, const Vector3f &value);

  /**
      Sets a uniform float2 value of shader.
      @param param - name of parameter in GLSL source code.
      @param value - value which should be stored in uniform variable.
      @return OK in case of success
      @return ERROR if parameter with given name was not found in GLSL code.
  */
  virtual Outcome setVector(std::string param, const Vector2f &value);

  /**
      Stores a given float value to a uniform variable.
      @param param - name of parameter in GLSL source code.
      @param value - value which should be stored in uniform variable.
      @return OK in case of success
      @return ERROR if parameter with given name was not found in GLSL code.
  */
  virtual Outcome setFloat(std::string param, float value);

  /**
      Stores a given int value to a uniform variable.
      @param param - name of parameter in GLSL source code.
      @param value - value which should be stored in uniform variable.
      @return OK in case of success
      @return ERROR if parameter with given name was not found in GLSL code.
  */
  virtual Outcome setInt(std::string param, int value);

  /**
      Gets a given float value to a uniform variable.
      @param param - name of parameter in GLSL source code.
      @param value - value which should be stored in uniform variable.
      @return OK in case of success
      @return ERROR if parameter with given name was not found in GLSL code.
  */
  virtual Outcome getFloat(std::string param, float *value);

  /**
      Set texture slot for GLSL sampler variable.
      @param param - name of parameter in GLSL source code.
      @param texture - slot which would be dound to sampler variable.
      @return OK in case of success
      @return ERROR if parameter with given name was not found in GLSL code.
  */
  virtual Outcome setTexture(std::string param, int texture);

  /**
      This function is used by Engine classes for managing program.
      instance specific data.
      @return Engine's internal handle for program object.
  */
  Handle getHandle();
};

}

#endif // __VE_PROGRAM_H__
