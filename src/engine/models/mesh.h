// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_MESH_H__
#define __VE_MESH_H__

#include <vector>

#include "engine/common.h"
#include "engine/math/vector2f.h"
#include "engine/math/vector3f.h"
#include "engine/math/vector4f.h"
#include "engine/math/matrix4f.h"

namespace ve {

/**
    Represents mesh data. Consists of three main parts:
    <ul>
    <li>Array of vertex coordinates</li>
    <li>Array of texture coordinates</li>
    <li>Array of indices for rendering</li>
    </ul>
    All vertex coordinates are in the object-space, so also
    "Center" parameter is available. It defines where base of object's coordinate system is.
*/
class Mesh {
private:
  /** Center of object's local coordinate system */
  Vector3f center;

  /** Array of indices */
  std::vector<unsigned short> index;

  /** Array of vertex coordinates */
  std::vector<float> vertex;

  /** Array of texture coordinates */
  std::vector<float> texCoord;

public:
  /**
      Default constructor.
  */
  Mesh();

  /**
      Sets array of vertices for this mesh.
      @param count - Number of vertices to set.
      @param data - Array of Vector3f objects that specify point positions.
      @return OK everytime.
  */
  Outcome setVertexList(int count, Vector3f *data);

  /**
      Sets array of texture coordinates for this mesh.
      @param count - Number of points to set texture coordinates for.
      @param data - Array of Vector2f objects that specify point texture coordinates.
      @return OK everytime.
  */
  Outcome setTextureList(int count, Vector2f *data);

  /**
      Sets indices for this mesh.
      @param count - Number of indices to set for this mesh.
      @param data - Array of indices to set.
      @return OK everytime.
  */
  Outcome setFaceList(int count, unsigned short *data);

  /**
      Sets center of this mesh.
      @param center - Center of this mesh.
  */
  void setCenter(Vector3f center);

  /**
      Returns center of this mesh.
      @return Center of this mesh.
  */
  Vector3f getCenter();

  /**
      Returns vertex data.
      @return Array of float values, 3 per vertex.
  */
  std::vector<float> getVertexList();

  /**
      Returns texture coordinates data.
      @return Array of float values, 2 per vertex.
  */
  std::vector<float> getTextureCoordsList();

  /**
      Returns index data.
      @return Array of unsigned short values.
  */
  std::vector<unsigned short> getIndexList();

  /**
      Returns number of vertex in this mesh.
      @return number of vertex in this mesh.
  */
  uint getVertexCount();
};

}

#endif // __VE_MESH_H__
