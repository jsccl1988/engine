// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "models/model.h"
#include "engines/engine.h"
#include "math/maths.h"

namespace ve {

Model::Model(Engine *engine) {
  this->engine = engine;
  indexVBO = 0;
  vertexVBO = 0;
  textureVBO = 0;
  normalVBO = 0;
}

Outcome Model::renderMesh(uint index) {
  ERROR_IF(index >= meshInfoList.size(), L"Index is out of bounds", ERROR);
  MeshInfo info = meshInfoList[index];

  GPUStateManager *stateManager = engine->getStateManager();

  stateManager->pushStates(BUFFERS_STATE);
  stateManager->setBuffersState(buffersState);
  CHECK_RESULT(engine->drawIndexedPrimitives(TRIANGLES, info.count, UNSIGNED_SHORT, (void*)info.start), L"Draw failed");
  stateManager->popStates(BUFFERS_STATE);

  return OK;
}

Outcome Model::generateNormalMap(std::vector<unsigned short> indices, std::vector<float> vertices, std::vector<float> &normals) {
  int i, j, k, len = indices.size() / 3;
  Vector3f vec1, vec2, norm;
  std::vector<int> normalCount;

  normals.resize(vertices.size());
  normalCount.resize(vertices.size() / 3);

  for (i = 0; i < len; i++) {
    for (j = 0; j < 3; j++)
      vec1[j] = vertices[3 * indices[3 * i + 1] + j] - vertices[3 * indices[3 * i] + j];
    for (j = 0; j < 3; j++)
      vec2[j] = vertices[3 * indices[3 * i + 2] + j] - vertices[3 * indices[3 * i + 1] + j];

    norm = Maths::cross(vec1, vec2);

    for (k = 0; k < 3; k++) {
      for (j = 0; j < 3; j++)
        normals[3 * indices[3 * i + k] + j] = (normals[3 * indices[3 * i + k] + j] * normalCount[indices[3 * i + k]] + norm[j]) / (float)(normalCount[indices[3 * i + k]] + 1);

      normalCount[indices[3 * i + k]]++;
    }
  }

  len = normals.size() / 3;
  for (i = 0; i < len; i++) {
    norm.set(normals[3 * i], normals[3 * i + 1], normals[3 * i + 2]);
    norm.norm();
    normals[3 * i] = norm[0];
    normals[3 * i + 1] = norm[1];
    normals[3 * i + 2] = norm[2];
  }

  return OK;
}

Outcome Model::update(std::vector<Mesh*> meshList) {
  int len = meshList.size();
  std::vector<float> vertices;
  std::vector<unsigned short> indices;
  std::vector<float> texCoords;
  std::vector<float> normals;
  int indexOffset = 0;

  this->meshList.clear();

  for (int i = 0; i < len; i++) {
    this->meshList.push_back(*meshList[i]);

    ERROR_IF(meshList[i]->getVertexCount() == 0, L"Empty vertex set", ERROR);
  }

  for (int i = 0; i < len; i++) {
    std::vector<unsigned short> meshIndex = meshList[i]->getIndexList();
    std::vector<float> meshVertex = meshList[i]->getVertexList();
    std::vector<float> meshTexCoords = meshList[i]->getTextureCoordsList();

    indexOffset = vertices.size() / 3;
    for (uint j = 0; j < meshIndex.size(); j++) {
      indices.push_back(indexOffset + meshIndex[j]);
    }

    meshInfoList.push_back(MeshInfo(indexOffset, meshIndex.size()));
    vertices.insert(vertices.end(), meshVertex.begin(), meshVertex.end());
    texCoords.insert(texCoords.end(), meshTexCoords.begin(), meshTexCoords.end());
  }

  GPUStateManager *stateManager = engine->getStateManager();
  stateManager->pushStates(BUFFERS_STATE);

  CHECK_POINTER(vertexVBO = engine->createVideoBuffer(VERTEX_ARRAY));
  CHECK_POINTER(indexVBO = engine->createVideoBuffer(INDEX_ARRAY));
  CHECK_POINTER(textureVBO = engine->createVideoBuffer(TEXTURE_COORD_ARRAY));
  CHECK_POINTER(normalVBO = engine->createVideoBuffer(NORMAL_ARRAY));

  ASSERT(vertexVBO->update(&vertices[0], sizeof(float) * vertices.size(), STATIC_DRAW));
  ASSERT(indexVBO->update(&indices[0], sizeof(short) * indices.size(), STATIC_DRAW));
  ASSERT(textureVBO->update(&texCoords[0], sizeof(float) * texCoords.size(), STATIC_DRAW));

  normals.resize(vertices.size());
  ASSERT(generateNormalMap(indices, vertices, normals));
  ASSERT(normalVBO->update(&normals[0], sizeof(float) * normals.size(), STATIC_DRAW));

  buffersState.indices = BufferDesc(1, UNSIGNED_SHORT, 0, indexVBO, true);
  buffersState.normals = BufferDesc(3, FLOAT, 0, normalVBO, true);
  buffersState.texCoords = BufferDesc(2, FLOAT, 0, textureVBO, true);
  buffersState.vertices = BufferDesc(3, FLOAT, 0, vertexVBO, true);

  stateManager->popStates(BUFFERS_STATE);

  return OK;
}

Vector3f Model::getMeshCenter(uint index) {
  ERROR_IF(index >= meshList.size(), L"Index is out of bounds", Vector3f(0, 0, 0));
  return meshList[index].getCenter();
}

uint Model::getMeshesCount() {
  return meshList.size();
}

}

