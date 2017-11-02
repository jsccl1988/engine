// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "shaders/shaders_impl.h"
#include "engines/gl_engine.h"

namespace ve {
ShadersImpl::ShadersImpl() {
}

ShadersImpl::~ShadersImpl() {
}

Outcome ShadersImpl::initialize(GLEngine *engine) {
  CHECK_POINTER(_glCreateShader = (PFNGLCREATESHADERPROC)engine->getProcAddress("glCreateShaderObjectARB"));
  CHECK_POINTER(_glCreateProgram = (PFNGLCREATEPROGRAMPROC)engine->getProcAddress("glCreateProgramObjectARB"));
  CHECK_POINTER(_glAttachShader = (PFNGLATTACHSHADERPROC)engine->getProcAddress("glAttachObjectARB"));
  CHECK_POINTER(_glLinkProgram = (PFNGLLINKPROGRAMPROC)engine->getProcAddress("glLinkProgramARB"));
  CHECK_POINTER(_glGetObjectParameteriv = (PFNGLGETOBJECTPARAMETERIVARBPROC)engine->getProcAddress("glGetObjectParameterivARB"));
  CHECK_POINTER(_glUseProgram = (PFNGLUSEPROGRAMPROC)engine->getProcAddress("glUseProgramObjectARB"));
  CHECK_POINTER(_glShaderSource = (PFNGLSHADERSOURCEARBPROC)engine->getProcAddress("glShaderSourceARB"));
  CHECK_POINTER(_glCompileShader = (PFNGLCOMPILESHADERARBPROC)engine->getProcAddress("glCompileShaderARB"));
  CHECK_POINTER(_glDetachShader = (PFNGLDETACHSHADERPROC)engine->getProcAddress("glDetachObjectARB"));
  CHECK_POINTER(_glDeleteObject = (PFNGLDELETEOBJECTARBPROC)engine->getProcAddress("glDeleteObjectARB"));
  CHECK_POINTER(_glGetInfoLog = (PFNGLGETINFOLOGARBPROC)engine->getProcAddress("glGetInfoLogARB"));
  CHECK_POINTER(_glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONARBPROC)engine->getProcAddress("glGetUniformLocationARB"));
  CHECK_POINTER(_glUniform1fv = (PFNGLUNIFORM1FVARBPROC)engine->getProcAddress("glUniform1fvARB"));
  CHECK_POINTER(_glUniform2fv = (PFNGLUNIFORM2FVARBPROC)engine->getProcAddress("glUniform2fvARB"));
  CHECK_POINTER(_glUniform3fv = (PFNGLUNIFORM3FVARBPROC)engine->getProcAddress("glUniform3fvARB"));
  CHECK_POINTER(_glUniform4fv = (PFNGLUNIFORM4FVARBPROC)engine->getProcAddress("glUniform4fvARB"));
  CHECK_POINTER(_glUniform4f = (PFNGLUNIFORM4FARBPROC)engine->getProcAddress("glUniform4fARB"));
  CHECK_POINTER(_glUniform1i = (PFNGLUNIFORM1IARBPROC)engine->getProcAddress("glUniform1iARB"));
  CHECK_POINTER(_glGetUniformfv = (PFNGLGETUNIFORMFVARBPROC)engine->getProcAddress("glGetUniformfvARB"));
  CHECK_POINTER(_glGetUniformiv = (PFNGLGETUNIFORMIVARBPROC)engine->getProcAddress("glGetUniformivARB"));
  return OK;
}

GLuint ShadersImpl::glCreateShader(GLenum type) {
  return _glCreateShader(type);
}

GLuint ShadersImpl::glCreateProgram() {
  return _glCreateProgram();
}

void ShadersImpl::glAttachShader(GLuint programId, GLuint shaderId) {
  _glAttachShader(programId, shaderId);
}

void ShadersImpl::glLinkProgram(GLuint programId) {
  _glLinkProgram(programId);
}

void ShadersImpl::glGetObjectParameteriv(GLhandleARB programId, GLenum target, GLint *value) {
  _glGetObjectParameteriv(programId, target, value);
}

void ShadersImpl::glUseProgram(GLuint programId) {
  _glUseProgram(programId);
}

void ShadersImpl::glShaderSource(GLuint shaderId, GLsizei size, const GLchar** source, const GLint *param) //TODO: Fix definition
{
  _glShaderSource(shaderId, size, source, param);
}

void ShadersImpl::glCompileShader(GLuint shaderId) {
  _glCompileShader(shaderId);
}

void ShadersImpl::glDetachShader(GLuint programId, GLuint shaderId) {
  _glDetachShader(programId, shaderId);
}

void ShadersImpl::glDeleteObject(GLhandleARB handle) // TODO: Is it really about shaders?
{
  _glDeleteObject(handle);
}

void ShadersImpl::glGetInfoLog(GLhandleARB programId, GLsizei size, GLsizei *written, GLcharARB *log) {
  _glGetInfoLog(programId, size, written, log);
}

GLint ShadersImpl::glGetUniformLocation(GLuint shaderId, const GLchar* name) {
  return _glGetUniformLocation(shaderId, name);
}

void ShadersImpl::glUniform1fv(GLint paramId, GLsizei size, const GLfloat *value) {
  _glUniform1fv(paramId, size, value);
}

void ShadersImpl::glUniform2fv(GLint paramId, GLsizei size, const GLfloat *value) {
  _glUniform2fv(paramId, size, value);
}

void ShadersImpl::glUniform3fv(GLint paramId, GLsizei size, const GLfloat *value) {
  _glUniform3fv(paramId, size, value);
}

void ShadersImpl::glUniform4fv(GLint paramId, GLsizei size, const GLfloat *value) {
  _glUniform4fv(paramId, size, value);
}

void ShadersImpl::glUniform4f(GLint paramId, float a, float b, float c, float d) {
  _glUniform4f(paramId, a, b, c, d);
}

void ShadersImpl::glUniform1i(GLint paramId, GLint value) {
  _glUniform1i(paramId, value);
}

void ShadersImpl::glGetUniformfv(GLuint shaderId, GLint paramId, GLfloat *values) {
  _glGetUniformfv(shaderId, paramId, values);
}

void ShadersImpl::glGetUniformiv(GLuint shaderId, GLint paramId, GLint *values) {
  _glGetUniformiv(shaderId, paramId, values);
}

}
