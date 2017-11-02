// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_GPU_STATE_DUMPER_H__
#define __VE_GPU_STATE_DUMPER_H__

#include "common.h"
#include "io/text_writer.h"
#include "states/gpu_state.h"

namespace ve {

/**
    Class for dumping GPU state into readbale HTML format and sends it via OutputStream class.
    Useful for debugging rendering problems.
*/
class GPUStateDumper {
protected:
  /**
      Converts Engine's enum to string that shows corresponding OpenGL parameter.
      @param tableIndex - Table to look constant at.
      @param value - Engine's enum constant.
      @return OpenGL's constant in a string.
  */
  std::string convertToGLString(uint tableIndex, uint value);

  /**
      Writes header of the HTML file.
      @param writer - TextWriter to send data into.
      @return OK if operation succeeded.
      @return non-OK if fails.
  */
  Outcome dumpHeader(TextWriter *writer);

  /**
      Writes HTML tags for viewport state.
      @param viewportState - Viewport state to dump.
      @param writer - TextWriter to send data into.
      @return OK if operation succeeded.
      @return non-OK if fails.
  */
  Outcome dumpViewportState(ViewportState &viewportState, TextWriter *writer);

  /**
      Writes HTML tags for blend stage state.
      @param blendState - Blend stage state to dump.
      @param writer - TextWriter to send data into.
      @return OK if operation succeeded.
      @return non-OK if fails.
  */
  Outcome dumpBlendState(BlendState &blendState, TextWriter *writer);

  /**
      Writes HTML tags for color state.
      @param colorState - Color state to dump.
      @param writer - TextWriter to send data into.
      @return OK if operation succeeded.
      @return non-OK if fails.
  */
  Outcome dumpColorState(ColorState &colorState, TextWriter *writer);

  /**
      Writes HTML tags for alpha test state.
      @param alphaTestState - Alpha test state to dump.
      @param writer - TextWriter to send data into.
      @return OK if operation succeeded.
      @return non-OK if fails.
  */
  Outcome dumpAlphaTestState(AlphaTestState &alphaTestState, TextWriter *writer);

  /**
      Writes HTML tags for depth test state.
      @param depthTestState - Depth test state to dump.
      @param writer - TextWriter to send data into.
      @return OK if operation succeeded.
      @return non-OK if fails.
  */
  Outcome dumpDepthTestState(DepthTestState &depthTestState, TextWriter *writer);

  /**
      Writes HTML tags for matrix state.
      @param matrixState - Matrix state state to dump.
      @param writer - TextWriter to send data into.
      @return OK if operation succeeded.
      @return non-OK if fails.
  */
  Outcome dumpMatrixState(MatrixState &matrixState, TextWriter *writer);

  /**
      Writes footer of the HTML file.
      @param writer - TextWriter to send data into.
      @return OK if operation succeeded.
      @return non-OK if fails.
  */
  Outcome dumpFooter(TextWriter *writer);

public:
  /**
      Default constructor. Do nothing.
  */
  GPUStateDumper();

  /**
      Dumps state into HTML format and send it to the output stream.
      @param state - GPU state to dump
      @param stream - output stream to send textual info to.
      @return OK - state was successfully dumped.
      @return non-OK if I/O error occurred.
  */
  virtual Outcome dumpState(GPUState *state, OutputStream *stream);
};

}

#endif // __VE_GPU_STATE_DUMPER_H__
