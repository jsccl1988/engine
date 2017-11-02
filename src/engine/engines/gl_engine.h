// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_GLENGINE_H__
#define __VE_GLENGINE_H__

#include <vector>
#include "engine/engines/engine.h"
#include "engine/buffers/vbo_ext.h"
#include "engine/buffers/vbo_impl.h"
#include "engine/shaders/shaders_ext.h"
#include "engine/shaders/shaders_impl.h"
#include "engine/buffers/fbo_ext.h"
#include "engine/buffers/fbo_impl.h"
#include "engine/textures/mips_ext.h"
#include "engine/textures/mips_impl.h"
#include "engine/states/gl_gpu_state_manager.h"
#include "engine/ext/vsync_ext.h"
#include "engine/ext/vsync_impl.h"
#include "engine/ext/multi_texture_ext.h"
#include "engine/ext/multi_texture_impl.h"
#include "engine/engines/gl_device_caps.h"

namespace ve {

  /**
      OpenGL implementation of Engine class.
  */
  class GLEngine : public Engine {
  private:
    /**
      Single instance of GLEngine class.
    */
    static GLEngine* instance;

    /*
        State manager.
    */
    GLGPUStateManager *stateManager;

    /*
        Device capabilities manager.
    */
    GLDeviceCaps *deviceCaps;

    /*
        Following classes contain functions from various OpenGL extensions.
    */
    VBOExt *VBOFunctions;
    ShadersExt *ShadersFunctions;
    FBOExt *FBOFunctions;
    MIPsExt *MIPs;
    VSyncExt *VSync;
    MultiTextureExt *MultiTextureFunctions;

    /* Map to associate GL ids with textures */
    std::map<GLint, Texture*> GLIdToTexture;
    std::map<GLint, VideoBuffer*> GLIdToBuffer;
    std::map<GLint, Program*> GLIdToProgram;

    /* Counter for the batches per frame */
    uint batches;

    GLenum getTexImageTypes(TextureFormat format);
    GLenum convertFormat(TextureFormat format);
    GLenum convertTopology(Topology topology);
    GLenum convertType(Type type);
    GLenum convertArray(Array array);
    GLenum convertVideoBufferStoreMethod(VideoBufferStoreMethod method);
    GLenum convertAccess(AccessType access);
    GLenum convertClearFlag(ClearFlag flag);
    GLenum convertMatrix(MatrixType type);
    GLenum convertRenderBufferSlot(RenderBufferSlot slot);

    /**
      Private constructor.
    */
    GLEngine();

    /**
      Private copy-constructor.
    */
    GLEngine(GLEngine &);

    /**
      Private operator =
    */
    GLEngine operator = (GLEngine &);
  public:
    /**
      Returns the single instance of GLEngine class.
      @return Pointer to GLEngine object.
    */
    static GLEngine *getInstance();

    virtual ~GLEngine();

    /* Init functions */
    virtual Outcome initialize(Window *window);

    /*
      Returns texture object associated with OpenGL id. This function is used only be
      GLGPUStateManager.
    */
    Texture* getTextureByGLId(GLint id);

    /*
      Returns video buffer object associated with OpenGL id. This function is used only be
      GLGPUStateManager.
    */
    VideoBuffer* getBufferById(GLint id);

    /*
      Returns shader program associated with OpenGL id. This function is used only be
      GLGPUStateManager.
    */
    Program* getProgramById(GLint id);

    /**
        Returns state manager of this engine. It used to set/get any pipeline state.
    */
    virtual GPUStateManager* getStateManager();

    /**
        Returns device capabilities manager. It is used to check features support
        of retrieve GPU-specific constants like maximum level of anisotropy
        supported on this GPU.
        @return DeviceCaps object.
    */
    virtual DeviceCaps* getDeviceCaps();

    /**
        Waits for vertical synchronization.
        @return 0 if function succeeded.
    */
    virtual int waitForVSync();

    /**
         Enables VSync.
     */
    virtual void enableVSync();

    /**
         Disables VSync.
     */
    virtual void disableVSync();

    bool isExtensionSupported(std::string extension);
    void* getProcAddress(std::string name);

    /* Create functions */
    virtual Texture* createTexture(TextureFormat format, int width, int height
      , TextureFormat nativeformat, void* data = NULL, bool useMips = true);

    /**
        Creates VideoBuffer object of a given type. Type specifies what kind of
        data will be stored in this buffer.
        @param type - Array type to create.
        @return Pointer to a VideoBuffer object if operation succeeded.
        @return NULL if engine error occurred.
        @note VideoBuffers must be supported by GPU to create them.
        To check this run 'glxinfo | grep GL_ARB_vertex_buffer_object' in a console.
        If they are not supported, several errors of 'Not implemented' class will be place to
        the log file.
    */
    virtual VideoBuffer* createVideoBuffer(Array type);

    /**
        Creates VertexShader object.
        @return Pointer to a Shader object if operation succeeded.
        @return NULL if engine error occurred.
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
    virtual Shader* createVertexShader();

    /**
        Creates PixelShader object.
        @return Pointer to a Shader object if operation succeeded.
        @return NULL if engine error occurred.
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
    virtual Shader* createPixelShader();

    /**
        Creates program object. Program object is used to apply
        shader effects to any kind of geometry. It is an entity that
        consist of linked vertex of pixel shaders.
        @return Pointer to a Program object if operation succeeded.
        @return NULL if engine error occurred.
        @note Following extensions must be supported by GPU to create
        Program objects:
        <ul>
        <li>GL_ARB_shading_language_100</li>
        <li>GL_ARB_shader_objects</li>
        <li>GL_ARB_vertex_shader</li>
        <li>GL_ARB_fragment_shader</li>
        </ul>
        Use 'glxinfo' command to check support.
    */
    virtual Program* createProgram();

    /* Texture functions */
    virtual Outcome freeTexture(Texture *texture);
    virtual Outcome updateTexture(Texture* texture, TextureFormat nativeformat, void* data);
    virtual void* getTextureData(Texture *texture);

    /* Shader functions */
    virtual Outcome loadShaderSource(Shader *shader, char* source);
    virtual Outcome compileShader(Shader *shader);
    virtual Outcome isShaderCompiled(Shader *shader);
    virtual char* getShaderLog(Shader *shader);
    virtual Outcome freeShader(Shader *shader);

    /* Program functions */
    virtual Outcome setProgramVertexShader(Program *program, Shader *shader);
    virtual Outcome setProgramPixelShader(Program *program, Shader *shader);
    virtual Outcome linkProgram(Program *program);
    virtual Outcome isProgramLinked(Program *program);
    virtual char *getProgramLinkLog(Program *program);
    virtual Outcome freeProgram(Program *program);

    virtual Outcome setProgramVector(Program *program, string &param, const Vector4f &value);
    virtual Outcome setProgramVector(Program *program, string &param, const Vector3f &value);
    virtual Outcome setProgramVector(Program *program, string &param, const Vector2f &value);
    virtual Outcome setProgramFloat(Program *program, string &param, float value);
    virtual Outcome setProgramInt(Program *program, string &param, int value);
    virtual Outcome getProgramFloat(Program *program, string &param, float *value);
    virtual Outcome setProgramTexture(Program *program, string &param, int texture);

    /* Buffer functions */
    virtual Outcome updateBuffer(VideoBuffer* buffer, void *data, unsigned int size, VideoBufferStoreMethod method);
    virtual Outcome updateIndexBuffer(VideoBuffer* buffer, void *data, unsigned int size, VideoBufferStoreMethod method);
    virtual void* mapBuffer(VideoBuffer* buffer, AccessType access);
    virtual Outcome unmapBuffer(VideoBuffer *buffer);
    virtual void* mapIndexBuffer(VideoBuffer* buffer, AccessType access);
    virtual Outcome unmapIndexBuffer(VideoBuffer *buffer);
    virtual Outcome freeBuffer(VideoBuffer *buffer);

    /* Draw functions */
    virtual Outcome drawPrimitives(Topology topology, unsigned int first, unsigned int count);
    virtual Outcome drawIndexedPrimitives(Topology topology, unsigned int count, Type type, void *indices);

    /* Matrix functions */
    virtual Outcome enableMatrix(MatrixType type);
    virtual Outcome loadIdentityMatrix();
    virtual Outcome multPerspectiveMatrix(double fovy, double aspect, double zNear, double zFar);
    virtual Outcome multLookAtMatrix(Vector3f position, Vector3f lookAt, Vector3f up);

    /* Frame buffer functions */
    virtual FrameBuffer* createFrameBuffer();
    virtual Outcome freeFrameBuffer(FrameBuffer *frameBuffer);
    virtual Outcome bindFrameBuffer(FrameBuffer *frameBuffer);
    virtual Outcome unbindFrameBuffer();
    virtual RenderBuffer* createRenderBuffer(TextureFormat format, uint width, uint height);
    virtual Outcome freeRenderBuffer(RenderBuffer *renderBuffer);
    virtual Outcome attachRenderBuffer(FrameBuffer *frameBuffer, RenderBuffer *renderBuffer, RenderBufferSlot slot);
    virtual Outcome attachTexture(FrameBuffer *frameBuffer, Texture *texture2D, RenderBufferSlot slot);
    virtual FrameBufferStatus checkFrameBufferStatus();

    /* Other functions */
    virtual Outcome clear(ClearFlag flag);
    virtual uint getBatchesCount();
    virtual void onSwapBuffers();

    /* Transforms */
    virtual Outcome beginTransform();
    virtual Outcome translate(float x, float y, float z);
    virtual Outcome rotate(float angle, float x, float y, float z);
    virtual Outcome scale(float x, float y, float z);
    virtual Outcome endTransform();
  };

}

#endif // __VE_GLENGINE_H__
