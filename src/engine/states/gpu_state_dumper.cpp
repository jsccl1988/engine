// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "io/text_writer.h"
#include "states/gpu_state_dumper.h"

namespace ve {

/* Indexes of map tables for different constants */
const static int COMPARISON_TABLE = 0;
const static int TEXTURE_FILTER_TABLE = 1;
const static int TEXTURE_COORD_WRAP_MODE_TABLE = 2;
const static int TEXTURE_ENVIRONMENT_TABLE = 3;
const static int FACE_TABLE = 4;
const static int POLYGON_MODE_TABLE = 5;
const static int BLEND_FACTOR_TABLE = 6;

const static char* g_ComparisonTable[] = { "GL_LESS", "GL_LEQUAL", "GL_GREATER", "GL_GEQUAL", "GL_EQUAL" };

const static char* g_TextureFilterTable[] =
{ "GL_NEAREST", "GL_LINEAR", "GL_NEAREST_MIPMAP_NEAREST", "GL_LINEAR_MIPMAP_NEAREST",
  "GL_NEAREST_MIPMAP_LINEAR", "GL_LINEAR_MIPMAP_LINEAR"
};

const static char* g_TextureCoordWrapModeTable[] = { "GL_CLAMP", "GL_REPEAT", "GL_CLAMP_TO_EDGE" };

const static char* g_TextureEnvironmentTable[] = { "GL_REPLACE", "GL_MODULATE", "GL_DECAL", "GL_BLEND", "GL_ADD" };

const static char* g_FaceTable[] = { "GL_BACK", "GL_FRONT", "GL_FRONT_AND_BACK" };

const static char* g_PolygonModeTable[] = { "GL_POINT", "GL_LINE", "GL_FILL" };

const static char* g_BlendFactorTable[] =
{
    "GL_ZERO", "GL_ONE", "GL_SRC_COLOR", "GL_DST_COLOR",
    "GL_ONE_MINUS_DST_COLOR", "GL_SRC_ALPHA", "GL_ONE_MINUS_SRC_ALPHA",
    "GL_DST_ALPHA", "GL_ONE_MINUS_DST_ALPHA", "GL_SRC_ALPHA_SATURATE"
};

const static char** g_EngineToStrMap[] =
{
    g_ComparisonTable,
    g_TextureFilterTable,
    g_TextureCoordWrapModeTable,
    g_TextureEnvironmentTable,
    g_FaceTable,
    g_PolygonModeTable,
    g_BlendFactorTable
};

const static int g_TableSize[] =
{
    sizeof(g_ComparisonTable) / sizeof(int),
    sizeof(g_TextureFilterTable) / sizeof(int),
    sizeof(g_TextureCoordWrapModeTable) / sizeof(int),
    sizeof(g_TextureEnvironmentTable) / sizeof(int),
    sizeof(g_FaceTable) / sizeof(int),
    sizeof(g_PolygonModeTable) / sizeof(int),
    sizeof(g_BlendFactorTable) / sizeof(int)
};

const static int g_TablesCount = sizeof(g_EngineToStrMap) / sizeof(int*);

/**
    Default constructor. Do nothing.
*/
GPUStateDumper::GPUStateDumper() {
}

/**
    Converts Engine's enum to string that shows corresponding OpenGL parameter.
    @param tableIndex - Table to look constant at.
    @param value - Engine's enum constant.
    @return OpenGL's constant in a string.
*/
std::string GPUStateDumper::convertToGLString(uint tableIndex, uint value) {
  ERROR_IF(tableIndex >= g_TablesCount, L"Unknown table", "ERROR");
  ERROR_IF(value >= (uint)g_TableSize[tableIndex], L"Unnown value", "ERROR");
  return g_EngineToStrMap[tableIndex][value];
}

/**
    Writes header of the HTML file.
    @param writer - TextWriter to send data into.
    @return OK if operation succeeded.
    @return non-OK if fails.
*/
Outcome GPUStateDumper::dumpHeader(TextWriter *writer) {
  writer->printf("<html><head><title>GPU State Dump</title></head><body>");
  return OK;
}

/**
    Writes HTML tags for viewport state.
    @param viewportState - Viewport state to dump.
    @param writer - TextWriter to send data into.
    @return OK if operation succeeded.
    @return non-OK if fails.
*/
Outcome GPUStateDumper::dumpViewportState(ViewportState &viewportState, TextWriter *writer) {
  writer->printf("<table border=\"1\" width=\"200\">");
  writer->printf("<tr><td colspan=\"2\" bgcolor=#AAAAAA align=\"center\">Viewport</td>");
  writer->printf("<tr><td>X</td><td align=\"center\">%d</td></tr>", viewportState.x);
  writer->printf("<tr><td>Y</td><td align=\"center\">%d</td></tr>", viewportState.y);
  writer->printf("<tr><td>Width</td><td align=\"center\">%d</td></tr>", viewportState.width);
  writer->printf("<tr><td>Height</td><td align=\"center\">%d</td></tr>", viewportState.height);
  writer->printf("</table>");
  return OK;
}

/**
    Writes HTML tags for blend stage state.
    @param blendState - Blend stage state to dump.
    @param writer - TextWriter to send data into.
    @return OK if operation succeeded.
    @return non-OK if fails.
*/
Outcome GPUStateDumper::dumpBlendState(BlendState &blendState, TextWriter *writer) {
  writer->printf("<table border=\"1\" width=\"200\">");
  writer->printf("<tr><td colspan=\"2\" bgcolor=#AAAAAA align=\"center\">Blend stage</td>");
  writer->printf("<tr><td>Enabled</td><td align=\"center\">%s</td></tr>", (blendState.isEnabled) ? "Yes" : "No");
  writer->printf("<tr><td>Src factor</td><td align=\"center\">%s</td></tr>", convertToGLString(BLEND_FACTOR_TABLE, blendState.sourceFactor).c_str());
  writer->printf("<tr><td>Dst factor</td><td align=\"center\">%s</td></tr>", convertToGLString(BLEND_FACTOR_TABLE, blendState.destFactor).c_str());
  writer->printf("</table>");
  return OK;
}

/**
    Writes HTML tags for color state.
    @param colorState - Color state to dump.
    @param writer - TextWriter to send data into.
    @return OK if operation succeeded.
    @return non-OK if fails.
*/
Outcome GPUStateDumper::dumpColorState(ColorState &colorState, TextWriter *writer) {
  writer->printf("<table border=\"1\" width=\"200\">");
  writer->printf("<tr><td colspan=\"2\" bgcolor=#AAAAAA align=\"center\">Color</td>");
  writer->printf("<tr><td>Red</td><td align=\"center\">%.2f</td></tr>", colorState.r);
  writer->printf("<tr><td>Green</td><td align=\"center\">%.2f</td></tr>", colorState.g);
  writer->printf("<tr><td>Blue</td><td align=\"center\">%.2f</td></tr>", colorState.b);
  writer->printf("<tr><td>Alpha</td><td align=\"center\">%.2f</td></tr>", colorState.a);
  writer->printf("</table>");

  return OK;
}

/**
    Writes HTML tags for alpha test state.
    @param alphaTestState - Alpha test state to dump.
    @param writer - TextWriter to send data into.
    @return OK if operation succeeded.
    @return non-OK if fails.
*/
Outcome GPUStateDumper::dumpAlphaTestState(AlphaTestState &alphaTestState, TextWriter *writer) {
  writer->printf("<table border=\"1\" width=\"200\">");
  writer->printf("<tr><td colspan=\"2\" bgcolor=#AAAAAA align=\"center\">Alpha Test</td>");
  writer->printf("<tr><td>Enabled</td><td align=\"center\">%s</td></tr>", alphaTestState.isEnabled ? "Yes" : "No");
  writer->printf("<tr><td>Function</td><td align=\"center\">%s</td></tr>", convertToGLString(COMPARISON_TABLE, alphaTestState.func).c_str());
  writer->printf("<tr><td>Ref value</td><td align=\"center\">%.2f</td></tr>", alphaTestState.refValue);
  writer->printf("</table>");

  return OK;
}

/**
    Writes HTML tags for depth test state.
    @param depthTestState - Depth test state to dump.
    @param writer - TextWriter to send data into.
    @return OK if operation succeeded.
    @return non-OK if fails.
*/
Outcome GPUStateDumper::dumpDepthTestState(DepthTestState &depthTestState, TextWriter *writer) {
  writer->printf("<table border=\"1\" width=\"200\">");
  writer->printf("<tr><td colspan=\"2\" bgcolor=#AAAAAA align=\"center\">Depth Test</td></tr>");
  writer->printf("<tr><td>Enabled</td><td align=\"center\">%s</td></tr>", depthTestState.isEnabled ? "Yes" : "No");
  writer->printf("<tr><td>Function</td><td align=\"center\">%s</td></tr>", convertToGLString(COMPARISON_TABLE, depthTestState.func).c_str());
  writer->printf("</table>");

  return OK;
}

/**
    Writes HTML tags for matrix state.
    @param matrixState - Matrix state state to dump.
    @param writer - TextWriter to send data into.
    @return OK if operation succeeded.
    @return non-OK if fails.
*/
Outcome GPUStateDumper::dumpMatrixState(MatrixState &matrixState, TextWriter *writer) {
  writer->printf("<table border=\"1\" width=\"200\">");
  writer->printf("<tr><td colspan=\"4\" bgcolor=#AAAAAA align=\"center\">ModelView</td><td colspan=\"4\" bgcolor=#AAAAAA align=\"center\">Projection</td></tr>");
  for (int row = 0; row < 4; row++) {
    writer->printf("<tr>");
    for (int col = 0; col < 4; col++) {
      writer->printf("<td>%.3f</td>", matrixState.worldView[row][col]);
    }

    for (int col = 0; col < 4; col++) {
      writer->printf("<td>%.3f</td>", matrixState.projection[row][col]);
    }
    writer->printf("</tr>");
  }
  writer->printf("</table>");
  return OK;
}

/**
    Writes footer of the HTML file.
    @param writer - TextWriter to send data into.
    @return OK if operation succeeded.
    @return non-OK if fails.
*/
Outcome GPUStateDumper::dumpFooter(TextWriter *writer) {
  writer->printf("</body></html>");
  return OK;
}

/**
    Dumps state into HTML format and send it to the output stream.
    @param state - GPU state to dump
    @param stream - output stream to send textual info to.
    @return OK - state was successfully dumped.
    @return non-OK if I/O error occurred.
*/
Outcome GPUStateDumper::dumpState(GPUState *state, OutputStream *stream) {
  TextWriter *writer = new TextWriter(stream);
  CHECK_POINTER(writer);

  ASSERT(dumpHeader(writer));
  ASSERT(dumpViewportState(state->viewportState, writer));
  writer->printf("<br>");
  ASSERT(dumpBlendState(state->blendState, writer));
  writer->printf("<br>");
  ASSERT(dumpColorState(state->colorState, writer));
  writer->printf("<br>");
  ASSERT(dumpAlphaTestState(state->alphaTestState, writer));
  writer->printf("<br>");
  ASSERT(dumpDepthTestState(state->depthTestState, writer));
  writer->printf("<br>");
  ASSERT(dumpMatrixState(state->matrixState, writer));
  ASSERT(dumpFooter(writer));

  writer->flush();
  delete writer;
  return OK;
}

}
