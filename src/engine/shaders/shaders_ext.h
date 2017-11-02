// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_SHADERS_EXT_H__
#define __VE_SHADERS_EXT_H__

#include "engine/common.h"

namespace ve {

class GLEngine;

/**
    This class was produced to extend GLEngine's capabilities in
    shaders area. All the functions writes "Function
    is not implemented" in a log file. It contains only functions
    which were introduced in the following extensions:

    <ul>
    <li>GL_ARB_shading_language_100</li>
    <li>GL_ARB_shader_objects</li>
    <li>GL_ARB_vertex_shader</li>
    <li>GL_ARB_fragment_shader</li>
    </ul>

    GLEngine uses this class for all shader functions if shaders
    are not supported and ShadersImpl class in case of shaders support.
    During initialization GLEngine decides if it should create instance
    of this class or instance of ShadersImpl class. It depends on shaders
    support for GPU.

    This technique of extensions support will lead to safe calls even
    for functions which are not supported on GPU where executed.

    @see GLEngine::initialize()
    @see ShadersImpl
*/
class ShadersExt {
public:
  ShadersExt();
  virtual ~ShadersExt();
  virtual Outcome initialize(GLEngine *engine);
  virtual GLuint glCreateShader(GLenum type);
  virtual GLuint glCreateProgram();
  virtual void glAttachShader(GLuint programId, GLuint shaderId);
  virtual void glLinkProgram(GLuint programId);
  virtual void glGetObjectParameteriv(GLhandleARB programId, GLenum target, GLint *value);
  virtual void glUseProgram(GLuint programID);
  virtual void glShaderSource(GLuint shaderId, GLsizei size, const GLchar** source, const GLint *param); //TODO: Fix definition
  virtual void glCompileShader(GLuint shaderId);
  virtual void glDetachShader(GLuint programId, GLuint shaderId);
  virtual void glDeleteObject(GLhandleARB handle);
  virtual void glGetInfoLog(GLhandleARB programId, GLsizei size, GLsizei *written, GLcharARB *log);
  virtual GLint glGetUniformLocation(GLuint shaderId, const GLchar* name);
  virtual void glUniform1fv(GLint paramId, GLsizei size, const GLfloat *value);
  virtual void glUniform2fv(GLint paramId, GLsizei size, const GLfloat *value);
  virtual void glUniform3fv(GLint paramId, GLsizei size, const GLfloat *value);
  virtual void glUniform4fv(GLint paramId, GLsizei size, const GLfloat *value);
  virtual void glUniform4f(GLint paramId, float a, float b, float c, float d);
  virtual void glUniform1i(GLint paramId, GLint value);
  virtual void glGetUniformfv(GLuint shaderId, GLint paramId, GLfloat *values);
  virtual void glGetUniformiv(GLuint shaderId, GLint paramId, GLint *values);
};

}

#endif // __VE_SHADERS_EXT_H__
