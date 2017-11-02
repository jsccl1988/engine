// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "common.h"
#include "logs/log.h"

namespace ve {

Log* Log::instance = NULL;

Log::Log() {
  errors = 0;
  warnings = 0;
}

Log::~Log() {
  clearStreams();
}

Log* Log::getInstance() {
  if (instance == NULL) {
    instance = new Log();
  }

  return instance;
}

/**
    Attaches output stream to the log. It means that any log message will
    be sent to this stream as well as to any other stream that was attacjed to this log file.
*/
void Log::addOutputStream(OutputStream *stream) {
  streams.push_back(new TextWriter(stream));
}

/**
    Remove all the streams from this log.
*/
void Log::clearStreams() {
  for (ve::uint i = 0; i < streams.size(); i++) {
    delete streams[i];
  }

  streams.clear();
}

std::wstring Log::convertGLError(int code) {
  switch (code) {
  case GL_NO_ERROR:
    return L"No error";
  case GL_INVALID_ENUM:
    return L"Invalid enum";
  case GL_INVALID_VALUE:
    return L"Invalid value";
  case GL_INVALID_OPERATION:
    return L"Invalid operation";
  case GL_STACK_OVERFLOW:
    return L"Stack overflow";
  case GL_STACK_UNDERFLOW:
    return L"Stack underflow";
  case GL_OUT_OF_MEMORY:
    return L"Out of memory";
  case GL_TABLE_TOO_LARGE:
    return L"Table too large";
  default:
    FAIL(L"Undefined code", L"Undefined");
  }
}

void Log::info(std::wstring msg) {
  for (uint i = 0; i < streams.size(); i++) {
    streams[i]->printf("%ls\n", msg.c_str());
    streams[i]->flush();
  }
}

void Log::debugInfo(std::wstring file, int line, std::wstring function, std::wstring info) {
  for (uint i = 0; i < streams.size(); i++) {
    streams[i]->printf("DEBUG:  File %ls \n\tLine: %d \n\tFunction:%ls [%ls]\n", file.c_str(), line, function.c_str(), info.c_str());
    streams[i]->flush();
  }
}

void Log::warning(std::wstring warning) {
  for (uint i = 0; i < streams.size(); i++) {
    streams[i]->printf("WARNING: %ls\n", warning.c_str());
    streams[i]->flush();
  }
  warnings++;
}

void Log::error(std::wstring error) {
  for (uint i = 0; i < streams.size(); i++) {
    streams[i]->printf("ERROR: %ls\n", error.c_str());
    streams[i]->flush();
  }
  errors++;
}

void Log::error(std::wstring function, std::wstring error) {
  for (uint i = 0; i < streams.size(); i++) {
    streams[i]->printf("ERROR: %ls [%ls]\n", function.c_str(), error.c_str());
    streams[i]->flush();
  }
  errors++;
}

void Log::error(int line, std::wstring function, std::wstring error) {
  for (uint i = 0; i < streams.size(); i++) {
    streams[i]->printf("ERROR: Line: %d %ls [%ls]\n", line, function.c_str(), error.c_str());
    streams[i]->flush();
  }
  errors++;
}

void Log::error(std::wstring file, int line, std::wstring function, std::wstring error) {
  for (uint i = 0; i < streams.size(); i++) {
    streams[i]->printf("ERROR:  File: %ls \n\tLine: %d \n\tFunction:%ls [%ls]\n", file.c_str(), line, function.c_str(), error.c_str());
    streams[i]->flush();
  }
  errors++;
}

void Log::glError(std::wstring file, int line, std::wstring function, GLenum error) {
  for (uint i = 0; i < streams.size(); i++) {
    streams[i]->printf("ERROR:  File: %ls \n\tLine: %d \n\tFunction:%ls [%ls]\n", file.c_str(), line, function.c_str(), convertGLError(error).c_str());
    streams[i]->flush();
  }
  errors++;
}

}
