// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include <stdio.h>
#include <vector>

#include "common.h"
#include "loaders/3ds_loader.h"

namespace ve {

_3dsLoader::_3dsLoader() {
}

Outcome _3dsLoader::freeMeshList() {
  uint len = meshList.size();

  for (uint i = 0; i < len; i++) {
    delete meshList[i];
  }

  return OK;
}

Outcome _3dsLoader::readName(FILE *source, std::string &name) {
  char c = 0;
  name = "";

  do {
    /* Read one character from file stream */
    ERROR_IF(fread(&c, sizeof(char), 1, source) != 1, L"readName failed", ERROR);

    if (c != 0) {
      name = name + c;
    }
  } while (c != 0);

  return OK;
}

Outcome _3dsLoader::readMesh(FILE *source, unsigned length) {
  _3dsChunk chunk;
  uint i;
  _3dsVertexList vertexList;
  _3dsVertex vertex;
  _3dsFaceList faceList;
  _3dsFace face;
  _3dsLocalAxis localData;
  std::vector<Vector3f> vertexData;
  std::vector<unsigned short> indexData;
  std::vector<Vector2f> texData;
  unsigned short vertexCount;
  _3dsTexCoord texCoord;
  Mesh *newMesh = new Mesh();

  while (length != 0) {
    ERROR_IF(fread(&chunk, sizeof(chunk), 1, source) != 1, L"3ds loader failed to parse file", ERROR);

    switch (chunk.type) {
    case TRI_RTEXL:
      ERROR_IF(fread(&vertexList, sizeof(vertexList), 1, source) != 1, L"Failed to read vertex list", ERROR);
      vertexData.clear();

      for (i = 0; i < vertexList.count; i++) {
        ERROR_IF(fread(&vertex, sizeof(vertex), 1, source) != 1, L"Failed to read vertex", ERROR);

        vertexData.push_back(Vector3f(vertex.x, vertex.y, vertex.z));
      }

      newMesh->setVertexList(vertexList.count, &vertexData[0]);
      break;

    case TRI_FACEL1:
      ERROR_IF(fread(&faceList, sizeof(faceList), 1, source) != 1, L"Failed to read face list", ERROR);
      indexData.clear();

      for (i = 0; i < faceList.count; i++) {
        ERROR_IF(fread(&face, sizeof(face), 1, source) != 1, L"Failed to read face", ERROR);

        indexData.push_back(face.a);
        indexData.push_back(face.b);
        indexData.push_back(face.c);
      }

      newMesh->setFaceList(faceList.count, &indexData[0]);
      break;

    case TRI_TEXCOORD:
      ERROR_IF(fread(&vertexCount, sizeof(vertexCount), 1, source) != 1, L"Failed to read vertex count", ERROR);
      texData.clear();

      for (i = 0; i < vertexCount; i++) {
        ERROR_IF(fread(&texCoord, sizeof(texCoord), 1, source) != 1, L"Failed to read texture coords", ERROR);
        texData.push_back(Vector2f(texCoord.u, texCoord.v));
      }

      newMesh->setTextureList(vertexCount, &texData[0]);
      break;

    case TRI_LOCAL:
      ERROR_IF(fread(&localData, sizeof(localData), 1, source) != 1, L"Failed to load local chunk", ERROR);
      newMesh->setCenter(Vector3f(localData.xCenter, localData.yCenter, localData.zCenter));
      break;

    default:
      fseek(source, chunk.length - sizeof(chunk), SEEK_CUR);
    }

    length -= chunk.length;
  }

  if (newMesh->getVertexCount() != 0) {
    meshList.push_back(newMesh);
  }

  return OK;
}

Outcome _3dsLoader::readLight(FILE *source, unsigned length) {
  _3dsLight light;
  _3dsChunk chunk;
  _3dsRGB rgb;
  _3dsTrueColor trueColor;
  _3dsSpot spot;

  ERROR_IF(fread(&light, sizeof(light), 1, source) != 1, L"Failed to read light chunk", ERROR);
  length -= sizeof(light);

  while (length != 0) {
    ERROR_IF(fread(&chunk, sizeof(chunk), 1, source) != 1, L"Failed to read light data", ERROR);

    switch (chunk.type) {
    case LIT_SPOT:
      ERROR_IF(fread(&spot, sizeof(spot), 1, source) != 1, L"Failed to read spot data", ERROR);
      break;

    case COL_RGB:
      ERROR_IF(fread(&rgb, sizeof(rgb), 1, source) != 1, L"Failed to read RGB data", ERROR);
      break;

    case COL_TRU:
      ERROR_IF(fread(&trueColor, sizeof(trueColor), 1, source) != 1, L"Failed to read true color data", ERROR);
      break;

    default:
      fseek(source, chunk.length, SEEK_CUR);
    }

    length -= chunk.length;
  }

  return OK;
}

Outcome _3dsLoader::readCamera(FILE *source, unsigned length) {
  _3dsCamera camera;

  ERROR_IF(fread(&camera, sizeof(camera), 1, source) != 1, L"Failed to read camera chunk", ERROR);
  length = length - sizeof(camera);

  if (length > 0) {
    fseek(source, length, SEEK_CUR);
  }

  return OK;
}

Outcome _3dsLoader::readObject(FILE *source, unsigned length) {
  _3dsChunk chunk;

  while (length != 0) {
    ERROR_IF(fread(&chunk, sizeof(chunk), 1, source) != 1, L"Failed to read object chunk", ERROR);

    switch (chunk.type) {
    case OBJ_TRIMESH:
      ASSERT(readMesh(source, chunk.length - sizeof(chunk)));
      break;

    case OBJ_LIGHT:
      ASSERT(readLight(source, chunk.length - sizeof(chunk)));
      break;

    case OBJ_CAMERA:
      ASSERT(readCamera(source, chunk.length - sizeof(chunk)));
      break;

    default:
      fseek(source, chunk.length - sizeof(chunk), SEEK_CUR);
      break;
    }

    length -= chunk.length;
  }

  return OK;
}

Outcome _3dsLoader::load(FILE* source, size_t offset) {
  _3dsChunk chunk;
  std::string objName;

  CHECK_POINTER(source);
  ASSERT(freeMeshList());

  fseek(source, offset, SEEK_SET);
  while (fread(&chunk, sizeof(chunk), 1, source) == 1) {
    switch (chunk.type) {
    case MAIN3DS:
      break;

    case EDIT3DS:
      break;

    case KEYF3DS:
      fseek(source, chunk.length - sizeof(chunk), SEEK_CUR);
      break;

      /* Edit section */
    case EDIT_OBJECT:
      readName(source, objName);
      ASSERT(readObject(source, chunk.length - sizeof(chunk) - objName.length() - 1));
      break;

    default:
      fseek(source, chunk.length - sizeof(chunk), SEEK_CUR);
    }
  }

  return OK;
}

std::vector<Mesh*> _3dsLoader::getMeshList() {
  return meshList;
}

}
