// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_TYPES_H__
#define __VE_TYPES_H__

namespace ve {
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;
typedef uint Handle;
typedef uint Message;

enum AccessType {
  READ_ONLY = 0,
  WRITE_ONLY,
  READ_WRITE
};

enum RenderBufferSlot {
  COLOR_ATTACHMENT0 = 0,
  COLOR_ATTACHMENT1,
  COLOR_ATTACHMENT2,
  COLOR_ATTACHMENT3,
  COLOR_ATTACHMENT4,
  COLOR_ATTACHMENT5,
  COLOR_ATTACHMENT6,
  COLOR_ATTACHMENT7,
  DEPTH_ATTACHMENT,
  STENCIL_ATTACHMENT
};

enum FrameBufferStatus {
  FRAMEBUFFER_COMPLETE = 0,
  FRAMEBUFFER_INCOMPLETE_ATTACHMENT,
  FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT,
  FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER,
  FRAMEBUFFER_INCOMPLETE_READ_BUFFER,
  FRAMEBUFFER_UNSUPPORTED
};

enum Topology {
  POINTS = 0,
  LINE_STRIP,
  LINE_LOOP,
  LINES,
  TRIANGLE_STRIP,
  TRIANGLE_FAN,
  TRIANGLES,
  QUAD_STRIP,
  QUADS,
  POLYGON
};

enum Comparison {
  LESS = 0,
  LEQUAL,
  GREATER,
  GEQUAL,
  EQUAL
};

enum Face {
  BACK = 0,
  FRONT,
  FRONT_AND_BACK
};

enum PolygonMode {
  POINT = 0,
  LINE,
  FILL
};

enum Type {
  SHORT = 0,
  INT,
  FLOAT,
  DOUBLE,
  UNSIGNED_INT,
  UNSIGNED_BYTE,
  UNSIGNED_SHORT
};

enum ClearFlag {
  COLOR = 1,
  DEPTH = 2,
  STENCIL = 4
};

enum MatrixType {
  PROJECTION = 0,
  MODELVIEW
};

enum BlendFactor {
  ZERO = 0,
  ONE,
  SRC_COLOR,
  DST_COLOR,
  ONE_MINUS_DST_COLOR,
  SRC_ALPHA,
  ONE_MINUS_SRC_ALPHA,
  DST_ALPHA,
  ONE_MINUS_DST_ALPHA,
  SRC_ALPHA_SATURATE
};

enum TextureEnvironment {
  REPLACE = 0,
  MODULATE,
  DECAL,
  BLEND,
  ADD
};

}

#endif // __VE_TYPES_H__
