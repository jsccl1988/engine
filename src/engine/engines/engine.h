// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_ENGINE_H__
#define __VE_ENGINE_H__

#include <vector>

#include "engine/math/vector2f.h"
#include "engine/math/vector3f.h"
#include "engine/math/vector4f.h"
#include "engine/math/matrix4f.h"

#include "engine/textures/texture.h"
#include "engine/shaders/shaders.h"
#include "engine/shaders/program.h"
#include "engine/buffers/video_buffer.h"
#include "engine/buffers/frame_buffer.h"
#include "engine/buffers/render_buffer.h"
#include "engine/ui/ui.h"
#include "engine/cameras/camera.h"
#include "engine/cameras/ortho_camera.h"
#include "engine/tools/memory_manager.h"
#include "engine/sprites/simple_sprite.h"
#include "engine/sprites/sprite.h"
#include "engine/sprites/animated_sprite.h"
#include "engine/sprites/movable_sprite.h"
#include "engine/io/file_output_stream.h"
#include "engine/states/gpu_state_manager.h"
#include "engine/engines/device_caps.h"

#include "engine/windows/window.h"

namespace ve {

/**
    Abstract engine class is the main class of the library. Only this class works directly with renderer layer
    to make it abstract for other library components like GUI, font, sprite system, etc. They use it
    as an abstract class that has render abilities. Engine class was implemented like
    "Facade" pattern for any rendering system to support engines differs from
    OpenGL.

    @note There are no a lot of comments for this class as well as for its implementations,
    good knowledge of graphics pipeline is needed to use this class directly. But if you
    have such knowledge it becomes obvious for you ;)
*/
class Engine {
protected:
  /**
      Log file stream is used to store all the errors/warnings in the application into the
      "eengine.log" file.
  */
  FileOutputStream *logFileStream;

public:
  /**
      Default constructor. Creates MemoryManager object to
      track allocated memory and opens log file.
  */
  Engine();

  /**
      Destructor. Destroys all the created by this class objects and closes log file.
  */
  virtual ~Engine();

  /**
      Initializes engine after its creation.
      @return OK if operation succeeded.
      @return NULL_POINTER if window pointer is NULL.
  */
  virtual Outcome initialize(Window *window) = 0;

  /**
      Returns state manager of this engine. It used to set/get any pipeline state.
  */
  virtual GPUStateManager* getStateManager() = 0;

  /**
      Returns device capabilities manager. It is used to check features support
      of retrieve GPU-specific constants like maximum level of anisotropy
      supported on this GPU.
      @return DeviceCaps object.
  */
  virtual DeviceCaps* getDeviceCaps() = 0;

  /**
      Waits for vertical synchronization.
      @return 0 if function succeeded.
  */
  virtual int waitForVSync() = 0;

  /**
        Enables VSync.
    */
  virtual void enableVSync() = 0;

  /**
        Disables VSync.
    */
  virtual void disableVSync() = 0;

  /**
      Creates texture object and fills it with a given color data.
      @param format - Format of the texture to create.
      @param width - Width of the texture.
      @param height - Height of the texture.
      @param nativeformat - Format of the data.
      @param data - Color data to fill texture. Size of this array depends on texture format.
      It equals ((width * height) * (number of components in format)) bytes.
      @param useMips - Flag that defines if MIP-levels autogeneration
      will be enabled for the texture.
      @return Pointer to a Texture object if operation suceeded.
      @return NULL if OpenGL's error occurred.
  */
  virtual Texture* createTexture(TextureFormat format, int width, int height
    , TextureFormat nativeformat, void* data = NULL, bool useMips = true) = 0;

  /**
      Creates VideoBuffer object of a given type. Type specifies what kind of
      data will be stored in this buffer.
      @param type - Array type to create.
      @return Pointer to a VideoBuffer object if operation succeeded.
      @return NULL if video buffers are unsupported by GPU.
  */
  virtual VideoBuffer* createVideoBuffer(Array type) = 0;

  /**
      Creates VertexShader object.
      @return Pointer to a Shader object if operation succeeded.
      @return NULL if shaders are unsupported.
  */
  virtual Shader* createVertexShader() = 0;

  /**
      Creates PixelShader object.
      @return Pointer to a Shader object if operation succeeded.
      @return NULL if shaders are unsupported.
  */
  virtual Shader* createPixelShader() = 0;

  /**
      Creates program object. Program object is used to apply
      shader effects to any kind of geometry. It is an entity that
      consist of linked vertex of pixel shaders.
      @return Pointer to a Program object if operation succeeded.
      @return NULL if shaders are unsupported.
  */
  virtual Program* createProgram() = 0;

  /**
      Frees GPU memory allocated by texture object.
      @param texture - Texture object to free its GPU allocated memory.
      @return OK if memory was freed.
      @return NULL_POINTER if texture pointer is NULL
      @return Other error codes if engine error occurred.
  */
  virtual Outcome freeTexture(Texture *texture) = 0;

  /**
      Updates color data for a texture.
      @param texture - Texture to updata its color data.
      @param data - array of color data to update. It should has
      the same format for pixels as texture has.
      @param nativeformat - Format of the data.
      @return OK if operation succeeded.
      @return non-OK if error occurred.
  */
  virtual Outcome updateTexture(Texture* texture, TextureFormat nativeformat, void* data) = 0;

  /**
      Retrieves texture data from GPU memory.
      @param texture - Texture object to get data from.
      @return Array of color data for the given texture.
      @return NULL if error occurred.
  */
  virtual void* getTextureData(Texture *texture) = 0;

  /**
      Loads source code to a shader object.
      @param shader - Shader object to load source in.
      @param source - NULL-terminated string that contains GLSL source code.
      @return OK if operation succeeded.
      @return NULL_POINTER if shader pointer is NULL
      @return non-OK if error occurred.
      @note Need shader support on GPU.
  */
  virtual Outcome loadShaderSource(Shader *shader, char* source) = 0;

  /**
      Compiles shader.
      @param shader - Shader to compile.
      @return OK if operation succeeded.
      @return NULL_POINTER if shader pointer is NULL
      @return non-OK if error occurred.
      @note Need shader support on GPU.
  */
  virtual Outcome compileShader(Shader *shader) = 0;

  /**
      Checks if shader was compiled successfully.
      @param shader - Shader to check its compilation status.
      @return OK if operation succeeded.
      @return NULL_POINTER if shader pointer is NULL
      @return non-OK if error occurred.
      @note Need shader support on GPU.
  */
  virtual Outcome isShaderCompiled(Shader *shader) = 0;

  /**
      Returns shader compilation log in case of compile errors.
      @param shader - Shader object to return compilation log for.
      @return NULL-terminated string that contains compilation log.
      @return NULL pointer if no compilation log available.
      @note Need shader support on GPU.
  */
  virtual char* getShaderLog(Shader *shader) = 0;

  /**
      Frees GPU memory allocated for a shader.
      @param shader - Shader to release its GPU memory.
      @return OK if operation succeeded.
      @return NULL_POINTER if shader pointer is NULL
      @return non-OK if error occurred.
  */
  virtual Outcome freeShader(Shader *shader) = 0;

  /**
      Attachs vertex shader to a program.
      @param program - Shader program to set vertex shader for.
      @param shader - Vertex shader to attach to the program.
      @return OK if operation succeeded.
      @return NULL_POINTER if program or shader pointer is NULL
      @return non-OK if error occurred.
  */
  virtual Outcome setProgramVertexShader(Program *program, Shader *shader) = 0;

  /**
      Attachs pixel shader to a program.
      @param program - Shader program to set pixel shader for.
      @param shader - Pixel shader to attach to the program.
      @return OK if operation succeeded.
      @return NULL_POINTER if program or shader pointer is NULL
      @return non-OK if error occurred.
  */
  virtual Outcome setProgramPixelShader(Program *program, Shader *shader) = 0;

  /**
      Links vertex and pixel shaders in a program. They should be set
      before this function call.
      @param program - Shader program to link.
      @return OK if operation succeeded.
      @return NULL_POINTER if program or shader pointer is NULL
      @return non-OK if error occurred.
  */
  virtual Outcome linkProgram(Program *program) = 0;

  /**
      Checks if program was successfully linked.
      @param program - Shader program to check linking status.
      @return OK if no errors occurred during linking process.
      @return NULL_POINTER if program pointer is NULL.
      @return non-OK if there were errors during linking.
  */
  virtual Outcome isProgramLinked(Program *program) = 0;

  /**
      Returns linking log for a linked program.
      @param program - Program to get linker log for.
      @return NULL_terminated string that contains linker log.
      @return NULL if no log available.
  */
  virtual char *getProgramLinkLog(Program *program) = 0;

  /**
      Releases GPU resources allocated for a program.
      @param program - Shader program to release its GPU resources.
      @return OK if operation succeeded.
      @return NULL_POINTER if program pointer is NULL.
  */
  virtual Outcome freeProgram(Program *program) = 0;

  /**
      Sets value for 4-components vector defined in a shader source code.
      @param program - Shader program to set vector variable in.
      @param param - Text name of vector variable inside shader source code.
      @param value - Value to set into the variable.
      @return OK if operation succeeded.
      @return NULL_POINTER if program pointer is NULL.
      @return ERROR if no vector variable with the given name was found in
      the shaders source code.
  */
  virtual Outcome setProgramVector(Program *program, string &param, const Vector4f &value) = 0;

  /**
      Sets value for 3-components vector defined in a shader source code.
      @param program - Shader program to set vector variable in.
      @param param - Text name of vector variable inside shader source code.
      @param value - Value to set into the variable.
      @return OK if operation succeeded.
      @return NULL_POINTER if program pointer is NULL.
      @return ERROR if no vector variable with the given name was found in
      the shaders source code.
  */
  virtual Outcome setProgramVector(Program *program, string &param, const Vector3f &value) = 0;

  /**
      Sets value for 2-components vector defined in a shader source code.
      @param program - Shader program to set vector variable in.
      @param param - Text name of vector variable inside shader source code.
      @param value - Value to set into the variable.
      @return OK if operation succeeded.
      @return NULL_POINTER if program pointer is NULL.
      @return ERROR if no vector variable with the given name was found in
      the shaders source code.
  */
  virtual Outcome setProgramVector(Program *program, string &param, const Vector2f &value) = 0;

  /**
      Sets value for float variable defined in a shader source code.
      @param program - Shader program to set float variable in.
      @param param - Text name of float variable inside shader source code.
      @param value - Value to set into the variable.
      @return OK if operation succeeded.
      @return NULL_POINTER if program pointer is NULL.
      @return ERROR if no float variable with the given name was found in
      the shaders source code.
  */
  virtual Outcome setProgramFloat(Program *program, string &param, float value) = 0;

  /**
      Sets value for integer variable defined in a shader source code.
      @param program - Shader program to set integer variable in.
      @param param - Text name of integer variable inside shader source code.
      @param value - Value to set into the variable.
      @return OK if operation succeeded.
      @return NULL_POINTER if program pointer is NULL.
      @return ERROR if no integer variable with the given name was found in
      the shaders source code.
  */
  virtual Outcome setProgramInt(Program *program, string &param, int value) = 0;

  /**
      Returns value for float variable defined in a shader source code.
      @param program - Shader program to get float variable value from.
      @param param - Text name of float variable inside shader source code.
      @param value - Returned value of the variable.
      @return OK if operation succeeded.
      @return NULL_POINTER if program pointer is NULL.
      @return ERROR if no float variable with the given name was found in
      the shaders source code.
  */
  virtual Outcome getProgramFloat(Program *program, string &param, float *value) = 0;

  /**
      Sets texture variable defined in a shader source code.
      @param program - Shader program to set texture variable in.
      @param param - Text name of texture variable inside shader source code.
      @param texture - Texture slot to set into this variable.
      @return OK if operation succeeded.
      @return NULL_POINTER if program pointer is NULL.
      @return ERROR if no texture variable with the given name was found in
      the shaders source code.
  */
  virtual Outcome setProgramTexture(Program *program, string &param, int texture) = 0;

  /**
      Populates video buffer with data.
      @param buffer - Video buffer to fill.
      @param data - Pointer to data to load to the buffer.
      @param size - Number of bytes to load from 'data' array.
      @param method - Video buffer storing method. Depends on
      this buffer usage in the program.
      @return OK if operation succeeded.
      @return NULL_POINTER if buffer pointer is NULL.
      @return non-OK in case of wrong parameters.
  */
  virtual Outcome updateBuffer(VideoBuffer* buffer, void *data, uint size, VideoBufferStoreMethod method) = 0;

  /**
      Populates video buffer with indices.
      @param buffer - Video buffer to fill.
      @param data - Pointer to data to load to the buffer.
      @param size - Number of bytes to load from 'data' array.
      @param method - Video buffer storing method. Depends on
      this buffer usage in the program.
      @return OK if operation succeeded.
      @return NULL_POINTER if buffer pointer is NULL.
      @return non-OK in case of wrong parameters.
  */
  virtual Outcome updateIndexBuffer(VideoBuffer* buffer, void *data, uint size, VideoBufferStoreMethod method) = 0;

  /**
      Maps video buffer data to the system memory.
      @param buffer - Video buffer to map.
      @param access - Access flag that defines usage of the mapped content.
      @return Pointer to mapped data.
      @return NULL if mapping failed.
  */
  virtual void* mapBuffer(VideoBuffer* buffer, AccessType access) = 0;

  /**
      Unmaps video buffer data.
      @param buffer - Video buffer to unmap.
      @return OK if operation succeeded.
      @return non-OK in case of OpenGL error.
  */
  virtual Outcome unmapBuffer(VideoBuffer *buffer) = 0;

  /**
      Maps video buffer that contains indexes to the system memory.
      @param buffer - Video buffer to map.
      @param access - Access flag that defines usage of the mapped content.
      @return Pointer to mapped data.
      @return NULL if mapping failed.
  */
  virtual void* mapIndexBuffer(VideoBuffer* buffer, AccessType access) = 0;

  /**
      Unmaps video buffer that contains indices.
      @param buffer - Video buffer to unmap.
      @return OK if operation succeeded.
      @return non-OK in case of renderer error.
  */
  virtual Outcome unmapIndexBuffer(VideoBuffer *buffer) = 0;

  /**
      Releases GPU resources allocated for a video buffer.
      @param buffer - Video buffer to release its GPU resources.
      @return OK everytime.
  */
  virtual Outcome freeBuffer(VideoBuffer *buffer) = 0;

  /**
      Draws geometry using buffers set before this call.
      @param topology - Kind of primitives to construct from vertex array.
      @param first - Vertex to start render from.
      @param count - Number of vertices to render.
      @return OK if operation succeeded.
      @return non-OK in case of renderer error.
  */
  virtual Outcome drawPrimitives(Topology topology, uint first, uint count) = 0;

  /**
      Draws indexed geometry using buffers set before this call.
      @param topology - Kind of primitives to construct from vertex array.
      @param count - Number of vertices to render.
      @param type - Type od indices.
      @param indices - Buffer to load indices from or 0 if VBO is used.
      @return OK if operation succeeded.
      @return non-OK in case of renderer error.
  */
  virtual Outcome drawIndexedPrimitives(Topology topology, uint count, Type type, void *indices) = 0;

  /**
      Activates stack of specified matrices. Functions that changes
      current matrix will be applied to a matrix from this stack.
      @param type - Matrix type to activate.
      @return OK if operation succeeded.
      @return non-OK in case of renderer error.
  */
  virtual Outcome enableMatrix(MatrixType type) = 0;

  /**
      Loads identity matrix in a current matrix.
      @return OK if operation succeeded.
      @return non-OK in case of renderer error.
  */
  virtual Outcome loadIdentityMatrix() = 0;

  /**
      Multiplies current matrix at perspective correction
      matrix defined by projection properties.
      @param fovy - Specifies the field of view angle (in degrees) in the y direction.
      @param aspect - Indicates the aspect ratio. This value determines
      the field of view in the x direction and is the ratio of x (width) to y (height).
      @param zNear Specifies the distance from the viewer to the closest clipping plane.
      This value must be positive.
      @param zFar  Specifies the distance from the viewer to the farthest clipping plane.
      This value must be positive.
      @return OK if operation succeeded.
      @return non-OK in case of renderer error.
      @see OpenGL's gluPerspective() function for details.
  */
  virtual Outcome multPerspectiveMatrix(double fovy, double aspect, double zNear, double zFar) = 0;

  /**
      @see OpenGL's gluLookAt() function for details.
  */
  virtual Outcome multLookAtMatrix(Vector3f position, Vector3f lookAt, Vector3f up) = 0;

  /**
      Creates FrameBuffer object.
      @return Pointer to a FrameBuffer object.
      @return NULL if frame buffer objects are not supported by GPU.
  */
  virtual FrameBuffer* createFrameBuffer() = 0;

  /**
      Releases GPU resources allocated by frame buffer object.
      @param frameBuffer - Frame buffer object to free its GPU resources.
      @return OK if operation succeeded.
      @return NULL_POINTER if frame buffer pointer is NULL.
      @return ERROR if frame buffer was not created by this engine.
  */
  virtual Outcome freeFrameBuffer(FrameBuffer *frameBuffer) = 0;

  /**
      Binds a frame buffer to the pipeline.
      @param frameBuffer - Frame buffer to bind.
      @return OK if operation succeeded.
      @return ERROR if renderer error occurred.
  */
  virtual Outcome bindFrameBuffer(FrameBuffer *frameBuffer) = 0;

  /**
      Restores default frame buffer.
      @return OK if operation succeeded.
      @return ERROR if renderer error occurred.
  */
  virtual Outcome unbindFrameBuffer() = 0;

  /**
      Creates RenderBuffer object.
      @param format - Render buffer format to create.
      @param width - Width of render buffer.
      @param height - Height of render buffer.
      @return Pointer to a RenderBuffer object.
      @return NULL if render buffer with these properties is unsupported.
  */
  virtual RenderBuffer* createRenderBuffer(TextureFormat format, uint width, uint height) = 0;

  /**
      Frees GPU resources that were allocated for RenderBuffer object
      @param renderBuffer - buffer to release its resources
      @return OK if operation succeeded.
      @return ERROR in case of renderer error.
  */
  virtual Outcome freeRenderBuffer(RenderBuffer *renderBuffer) = 0;

  virtual Outcome attachRenderBuffer(FrameBuffer *frameBuffer, RenderBuffer *renderBuffer, RenderBufferSlot slot) = 0;
  virtual Outcome attachTexture(FrameBuffer *frameBuffer, Texture *texture2D, RenderBufferSlot slot) = 0;
  virtual FrameBufferStatus checkFrameBufferStatus() = 0;

  /**
      Clears buffers that are defined in flag parameter. Typically they are color and
      depth buffers.
      @param flag - Flag that defines buffers to clear.
      @return OK if operation succeeded.
      @return ERROR if error occurred in renderer.
  */
  virtual Outcome clear(ClearFlag flag) = 0;

  /**
      Pushes current transformation matrix into the stack.
      @return OK everytime.
  */
  virtual Outcome beginTransform() = 0;

  /**
      Applies translate matrix to the current matrix.
      @param x - Translation along X-axis.
      @param y - Translation along Y-axis.
      @param z - Translation along Z-axis.
      @return OK if operation succeeded.
      @return ERROR if error occurred in renderer.
  */
  virtual Outcome translate(float x, float y, float z) = 0;

  /**
      Computes a matrix that performs a counterclockwise rotation of Angle degrees
      about the vector from the origin through the point (X, Y, Z).
      The current matrix is multiplied by this rotation matrix, with the product replacing the current matrix.
      @param angle - Angle (in degrees) to rotate.
      @param x - X component of the vector.
      @param y - Y component of the vector.
      @param z - Z component of the vector.
      @return OK if operation succeeded.
      @return ERROR if error occurred in renderer.
  */
  virtual Outcome rotate(float angle, float x, float y, float z) = 0;

  /**
      Produces a general scaling along the X, Y, and Z axes. The three arguments
      indicate the desired scale factors along each of the three axes.
      @param x - factor to scale along the X axis.
      @param y - factor to scale along the Y axis.
      @param z - factor to scale along the Z axis.
      @return OK if operation succeeded.
      @return ERROR if error occurred in renderer.
  */
  virtual Outcome scale(float x, float y, float z) = 0;

  /**
      Pops transformation matrix from the stack and to replace the current.
      @return OK if operation succeeded.
      @return ERROR if error occurred in renderer.
  */
  virtual Outcome endTransform() = 0;

  /**
      Returns number of color components in texture format.
      @note Should be moved out of here.
      @param format - Texture format to get number of components for.
      @return Number of color components in texture format.
  */
  int getComponents(TextureFormat format);

  /**
    Returns number of batches processed in the current frame.
    @return Number of batches processed in the current frame.
  */
  virtual uint getBatchesCount() = 0;

  /**
    Callback that is called by WindowSystem when it swaps frame buffers.
  */
  virtual void onSwapBuffers() = 0;
};

}

#endif // __VE_ENGINE_H__
