// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include <string.h>

#include "engine/common.h"
#include "engine/engines/gl_engine.h"
#include "engine/textures/texture.h"
#include "engine/buffers/video_buffer.h"
#include "engine/shaders/shaders.h"
#include "engine/shaders/program.h"
#include "engine/tools/string_tool.h"

namespace ve {

GLEngine* GLEngine::instance = NULL;

/* Init functions */
GLEngine::GLEngine() {
  stateManager = NULL;
  deviceCaps = NULL;
  batches = 0;
}

GLEngine::~GLEngine() {
  delete stateManager;
  delete deviceCaps;
}

GLEngine* GLEngine::getInstance() {
  if (instance == NULL) {
    instance = new GLEngine();
  }

  return instance;
}

Outcome GLEngine::initialize(Window *window) {
  deviceCaps = new GLDeviceCaps(this);
  CHECK_POINTER(deviceCaps);

  /* Init ARB_multitexture */
  if (deviceCaps->isMultiTextureSupported()) {
    MultiTextureFunctions = new MultiTextureImpl();
  } else {
    MultiTextureFunctions = new MultiTextureExt();
  }
  CHECK_POINTER(MultiTextureFunctions);
  MultiTextureFunctions->initialize(this);

  /* Init GL_ARB_vertex_buffer_object */
  if (deviceCaps->isVBOSupported()) {
    VBOFunctions = new VBOImpl();
  } else {
    VBOFunctions = new VBOExt();
  }
  CHECK_POINTER(VBOFunctions);
  ASSERT(VBOFunctions->initialize(this));

  /* Init shaders */
  if (deviceCaps->isGLSLSupported()) {
    ShadersFunctions = new ShadersImpl();
  } else {
    ShadersFunctions = new ShadersExt();
  }
  CHECK_POINTER(ShadersFunctions);
  ASSERT(ShadersFunctions->initialize(this));

  /* Init frame buffer objects */
  if (deviceCaps->isFBOSupported()) {
    FBOFunctions = new FBOImpl();
  } else {
    FBOFunctions = new FBOExt();
  }
  CHECK_POINTER(FBOFunctions);
  ASSERT(FBOFunctions->initialize(this));

  /* Init mimmap generation */
  if (deviceCaps->isMipMapsSupported()) {
    MIPs = new MIPsImpl();
  } else {
    MIPs = new MIPsExt();
  }
  CHECK_POINTER(MIPs);
  ASSERT(MIPs->initialize(this));

  /* Init VSync extension */
  if (deviceCaps->isVSyncSupported()) {
    VSync = new VSyncImpl();
  } else {
    VSync = new VSyncExt();
  }
  CHECK_POINTER(VSync);
  ASSERT(VSync->initialize(this));

  ((GLDeviceCaps*)deviceCaps)->setFBOFunctions(FBOFunctions);

  stateManager = new GLGPUStateManager(this, MultiTextureFunctions, VBOFunctions, ShadersFunctions);
  CHECK_POINTER(stateManager);

  return OK;
}

/**
    Returns state manager of this engine. It used to set/get any pipeline state.
*/
GPUStateManager* GLEngine::getStateManager() {
  return stateManager;
}

/**
    Returns device capabilities manager. It is used to check features support
    of retrieve GPU-specific constants like maximum level of anisotropy
    supported on this GPU.
    @return DeviceCaps object.
*/
DeviceCaps* GLEngine::getDeviceCaps() {
  return deviceCaps;
}

/**
    Waits for vertical synchronization.
    @return 0 if function succeeded.
*/
int GLEngine::waitForVSync() {
  return VSync->waitForVSync();
}

/**
      Enables VSync.
  */
void GLEngine::enableVSync() {
  VSync->enableVSync();
}

/**
      Disables VSync.
  */
void GLEngine::disableVSync() {
  VSync->disableVSync();
}

bool GLEngine::isExtensionSupported(std::string extension) {
  char *ext = (char*)glGetString(GL_EXTENSIONS);

  CHECK_POINTER_EX(ext, false);

  if (strstr(ext, extension.c_str()) != NULL) {
    return true;
  }

#ifdef VE_LINUX
  /* There is a chance to found extension in the GLX extensions list */
  ext = (char*)glXQueryExtensionsString(glXGetCurrentDisplay(), 0);
  if (strstr(ext, extension.c_str()) != NULL) {
    return true;
  }
#endif // VE_LINUX

  return false;
}

void* GLEngine::getProcAddress(std::string name) {
#ifdef VE_LINUX
  return (void *)glXGetProcAddressARB((const GLubyte *)name.c_str());
#else
  return wglGetProcAddress(name.c_str());
#endif
}

/* Internal functions */
GLenum GLEngine::convertFormat(TextureFormat format) {
  switch (format) {
  case RGB8:
    return GL_RGB;
  case RGBA8:
    return GL_RGBA;
  case BGR8:
    return GL_BGR;
  case BGRA8:
    return GL_BGRA;
  case RGB_DXT1:
    return GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
  case RGBA_DXT1:
    return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
  case RGBA_DXT3:
    return GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
  case RGBA_DXT5:
    return GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
  case LUMINANCE8:
    return GL_LUMINANCE;
  case INTENSITY8:
    return GL_INTENSITY;
  case RGB16F:
    return GL_RGB16F_ARB;
  case RGBA16F:
    return GL_RGBA16F_ARB;
  case ALPHA16F:
    return GL_ALPHA16F_ARB;
  case INTENSITY16F:
    return GL_INTENSITY16F_ARB;
  case LUMINANCE16F:
    return GL_LUMINANCE16F_ARB;
  case LUMINANCE_ALPHA16F:
    return GL_LUMINANCE_ALPHA16F_ARB;
  case RGB32F:
    return GL_RGB32F_ARB;
  case RGBA32F:
    return GL_RGBA32F_ARB;
  case ALPHA32F:
    return GL_ALPHA32F_ARB;
  case INTENSITY32F:
    return GL_INTENSITY32F_ARB;
  case LUMINANCE32F:
    return GL_LUMINANCE32F_ARB;
  case LUMINANCE_ALPHA32F:
    return GL_LUMINANCE_ALPHA32F_ARB;
  }

  LOG_ERROR(L"Unsupported format");
  return (GLenum)ERROR;
}

GLenum GLEngine::getTexImageTypes(TextureFormat format) {
  switch (format) {
  case RGB8:
    return GL_UNSIGNED_BYTE;
  case RGBA8:
    return GL_UNSIGNED_BYTE;
  case BGR8:
    return GL_UNSIGNED_INT_8_8_8_8_REV;
  case BGRA8:
    return GL_UNSIGNED_INT_8_8_8_8_REV;
  case RGB_DXT1:
    return GL_UNSIGNED_BYTE;
  case RGBA_DXT1:
    return GL_UNSIGNED_BYTE;
  case RGBA_DXT3:
    return GL_UNSIGNED_BYTE;
  case RGBA_DXT5:
    return GL_UNSIGNED_BYTE;
  case LUMINANCE8:
    return GL_UNSIGNED_BYTE;
  case INTENSITY8:
    return GL_UNSIGNED_BYTE;
  case RGB16F:
    return GL_UNSIGNED_BYTE;
  case RGBA16F:
    return GL_UNSIGNED_BYTE;
  case ALPHA16F:
    return GL_UNSIGNED_BYTE;
  case INTENSITY16F:
    return GL_UNSIGNED_BYTE;
  case LUMINANCE16F:
    return GL_UNSIGNED_BYTE;
  case LUMINANCE_ALPHA16F:
    return GL_UNSIGNED_BYTE;
  case RGB32F:
    return GL_UNSIGNED_BYTE;
  case RGBA32F:
    return GL_UNSIGNED_BYTE;
  case ALPHA32F:
    return GL_UNSIGNED_BYTE;
  case INTENSITY32F:
    return GL_UNSIGNED_BYTE;
  case LUMINANCE32F:
    return GL_UNSIGNED_BYTE;
  case LUMINANCE_ALPHA32F:
    return GL_UNSIGNED_BYTE;
  }

  LOG_ERROR(L"Unsupported format");
  return (GLenum)ERROR;
}

GLenum GLEngine::convertTopology(Topology topology) {
  switch (topology) {
  case POINTS:
    return GL_POINTS;
  case LINE_STRIP:
    return GL_LINE_STRIP;
  case LINE_LOOP:
    return GL_LINE_LOOP;
  case LINES:
    return GL_LINES;
  case TRIANGLE_STRIP:
    return GL_TRIANGLE_STRIP;
  case TRIANGLE_FAN:
    return GL_TRIANGLE_FAN;
  case TRIANGLES:
    return GL_TRIANGLES;
  case QUAD_STRIP:
    return GL_QUAD_STRIP;
  case QUADS:
    return GL_QUADS;
  case POLYGON:
    return GL_POLYGON;
  }
  FAIL(L"Unsupported topology", (GLenum)ERROR);
}

GLenum GLEngine::convertType(Type type) {
  switch (type) {
  case SHORT:
    return GL_SHORT;
  case INT:
    return GL_INT;
  case FLOAT:
    return GL_FLOAT;
  case DOUBLE:
    return GL_DOUBLE;
  case UNSIGNED_INT:
    return GL_UNSIGNED_INT;
  case UNSIGNED_BYTE:
    return GL_UNSIGNED_BYTE;
  case UNSIGNED_SHORT:
    return GL_UNSIGNED_SHORT;
  }
  FAIL(L"Unsupported type", (GLenum)ERROR);
}

GLenum GLEngine::convertArray(Array array) {
  switch (array) {
  case TEXTURE_COORD_ARRAY:
    return GL_TEXTURE_COORD_ARRAY;
  case COLOR_ARRAY:
    return GL_COLOR_ARRAY;
  case INDEX_ARRAY:
    return GL_INDEX_ARRAY;
  case NORMAL_ARRAY:
    return GL_NORMAL_ARRAY;
  case VERTEX_ARRAY:
    return GL_VERTEX_ARRAY;
  }
  FAIL(L"Unsupported array", (GLenum)ERROR);
}

GLenum GLEngine::convertVideoBufferStoreMethod(VideoBufferStoreMethod method) {
  switch (method) {
  case STATIC_DRAW:
    return GL_STATIC_DRAW_ARB;
  case STATIC_READ:
    return GL_STATIC_READ_ARB;
  case STATIC_COPY:
    return GL_STATIC_COPY_ARB;
  case DYNAMIC_DRAW:
    return GL_DYNAMIC_DRAW_ARB;
  case DYNAMIC_READ:
    return GL_DYNAMIC_READ_ARB;
  case DYNAMIC_COPY:
    return GL_DYNAMIC_COPY_ARB;
  case STREAM_DRAW:
    return GL_STREAM_DRAW_ARB;
  case STREAM_READ:
    return GL_STREAM_READ_ARB;
  case STREAM_COPY:
    return GL_STREAM_COPY_ARB;
  }

  FAIL(L"Unsupported video buffer store method", (GLenum)ERROR);
}

GLenum GLEngine::convertAccess(AccessType access) {
  switch (access) {
  case READ_ONLY:
    return GL_READ_ONLY_ARB;
  case WRITE_ONLY:
    return GL_WRITE_ONLY_ARB;
  case READ_WRITE:
    return GL_READ_WRITE_ARB;
  }
  FAIL(L"Unsupported access", (GLenum)ERROR);
}

GLenum GLEngine::convertClearFlag(ClearFlag flag) {
  GLenum result = 0;
  if (flag & COLOR) {
    result |= GL_COLOR_BUFFER_BIT;
  }
  if (flag & DEPTH) {
    result |= GL_DEPTH_BUFFER_BIT;
  }
  if (flag & STENCIL) {
    result |= GL_STENCIL_BUFFER_BIT;
  }
  return result;
}

GLenum GLEngine::convertMatrix(MatrixType type) {
  switch (type) {
  case PROJECTION:
    return GL_PROJECTION;
  case MODELVIEW:
    return GL_MODELVIEW;
  }
  FAIL(L"Unsupported matrix type", (GLenum)ERROR);
}

GLenum GLEngine::convertRenderBufferSlot(RenderBufferSlot slot) {
  GLenum map[] =
  {
      GL_COLOR_ATTACHMENT0_EXT, GL_COLOR_ATTACHMENT1_EXT, GL_COLOR_ATTACHMENT2_EXT,
      GL_COLOR_ATTACHMENT3_EXT, GL_COLOR_ATTACHMENT4_EXT, GL_COLOR_ATTACHMENT5_EXT,
      GL_COLOR_ATTACHMENT6_EXT, GL_COLOR_ATTACHMENT7_EXT, GL_DEPTH_ATTACHMENT_EXT,
      GL_STENCIL_ATTACHMENT_EXT
  };

  int index = static_cast<int>(slot);
  ERROR_IF(index >= sizeof(map) / sizeof(GLenum), L"Index: " + StringTool::intToStr(index) + L" is out of bounds", ERROR);
  return map[index];
}

/* Create functions */
Texture* GLEngine::createTexture(TextureFormat format, int width, int height, TextureFormat nativeformat, void* data, bool useMips) {
  GLhandleARB newHandle;
  glGenTextures(1, &newHandle);
  GLuint internalFormat = convertFormat(format);
  GLuint nativeFormat = convertFormat(nativeformat);
  int components = getComponents(format);

  CHECK_POINTER_EX(data, NULL);

  GLenum target = GL_TEXTURE_2D;
  bool nonPowerOfTwo = (width & (width - 1)) != 0 || (height & (height - 1)) != 0;
  //if (nonPowerOfTwo) {
  //  target = GL_TEXTURE_RECTANGLE_ARB;
  //}

  GL_SAFE_CALL(glPixelStorei(GL_UNPACK_ALIGNMENT, 1), NULL);
  GL_SAFE_CALL(glBindTexture(target, newHandle), NULL);

  GL_SAFE_CALL(glPixelStorei(GL_UNPACK_ROW_LENGTH, width), NULL);
  GL_SAFE_CALL(glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0), NULL);
  GL_SAFE_CALL(glPixelStorei(GL_UNPACK_SKIP_ROWS, 0), NULL);

  GL_SAFE_CALL(glTexImage2D(target, 0, internalFormat, width, height, 0
    , nativeFormat, getTexImageTypes(nativeformat), data), NULL);
  if (useMips && !nonPowerOfTwo) {
    GL_SAFE_CALL(MIPs->glGenerateMipmap(GL_TEXTURE_2D), NULL);
  }

  TextureDesc desc;
  memset(&desc, 0, sizeof(desc));
  desc.format = format;
  desc.width = width;
  desc.height = height;

  Texture *newTexture = new Texture(this, desc, newHandle);
  CHECK_ALLOC_EX(newTexture, NULL);
  REGISTER_POINTER(newTexture);

  GLIdToTexture[newHandle] = newTexture;

  return newTexture;
}

VideoBuffer* GLEngine::createVideoBuffer(Array type) {
  GLhandleARB newHandle;

  GL_SAFE_CALL(VBOFunctions->glGenBuffers(1, &newHandle), NULL);
  VideoBuffer *newVideoBuffer = new VideoBuffer(this, newHandle, type);
  CHECK_ALLOC_EX(newVideoBuffer, NULL);
  REGISTER_POINTER(newVideoBuffer);

  GLIdToBuffer[newHandle] = newVideoBuffer;

  return newVideoBuffer;
}

Shader* GLEngine::createVertexShader() {
  GLhandleARB newHandle = ShadersFunctions->glCreateShader(GL_VERTEX_SHADER_ARB);
  GL_CHECK(NULL);
  Shader *newShader = new Shader(this, newHandle);
  CHECK_ALLOC_EX(newShader, NULL);
  return newShader;
}

Shader* GLEngine::createPixelShader() {
  GLhandleARB newHandle = ShadersFunctions->glCreateShader(GL_FRAGMENT_SHADER_ARB);
  GL_CHECK(NULL);
  Shader* newShader = new Shader(this, newHandle);
  CHECK_ALLOC_EX(newShader, NULL);
  return newShader;
}

Program* GLEngine::createProgram() {
  GLhandleARB newHandle = ShadersFunctions->glCreateProgram();
  GL_CHECK(NULL);
  Program *newProgram = new Program(this, newHandle);
  CHECK_ALLOC_EX(newProgram, NULL);

  GLIdToProgram[newHandle] = newProgram;

  return newProgram;
}

/* Texture functions */
Outcome GLEngine::freeTexture(Texture *texture) {
  CHECK_POINTER(texture);
  GLhandleARB handle = texture->getHandle();
  GLIdToTexture[handle] = 0;
  if (handle != 0) {
    GL_SAFE_CALL(glDeleteTextures(1, &handle), ERROR);
  }
  return OK;
}

Outcome GLEngine::updateTexture(Texture* texture, TextureFormat nativeformat, void* data) {
  CHECK_POINTER_EX(data, ERROR);

  GLuint internalFormat = convertFormat(texture->getDesc().format);
  GLuint nativeFormat = convertFormat(nativeformat);
  int components = getComponents(texture->getDesc().format);
  GLenum target = GL_TEXTURE_2D;
  bool nonPowerOfTwo = (texture->getDesc().width & (texture->getDesc().width - 1)) != 0
    || (texture->getDesc().height & (texture->getDesc().height - 1)) != 0;
  //if (nonPowerOfTwo) {
  //  target = GL_TEXTURE_RECTANGLE_ARB;
  //}

  GL_SAFE_CALL(glPixelStorei(GL_UNPACK_ROW_LENGTH, texture->getDesc().width), ERROR);
  GL_SAFE_CALL(glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0), ERROR);
  GL_SAFE_CALL(glPixelStorei(GL_UNPACK_SKIP_ROWS, 0), ERROR);

  GL_SAFE_CALL(glTexImage2D(target, 0, internalFormat
    , texture->getDesc().width, texture->getDesc().height, 0
    , nativeFormat, getTexImageTypes(nativeformat), data), ERROR);

  return OK;
}

void* GLEngine::getTextureData(Texture *texture) {
  UNIMPLEMENTED();
  return NULL;
}

/* Shader functions */
Outcome GLEngine::loadShaderSource(Shader *shader, char* source) {
  GLhandleARB handle = shader->getHandle();
  GL_SAFE_CALL(ShadersFunctions->glShaderSource(handle, 1, (const GLchar**)&source, NULL), ERROR);
  return OK;
}

Outcome GLEngine::compileShader(Shader *shader) {
  GLhandleARB handle = shader->getHandle();
  GL_SAFE_CALL(ShadersFunctions->glCompileShader(handle), ERROR);
  return OK;
}

Outcome GLEngine::isShaderCompiled(Shader *shader) {
  GLhandleARB handle = shader->getHandle();
  int compileStatus = 0;

  GL_SAFE_CALL(ShadersFunctions->glGetObjectParameteriv(handle, GL_OBJECT_COMPILE_STATUS_ARB, &compileStatus), ERROR);
  if (compileStatus == 0) {
    return ERROR;
  }

  return OK;
}

Outcome GLEngine::setProgramVector(Program *program, string &param, const Vector4f &value) {
  CHECK_POINTER(program);
  GLhandleARB handle = program->getHandle();

  int loc = ShadersFunctions->glGetUniformLocation(handle, param.c_str());
  ERROR_IF(loc < 0, L"Incorrect name: " + StringTool::AsciiToWide(param), ERROR);
  GL_SAFE_CALL(ShadersFunctions->glUniform4fv(loc, 1, (const GLfloat*)&value), ERROR);
  return OK;
}

Outcome GLEngine::setProgramVector(Program *program, string &param, const Vector3f &value) {
  CHECK_POINTER(program);
  GLhandleARB handle = program->getHandle();

  int loc = ShadersFunctions->glGetUniformLocation(handle, param.c_str());
  ERROR_IF(loc < 0, L"Incorrect name: " + StringTool::AsciiToWide(param), ERROR);
  GL_SAFE_CALL(ShadersFunctions->glUniform3fv(loc, 1, (const GLfloat*)&value), ERROR);
  return OK;
}

Outcome GLEngine::setProgramVector(Program *program, string &param, const Vector2f &value) {
  CHECK_POINTER(program);
  GLhandleARB handle = program->getHandle();

  int loc = ShadersFunctions->glGetUniformLocation(handle, param.c_str());
  ERROR_IF(loc < 0, L"Incorrect name: " + StringTool::AsciiToWide(param), ERROR);
  GL_SAFE_CALL(ShadersFunctions->glUniform2fv(loc, 1, (const GLfloat*)&value), ERROR);
  return OK;
}

Outcome GLEngine::setProgramFloat(Program *program, string &param, float value) {
  CHECK_POINTER(program);
  GLhandleARB handle = program->getHandle();

  int loc = ShadersFunctions->glGetUniformLocation(handle, param.c_str());
  ERROR_IF(loc < 0, L"Incorrect Name: " + StringTool::AsciiToWide(param), ERROR);
  GL_SAFE_CALL(ShadersFunctions->glUniform1fv(loc, 1, &value), ERROR);
  return OK;
}

Outcome GLEngine::setProgramInt(Program *program, string &param, int value) {
  CHECK_POINTER(program);
  GLhandleARB handle = program->getHandle();

  int loc = ShadersFunctions->glGetUniformLocation(handle, param.c_str());
  ERROR_IF(loc < 0, L"Incorrect name: " + StringTool::AsciiToWide(param), ERROR);
  GL_SAFE_CALL(ShadersFunctions->glUniform1i(loc, value), ERROR);
  return OK;
}

Outcome GLEngine::getProgramFloat(Program *program, string &param, float *value) {
  CHECK_POINTER(program);
  GLhandleARB handle = program->getHandle();

  int loc = ShadersFunctions->glGetUniformLocation(handle, param.c_str());
  ERROR_IF(loc < 0, L"Incorrect name: " + StringTool::AsciiToWide(param), ERROR);
  GL_SAFE_CALL(ShadersFunctions->glGetUniformfv(handle, loc, value), ERROR);
  return OK;
}

Outcome GLEngine::setProgramTexture(Program *program, string &param, int texture) {
  CHECK_POINTER(program);
  GLhandleARB handle = program->getHandle();

  int loc = ShadersFunctions->glGetUniformLocation(handle, param.c_str());
  ERROR_IF(loc < 0, L"Incorrect Name: " + StringTool::AsciiToWide(param), ERROR);
  GL_SAFE_CALL(ShadersFunctions->glUniform1i(loc, texture), ERROR);
  return OK;
}

char* GLEngine::getShaderLog(Shader *shader) {
  CHECK_POINTER_EX(shader, NULL);

  GLchar *log = 0;
  int logLength = 0;
  int charsWritten = 0;
  GLhandleARB handle = shader->getHandle();

  GL_SAFE_CALL(ShadersFunctions->glGetObjectParameteriv(handle, GL_OBJECT_INFO_LOG_LENGTH_ARB, &logLength), NULL);

  if (logLength < 1)
    return NULL;

  log = new GLchar[logLength];
  CHECK_ALLOC_EX(log, NULL);

  GL_SAFE_CALL(ShadersFunctions->glGetInfoLog(handle, logLength, &charsWritten, log), NULL);
  return log;
}

Outcome GLEngine::freeShader(Shader *shader) {
  CHECK_POINTER(shader);
  GLhandleARB handle = shader->getHandle();
  if (handle != 0) {
    GL_SAFE_CALL(ShadersFunctions->glDeleteObject(handle), ERROR);
  }
  return OK;
}

/* Program functions */
Outcome GLEngine::setProgramVertexShader(Program *program, Shader *shader) {
  CHECK_POINTER(program);
  CHECK_POINTER(shader);
  GL_SAFE_CALL(ShadersFunctions->glAttachShader(program->getHandle(), shader->getHandle()), ERROR);
  return OK;
}

Outcome GLEngine::setProgramPixelShader(Program *program, Shader *shader) {
  CHECK_POINTER(program);
  CHECK_POINTER(shader);
  GL_SAFE_CALL(ShadersFunctions->glAttachShader(program->getHandle(), shader->getHandle()), ERROR);
  return OK;
}

Outcome GLEngine::linkProgram(Program *program) {
  CHECK_POINTER(program);
  GL_SAFE_CALL(ShadersFunctions->glLinkProgram(program->getHandle()), ERROR);
  return OK;
}

Outcome GLEngine::isProgramLinked(Program *program) {
  CHECK_POINTER(program);
  int linkStatus = 0;

  GL_SAFE_CALL(ShadersFunctions->glGetObjectParameteriv(program->getHandle(), GL_OBJECT_LINK_STATUS_ARB, &linkStatus), ERROR);
  if (linkStatus == 0) {
    return ERROR;
  }

  return OK;
}

char* GLEngine::getProgramLinkLog(Program *program) {
  CHECK_POINTER_EX(program, NULL);

  int logLength;
  char *log = NULL;
  GLhandleARB handle = program->getHandle();
  GL_SAFE_CALL(ShadersFunctions->glGetObjectParameteriv(handle, GL_OBJECT_INFO_LOG_LENGTH_ARB, &logLength), NULL);

  if (logLength != 1) {
    log = new GLchar[logLength];
    int charsWritten;

    GL_SAFE_CALL(ShadersFunctions->glGetInfoLog(handle, logLength, &charsWritten, log), NULL);
  }

  return log;
}

Outcome GLEngine::freeProgram(Program *program) {
  CHECK_POINTER(program);
  GLhandleARB handle = program->getHandle();

  if (handle != 0) {
    GL_SAFE_CALL(ShadersFunctions->glDeleteObject(handle), ERROR);
  }

  GLIdToProgram[handle] = 0;

  return OK;
}

/* Buffer functions */
Outcome GLEngine::updateBuffer(VideoBuffer *buffer, void *data, unsigned int size, VideoBufferStoreMethod method) {
  CHECK_POINTER(buffer);
  CHECK_POINTER(data);

  GL_SAFE_CALL(VBOFunctions->glBindBuffer(GL_ARRAY_BUFFER, buffer->getHandle()), ERROR);
  GLenum GLMethod = convertVideoBufferStoreMethod(method);
  ERROR_IF(GLMethod == (GLenum)ERROR, L"Convert failed", ERROR);
  GL_SAFE_CALL(VBOFunctions->glBufferData(GL_ARRAY_BUFFER, size, data, GLMethod), ERROR);

  return OK;
}

Outcome GLEngine::updateIndexBuffer(VideoBuffer *buffer, void *data, unsigned int size, VideoBufferStoreMethod method) {
  CHECK_POINTER(buffer);
  CHECK_POINTER(data);
  DEBUG_INFO(L"Update index buffer");

  GL_SAFE_CALL(VBOFunctions->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->getHandle()), ERROR);
  GLenum GLMethod = convertVideoBufferStoreMethod(method);
  ERROR_IF(GLMethod == (GLenum)ERROR, L"Convert failed", INVALID_ENUM);
  GL_SAFE_CALL(VBOFunctions->glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GLMethod), ERROR);

  return OK;
}

void* GLEngine::mapBuffer(VideoBuffer* buffer, AccessType access) {
  CHECK_POINTER_EX(buffer, NULL);
  GLenum glAccess = convertAccess(access);
  ERROR_IF(glAccess == (GLenum)ERROR, L"Unsupported access", NULL);
  void *result = VBOFunctions->glMapBuffer(GL_ARRAY_BUFFER, glAccess);
  GL_CHECK(NULL);
  return result;
}

Outcome GLEngine::unmapBuffer(VideoBuffer *buffer) {
  CHECK_POINTER(buffer);
  GLboolean result = VBOFunctions->glUnmapBuffer(GL_ARRAY_BUFFER);
  GL_CHECK(ERROR);
  if (result != GL_TRUE) {
    return ERROR;
  }
  return OK;
}

void* GLEngine::mapIndexBuffer(VideoBuffer* buffer, AccessType access) {
  CHECK_POINTER_EX(buffer, NULL);
  GLenum glAccess = convertAccess(access);
  ERROR_IF(glAccess == (GLenum)ERROR, L"Unsupported access", NULL);
  void *result = VBOFunctions->glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, glAccess);
  GL_CHECK(NULL);
  return result;
}

Outcome GLEngine::unmapIndexBuffer(VideoBuffer *buffer) {
  CHECK_POINTER(buffer);
  GLboolean result = VBOFunctions->glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
  GL_CHECK(ERROR);
  if (result != GL_TRUE) {
    return ERROR;
  }
  return OK;
}

Outcome GLEngine::freeBuffer(VideoBuffer *buffer) {
  CHECK_POINTER(buffer);

  GLhandleARB handle = buffer->getHandle();
  GLIdToBuffer[handle] = 0;
  GL_SAFE_CALL(VBOFunctions->glDeleteBuffers(1, &handle), ERROR);

  return OK;
}

/* Draw functions */
Outcome GLEngine::drawPrimitives(Topology topology, unsigned int first, unsigned int count) {
  /* Increment number of batches */
  batches++;
  GL_SAFE_CALL(glDrawArrays(convertTopology(topology), first, count), ERROR);
  return OK;
}

Outcome GLEngine::drawIndexedPrimitives(Topology topology, unsigned int count, Type type, void *indices) {
  /* Increment number of batches */
  batches++;
  GLenum top = convertTopology(topology);
  ERROR_IF(top == (GLenum)ERROR, L"Unsupported topology", ERROR);
  GLenum ty = convertType(type);
  ERROR_IF(ty == (GLenum)ERROR, L"Unsupported ty", ERROR);
  GL_SAFE_CALL(glDrawElements(top, count, ty, indices), ERROR);
  return OK;
}

Outcome GLEngine::enableMatrix(MatrixType type) {
  GLenum matrix = convertMatrix(type);
  ERROR_IF(matrix == (GLenum)ERROR, L"Unsupported matrix type", ERROR);
  GL_SAFE_CALL(glMatrixMode(matrix), ERROR);
  return OK;
}

Outcome GLEngine::loadIdentityMatrix() {
  GL_SAFE_CALL(glLoadIdentity(), ERROR);
  return OK;
}

Outcome GLEngine::multPerspectiveMatrix(double fovy, double aspect, double zNear, double zFar) {
  GL_SAFE_CALL(gluPerspective(fovy, aspect, zNear, zFar), ERROR);
  return OK;
}

Outcome GLEngine::multLookAtMatrix(Vector3f position, Vector3f lookAt, Vector3f up) {
  GL_SAFE_CALL(gluLookAt(position[0], position[1], position[2],
    lookAt[0], lookAt[1], lookAt[2],
    up[0], up[1], up[2]), ERROR);
  return OK;
}

/* Frame buffer functions */
FrameBuffer* GLEngine::createFrameBuffer() {
  GLhandleARB id;
  GL_SAFE_CALL(FBOFunctions->glGenFramebuffers(1, &id), NULL);
  FrameBuffer *newFB = new FrameBuffer(this, id);
  CHECK_ALLOC_EX(newFB, NULL);
  return newFB;
}

Outcome GLEngine::freeFrameBuffer(FrameBuffer *frameBuffer) {
  GLhandleARB id = frameBuffer->getHandle();
  GL_SAFE_CALL(FBOFunctions->glDeleteFramebuffers(1, &id), ERROR);
  return OK;
}

Outcome GLEngine::bindFrameBuffer(FrameBuffer *frameBuffer) {
  GLhandleARB id = frameBuffer->getHandle();
  GL_SAFE_CALL(FBOFunctions->glBindFramebuffer(GL_FRAMEBUFFER_EXT, id), ERROR);
  return OK;
}

Outcome GLEngine::unbindFrameBuffer() {
  GL_SAFE_CALL(FBOFunctions->glBindFramebuffer(GL_FRAMEBUFFER_EXT, 0), ERROR);
  return OK;
}

RenderBuffer* GLEngine::createRenderBuffer(TextureFormat format, uint width, uint height) {
  GLhandleARB id;
  GLenum rbFormat = convertFormat(format);
  ERROR_IF(rbFormat == (GLenum)ERROR, L"Unsupported format", NULL);
  GL_SAFE_CALL(FBOFunctions->glGenRenderbuffers(1, &id), NULL);
  GL_SAFE_CALL(FBOFunctions->glBindRenderbuffer(GL_RENDERBUFFER_EXT, id), NULL);
  GL_SAFE_CALL(FBOFunctions->glRenderbufferStorage(GL_RENDERBUFFER_EXT, rbFormat, width, height), NULL);
  RenderBuffer* newRB = new RenderBuffer(this, id, format, width, height);
  CHECK_ALLOC_EX(newRB, NULL);
  return newRB;
}

Outcome GLEngine::freeRenderBuffer(RenderBuffer *renderBuffer) {
  GLhandleARB id = renderBuffer->getHandle();
  GL_SAFE_CALL(FBOFunctions->glDeleteRenderbuffers(1, &id), ERROR);
  return OK;
}

Outcome GLEngine::attachRenderBuffer(FrameBuffer *frameBuffer, RenderBuffer *renderBuffer, RenderBufferSlot slot) {
  CHECK_POINTER(frameBuffer);
  CHECK_POINTER(renderBuffer);
  GLenum rbSlot = convertRenderBufferSlot(slot);
  ERROR_IF(rbSlot == (GLenum)ERROR, L"Unknown slot", ERROR);
  GLhandleARB id = renderBuffer->getHandle();
  GL_SAFE_CALL(FBOFunctions->glFramebufferRenderbuffer(GL_FRAMEBUFFER_EXT, rbSlot, GL_RENDERBUFFER_EXT, id), ERROR);
  return OK;
}

Outcome GLEngine::attachTexture(FrameBuffer *frameBuffer, Texture *texture2D, RenderBufferSlot slot) {
  CHECK_POINTER(frameBuffer);
  CHECK_POINTER(texture2D);
  GLenum rbSlot = convertRenderBufferSlot(slot);
  ERROR_IF(rbSlot == (GLenum)ERROR, L"Unknown slot", ERROR);
  GLhandleARB id = texture2D->getHandle();
  GL_SAFE_CALL(FBOFunctions->glFramebufferTexture2D(GL_FRAMEBUFFER_EXT, rbSlot, GL_TEXTURE_2D, id, 0), ERROR);
  return OK;
}

FrameBufferStatus GLEngine::checkFrameBufferStatus() {
  GLenum result = FBOFunctions->glCheckFramebufferStatus(GL_FRAMEBUFFER_EXT);
  switch (result) {
  case GL_FRAMEBUFFER_COMPLETE_EXT:
    return FRAMEBUFFER_COMPLETE;
  case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
    return FRAMEBUFFER_INCOMPLETE_ATTACHMENT;
  case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
    return FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT;
  case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
    return FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER;
  case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
    return FRAMEBUFFER_INCOMPLETE_READ_BUFFER;
  case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
    return FRAMEBUFFER_UNSUPPORTED;
  default:
    FAIL(L"Unknown status", FRAMEBUFFER_UNSUPPORTED);
  }
}

Outcome GLEngine::clear(ClearFlag flag) {
  GLenum flags = convertClearFlag(flag);
  ERROR_IF(flags == (GLenum)ERROR, L"Unsupported flags", ERROR);
  glClear(flags);
  GL_CHECK(ERROR);
  return OK;
}

/* Transforms */
Outcome GLEngine::beginTransform() {
  glPushMatrix();
  return OK;
}

Outcome GLEngine::translate(float x, float y, float z) {
  glTranslatef(x, y, z);
  GL_CHECK(ERROR);
  return OK;
}

Outcome GLEngine::rotate(float angle, float x, float y, float z) {
  glRotatef(angle, x, y, z);
  GL_CHECK(ERROR);
  return OK;
}

Outcome GLEngine::scale(float x, float y, float z) {
  glScalef(x, y, z);
  GL_CHECK(ERROR);
  return OK;
}

Outcome GLEngine::endTransform() {
  glPopMatrix();
  return OK;
}

Texture* GLEngine::getTextureByGLId(GLint id) {
  return GLIdToTexture[id];
}

VideoBuffer* GLEngine::getBufferById(GLint id) {
  return GLIdToBuffer[id];
}

Program* GLEngine::getProgramById(GLint id) {
  return GLIdToProgram[id];
}

uint GLEngine::getBatchesCount() {
  return batches;
}

void GLEngine::onSwapBuffers() {
  batches = 0;
}

}
