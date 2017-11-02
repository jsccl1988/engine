// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "models/mesh.h"

namespace ve {

Mesh::Mesh() {
}

Outcome Mesh::setVertexList(int count, Vector3f *data) {
  for (int i = 0; i < count; i++) {
    vertex.push_back(data[i][0]);
    vertex.push_back(data[i][1]);
    vertex.push_back(data[i][2]);
  }

  return OK;
}

Outcome Mesh::setTextureList(int count, Vector2f *data) {
  for (int i = 0; i < count; i++) {
    texCoord.push_back(data[i][0]);
    texCoord.push_back(data[i][1]);
  }

  return OK;
}

Outcome Mesh::setFaceList(int count, unsigned short *data) {
  for (int i = 0; i < 3 * count; i++) {
    index.push_back(data[i]);
  }

  return OK;
}

void Mesh::setCenter(Vector3f center) {
  this->center = center;
}

Vector3f Mesh::getCenter() {
  return center;
}

/**
    Returns vertex data.
    @return Array of float values, 3 per vertex.
*/
std::vector<float> Mesh::getVertexList() {
  return vertex;
}

/**
    Returns texture coordinates data.
    @return Array of float values, 2 per vertex.
*/
std::vector<float> Mesh::getTextureCoordsList() {
  return texCoord;
}

/**
    Returns index data.
    @return Array of unsigned short values.
*/
std::vector<unsigned short> Mesh::getIndexList() {
  return index;
}

/**
    Returns number of vertex in this mesh.
    @return number of vertex in this mesh.
*/
uint Mesh::getVertexCount() {
  return vertex.size();
}

}
