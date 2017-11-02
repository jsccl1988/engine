// Copyright (c) 2017 The Smart Authors.
// All rights reserved.
#ifndef __VE_DEBUG_H__
#define __VE_DEBUG_H__

#include "consts.h"
#include "tools/string_tool.h"

#define __WFILE__ StringTool::AsciiToWide(__FILE__)
#define __WFUNCTION__ StringTool::AsciiToWide(__FUNCTION__)

#define LOG_ERROR(description) Log::getInstance()->error(__WFILE__, __LINE__, __WFUNCTION__, std::wstring(description));

#ifdef VE_DEBUG

#define DEBUG_INFO(description) Log::getInstance()->debugInfo(StringTool::AsciiToWide(__FILE__), __LINE__, std::wstring(StringTool::AsciiToWide(__FUNCTION__)), std::wstring(description));

#define GL_CHECK(result) \
{ \
  GLenum error = glGetError(); \
  if (error != GL_NO_ERROR) \
  { \
    Log::getInstance()->glError(__WFILE__, __LINE__, __WFUNCTION__, error); \
    return result; \
  } \
}

#define GL_SAFE_CALL(call, result) \
  call; \
  GL_CHECK(result);

#else  // VE_DEBUG

#define DEBUG_INFO(description)
#define GL_CHECK(result)
#define GL_SAFE_CALL(call, result) call;

#endif // VE_DEBUG

#define ASSERT(result) \
{ \
  Outcome __outcome = (result); \
  if ((__outcome) != OK) \
  { \
    LOG_ERROR(StringTool::AsciiToWide(#result)); \
    return __outcome; \
  } \
}

#define CHECK_POINTER(pointer) \
{ \
  void *__pointer = (void*)(pointer); \
  if (__pointer == 0) \
  { \
    LOG_ERROR(L"NULL Pointer"); \
    return NULL_POINTER; \
  } \
}

#define CHECK_POINTER_EX(pointer, ret_val) \
{ \
  void *__pointer = pointer; \
  if (__pointer == 0) \
  { \
    LOG_ERROR(L"NULL Pointer"); \
    return ret_val; \
  } \
}

#define CHECK_ALLOC(pointer) \
  if ((pointer) == 0) \
  { \
    LOG_ERROR(L"Unsufficient memory"); \
    return OUT_OF_MEMORY; \
  }

#define CHECK_ALLOC_EX(pointer, ret_val) \
  if ((pointer) == 0) \
  { \
    LOG_ERROR(L"Unsufficient memory"); \
    return ret_val; \
  }

#define FAIL(description, err) \
  { \
    LOG_ERROR(std::wstring(description)); \
    return err; \
  } \

#define CHECK_RESULT(result, description) \
{ \
  Outcome __outcome = (result); \
  if ((__outcome) != OK) \
  { \
    LOG_ERROR(description); \
    return __outcome; \
  } \
}

#define ERROR_IF(condition, description, err) \
{ \
  bool __outcome = (condition); \
  if (__outcome == true) \
  { \
    LOG_ERROR(description); \
    return err; \
  } \
}

#define LOG_IF(condition, description) \
{ \
  bool __outcome = (condition); \
  if (__outcome == true) \
  { \
    LOG_ERROR(description); \
  } \
}

#define LOG_WIN_SOCKET_ERROR() LOG_ERROR(L"Win socket error: " + StringTool::intToStr(WSAGetLastError()));

#define LOG_LINUX_SOCKET_ERROR() LOG_ERROR(L"Linux socket error: " + StringTool::intToStr(errno));

#define LOG_WIN_ERROR() LOG_ERROR(L"Windows error: " + StringTool::intToStr(GetLastError()));

#define UNIMPLEMENTED() LOG_ERROR(L"Unimplemented method");

#define EPIC_FAIL(err) LOG_ERROR(err); exit(1);

#endif // __VE_DEBUG_H__
