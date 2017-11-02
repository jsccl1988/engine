// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_3DSLOADER_H__
#define __VE_3DSLOADER_H__

#include <string>

#include "engine/models/model.h"
#include "engine/loaders/loader.h"

namespace ve {

/* Primary chunk */

const unsigned MAIN3DS = 0x4D4D;

/* Main Chunks */

const unsigned EDIT3DS = 0x3D3D;  // this is the start of the editor config
const unsigned KEYF3DS = 0xB000;  // this is the start of the keyframer config

/* sub defines of EDIT3DS */

const unsigned EDIT_MATERIAL = 0xAFFF;
const unsigned EDIT_CONFIG1 = 0x0100;
const unsigned EDIT_CONFIG2 = 0x3E3D;
const unsigned EDIT_VIEW_P1 = 0x7012;
const unsigned EDIT_VIEW_P2 = 0x7011;
const unsigned EDIT_VIEW_P3 = 0x7020;
const unsigned EDIT_VIEW1 = 0x7001;
const unsigned EDIT_BACKGR = 0x1200;
const unsigned EDIT_AMBIENT = 0x2100;
const unsigned EDIT_OBJECT = 0x4000;

const unsigned EDIT_UNKNW01 = 0x1100;
const unsigned EDIT_UNKNW02 = 0x1201;
const unsigned EDIT_UNKNW03 = 0x1300;
const unsigned EDIT_UNKNW04 = 0x1400;
const unsigned EDIT_UNKNW05 = 0x1420;
const unsigned EDIT_UNKNW06 = 0x1450;
const unsigned EDIT_UNKNW07 = 0x1500;
const unsigned EDIT_UNKNW08 = 0x2200;
const unsigned EDIT_UNKNW09 = 0x2201;
const unsigned EDIT_UNKNW10 = 0x2210;
const unsigned EDIT_UNKNW11 = 0x2300;
const unsigned EDIT_UNKNW12 = 0x2302;
const unsigned EDIT_UNKNW13 = 0x3000;
const unsigned EDIT_UNKNW14 = 0xAFFF;

/* sub defines of EDIT_OBJECT */
const unsigned OBJ_TRIMESH = 0x4100;
const unsigned OBJ_LIGHT = 0x4600;
const unsigned OBJ_CAMERA = 0x4700;

const unsigned OBJ_UNKNWN01 = 0x4010;
const unsigned OBJ_UNKNWN02 = 0x4012; //>>---- Could be shadow

/* sub defines of OBJ_CAMERA */
const unsigned CAM_UNKNWN01 = 0x4710;
const unsigned CAM_UNKNWN02 = 0x4720;

/* sub defines of OBJ_LIGHT */
const unsigned LIT_OFF = 0x4620;
const unsigned LIT_SPOT = 0x4610;
const unsigned LIT_UNKNWN01 = 0x465A;

/* sub defines of OBJ_TRIMESH */
const unsigned TRI_RTEXL = 0x4110;
const unsigned TRI_FACEL2 = 0x4111;
const unsigned TRI_FACEL1 = 0x4120;
const unsigned TRI_TEXCOORD = 0x4140;
const unsigned TRI_SMOOTH = 0x4150;
const unsigned TRI_LOCAL = 0x4160;
const unsigned TRI_VISIBLE = 0x4165;

/* sub defs of KEYF3DS */

const unsigned KEYF_UNKNWN01 = 0xB009;
const unsigned KEYF_UNKNWN02 = 0xB00A;
const unsigned KEYF_FRAMES = 0xB008;
const unsigned KEYF_OBJDES = 0xB002;

/* these define the different color chunk types */
const unsigned COL_RGB = 0x0010;
const unsigned COL_TRU = 0x0011;
const unsigned COL_UNK = 0x0013;

/* defines for viewport chunks */

/*    const unsigned TOP           = 0x0001;
  const unsigned BOTTOM        = 0x0002;
  const unsigned LEFT          = 0x0003;
  const unsigned RIGHT         = 0x0004;
  const unsigned FRONT         = 0x0005;
  const unsigned BACK          = 0x0006;*/
const unsigned USER = 0x0007;
const unsigned CAMERA = 0x0008; // = 0xFFFF is the actual code read from file
const unsigned LIGHT = 0x0009;
const unsigned DISABLED = 0x0010;
const unsigned BOGUS = 0x0011;

#ifndef DOXYGEN

#pragma pack(push, 1)

struct _3dsChunk {
  unsigned short type;
  unsigned int length;
};

struct _3dsVertexList {
  unsigned short count;
};

struct _3dsVertex {
  float x;
  float y;
  float z;
};

struct _3dsFaceList {
  unsigned short count;
};

struct _3dsFace {
  unsigned short a;
  unsigned short b;
  unsigned short c;
  unsigned short flags;
};

struct _3dsLocalAxis {
  float xAxisX;
  float yAxisX;
  float zAxisX;
  float xAxisY;
  float yAxisY;
  float zAxisY;
  float xAxisZ;
  float yAxisZ;
  float zAxisZ;
  float xCenter;
  float yCenter;
  float zCenter;
};

struct _3dsLight {
  float x;
  float y;
  float z;
};

struct _3dsRGB {
  unsigned char r;
  unsigned char g;
  unsigned char b;
};

struct _3dsTrueColor {
  float r;
  float g;
  float b;
};

struct _3dsSpot {
  float targetX;
  float targetY;
  float targetZ;
  float hotspot;
  float falloff;
};

struct _3dsCamera {
  float x;
  float y;
  float z;
  float targetX;
  float targetY;
  float targetZ;
  float bank;
  float lens;
};

struct _3dsTexCoord {
  float u;
  float v;
};

#pragma pack(pop)

#endif // DOXYGEN

/**
    Class for loading 3ds static models.
*/
class _3dsLoader : public Loader {
private:
  std::vector<Mesh*> meshList;

  /**
      Reads string from the 3ds file which is processed now.
      @param source - file which is processed.
      @param name - string which was read will be place in this param.
      @return OK if name was read.
      @return ERROR if error occurred.
  */
  Outcome readName(FILE *source, std::string &name);

  /**
      Reads Mesh object section from the 3ds file which is processed now.
      @param source - file which is processed.
      @param length - length in bytes of this section.
      @return OK if mesh data was read.
      @return ERROR if error occurred.
  */
  Outcome readMesh(FILE *source, unsigned length);

  /**
      Reads Light section from the 3ds file which is processed now.
      @param source - file which is processed.
      @param length - length in bytes of this section.
      @return OK if light section was read.
      @return ERROR if error occurred.
  */
  Outcome readLight(FILE *source, unsigned length);

  /**
      Reads Camera section from the 3ds file which is processed now.
      @param source - file which is processed.
      @param length - length in bytes of this section.
      @return OK if camera data was read.
      @return ERROR if error occurred.
  */
  Outcome readCamera(FILE *source, unsigned length);

  /**
      Reads Object section from the 3ds file which is processed now.
      @param source - file which is processed.
      @param length - length in bytes of this section.
      @return OK if object section was read.
      @return ERROR if error occurred.
  */
  Outcome readObject(FILE *source, unsigned length);

  /**
      Free memory which was allocated for meshes.
      @return OK everytime.
  */
  Outcome freeMeshList();

public:
  /**
      Simple constructor.
  */
  _3dsLoader();

  /**
      Loads 3ds file from specified file starting from specified offset in bytes.
      Offset is usually 0, if 3ds file is read, for example. But for files which are
      contained in some archive-style file it may be useful to use offset param.
      @param source - File to read data from.
      @param offset - Offset in bytes where 3ds file starts.
      @return OK if 3ds image was read successfully.
      @return non-OK in case of engine error.
  */
  virtual Outcome load(FILE* source, size_t offset);

  /**
      Returns the list of loaded mesh objects. It contains data which was read since the last
      load() function call.
      @return List of loaded mesh objects.
  */
  std::vector<Mesh*> getMeshList();
};

}

#endif // __VE_3DSLOADER_H__
