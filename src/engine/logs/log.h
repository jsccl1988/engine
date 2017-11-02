// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_LOG_H__
#define __VE_LOG_H__

#include <string>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "engine/common.h"
#include "engine/types.h"
#include "engine/consts.h"
#include "engine/io/output_stream.h"
#include "engine/io/text_writer.h"

namespace ve {

/**
    Singleton class to manage log file, register errors,
    warnings and debug information.
*/
class Log {
private:
  /** List of attached output streams */
  std::vector<TextWriter*> streams;

  /** Number of errors */
  int errors;

  /** Number of warnings */
  int warnings;

  /** Instance of this class */
  static Log *instance;

  /**
      Private constructor. It uses start() function
      to create log file.
  */
  Log();

public:
  /**
      Log destructor. Log file is closed in this destructor.
  */
  virtual ~Log();

  /**
      Returns single instance of Log class.
      @return Pointer to a Log object.
  */
  static Log *getInstance();

  /**
      Attaches output stream to the log. It means that any log message will
      be sent to this stream as well as to any other stream that was attacjed to this log file.
  */
  void addOutputStream(OutputStream *stream);

  /**
      Remove all the streams from this log.
  */
  void clearStreams();

  /**
      Translates OpenGL error to string.
      @param code - GLenum constant of error to translate.
      @return String description for error code.
  */
  std::wstring convertGLError(int code);

  /**
      Puts info message to the log file.
      @param msg - Info string to place to this log file.
  */
  void info(std::wstring msg);

  /**
      Puts warning message to the log file.
      @param warning - Warning string to place to this log file.
  */
  void warning(std::wstring warning);

  /**
      Puts error message to the log file.
      @param error - Error string to place to this log file.
  */
  void error(std::wstring error);

  /**
      Puts error message to the log file.
      @param function - Function name where error occurred.
      @param error - Error string to place to this log file.
  */
  void error(std::wstring function, std::wstring error);

  /**
      Puts error message to the log file.
      @param line - Line number where error occurred.
      @param function - Function name where error occurred.
      @param error - Error string to place to this log file.
  */
  void error(int line, std::wstring function, std::wstring error);

  /**
      Puts error message to the log file.
      @param file - File name where error occurred.
      @param line - Line number where error occurred.
      @param function - Function name where error occurred.
      @param error - Error string to place to this log file.
  */
  void error(std::wstring file, int line, std::wstring function, std::wstring error);

  /**
      Puts debug info to the log file.
      @param file - File name where info was placed.
      @param line - Line number where info was placed.
      @param function - Function name where info was placed.
      @param info - Debug info string to place to this log file.
  */
  void debugInfo(std::wstring file, int line, std::wstring function, std::wstring info);

  /**
      Puts OpenGL error message to the log file.
      @param file - File name where error occurred.
      @param line - Line number where error occurred.
      @param function - Function name where error occurred.
      @param error - OpenGL error code to place to this log file.
  */
  void glError(std::wstring file, int line, std::wstring function, GLenum error);
};

}

#endif // __VE_LOG_H__
