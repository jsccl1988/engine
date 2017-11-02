// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_CONSTS_H__
#define __VE_CONSTS_H__

#include "engine/types.h"

/** @file eeConsts.h */

namespace ve {

/* Fuck the native windows definition of ERROR */
#if defined(ERROR) && defined(VE_WINDOWS)
#undef ERROR
#endif // ifdef ERROR

/**
    Outcome enumeration is used in almost every function
    as a result code. It is used to handle common errors
    which may occurr during function execution.
*/
enum Outcome {
  OK = -1,                /*!< Function succeeded.               */
  ERROR = -2,             /*!< Common error.                     */
  IO_ERROR = -3,          /*!< File I/O succeeded.               */
  SOUND_ERROR = -4,       /*!< Sound system common error.        */
  NULL_POINTER = -5,      /*!< NULL pointer exception.           */
  INVALID_ENUM = -6,      /*!< Invalid enumerated value.         */
  INVALID_VALUE = -7,     /*!< Invalid input value.              */
  INVALID_OPERATION = -8, /*!< Invalid operation was requested.  */
  STACK_OVERFLOW = -9,    /*!< Stack overflow occurred.          */
  STACK_UNDERFLOW = -10,  /*!< Stack underflow occurred.         */
  OUT_OF_MEMORY = -11,    /*!< Out of memory exception.          */
  TABLE_TOO_LARGE = -12,  /*!< Don't really know :)              */
  WINAPI_ERROR = -13,  /*!< Error was produced by WinAPI call */
};

// Resource types
enum ResourceType {
  PNG = 0,
  BMP,
  TGA,
  SC,
  VSH,
  PSH,
  TXT,
  OTHER
};

/**
    Constant which defines invalid handle.
*/
const uint INVALID_HANDLE = (uint)-1;

#define WHITE      Vector4f(1.0, 1.0, 1.0, 1.0)
#define GRAY       Vector4f(0.5, 0.5, 0.5, 1.0)
#define BLACK      Vector4f(0.0, 0.0, 0.0, 1.0)
#define RED        Vector4f(1.0, 0.0, 0.0, 1.0)
#define GREEN      Vector4f(0.0, 1.0, 0.0, 1.0)
#define BLUE       Vector4f(0.0, 0.0, 1.0, 1.0)
#define DARK_GREEN Vector4f(0.0, 0.5, 0.0, 1.0)
#define LIGHT_GRAY Vector4f(0.75, 0.75, 0.75, 1.0)
#define YELLOW     Vector4f(1.0, 1.0, 0.0, 1.0)

}

#endif // __VE_CONSTS_H__
