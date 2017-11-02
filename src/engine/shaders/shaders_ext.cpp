// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "shaders/shaders_ext.h"

namespace ve {

ShadersExt::ShadersExt() {
}

ShadersExt::~ShadersExt() {
}

Outcome ShadersExt::initialize(GLEngine *engine) {
  return OK;
}

GLuint ShadersExt::glCreateShader(GLenum type) {
  UNIMPLEMENTED();
  return 0;
}

GLuint ShadersExt::glCreateProgram() {
  UNIMPLEMENTED();
  return 0;
}

void ShadersExt::glAttachShader(GLuint programId, GLuint shaderId) {
  UNIMPLEMENTED();
}

void ShadersExt::glLinkProgram(GLuint programId) {
  UNIMPLEMENTED();
}

void ShadersExt::glGetObjectParameteriv(GLhandleARB programId, GLenum target, GLint *value) {
  UNIMPLEMENTED();
}

void ShadersExt::glUseProgram(GLuint programID) {
  UNIMPLEMENTED();
}

void ShadersExt::glShaderSource(GLuint shaderId, GLsizei size, const GLchar** source, const GLint *param) //TODO: Fix definition
{
  UNIMPLEMENTED();
}

void ShadersExt::glCompileShader(GLuint shaderId) {
  UNIMPLEMENTED();
}

void ShadersExt::glDetachShader(GLuint programId, GLuint shaderId) {
  UNIMPLEMENTED();
}

void ShadersExt::glDeleteObject(GLhandleARB handle) // TODO: Is it really about shaders?
{
  UNIMPLEMENTED();
}

void ShadersExt::glGetInfoLog(GLhandleARB programId, GLsizei size, GLsizei *wriiten, GLcharARB *log) {
  UNIMPLEMENTED();
}

GLint ShadersExt::glGetUniformLocation(GLuint shaderId, const GLchar* name) {
  UNIMPLEMENTED();
  return -1;
}

void ShadersExt::glUniform1fv(GLint paramId, GLsizei size, const GLfloat *value) {
  UNIMPLEMENTED();
}

void ShadersExt::glUniform2fv(GLint paramId, GLsizei size, const GLfloat *value) {
  UNIMPLEMENTED();
}

void ShadersExt::glUniform3fv(GLint paramId, GLsizei size, const GLfloat *value) {
  UNIMPLEMENTED();
}

void ShadersExt::glUniform4fv(GLint paramId, GLsizei size, const GLfloat *value) {
  UNIMPLEMENTED();
}

void ShadersExt::glUniform4f(GLint paramId, float a, float b, float c, float d) {
  UNIMPLEMENTED();
}

void ShadersExt::glUniform1i(GLint paramId, GLint value) {
  UNIMPLEMENTED();
}

void ShadersExt::glGetUniformfv(GLuint shaderId, GLint paramId, GLfloat *values) {
  UNIMPLEMENTED();
}

void ShadersExt::glGetUniformiv(GLuint shaderId, GLint paramId, GLint *values) {
  UNIMPLEMENTED();
}

};
