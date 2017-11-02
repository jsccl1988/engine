// Copyright (c) 2017 The Smart Authors.
// All rights reserved.
#ifndef __VE_MODEL_H__
#define __VE_MODEL_H__

#include <vector>

#include "engine/engines/engine.h"
#include "engine/visible_object.h"
#include "engine/math/vector3f.h"
#include "engine/buffers/video_buffer.h"
#include "engine/models/mesh.h"
#include "engine/states/buffer_state.h"

namespace ve {

/**
    Represents 3D model data. Contains VBOs for model
    rendering and list meshes that are used for rendering.
    This is not a class for model rendering. It is used only
    for storing model-related data, not a model instance data.
*/
class Model :public VisibleObject {
private:

  /**
      Internal information about mesh. All the meshes lye inside one VBO and
      this structure helps to determine where the concrete mesh lies.
  */
  struct MeshInfo {
    /** Mesh offset in bytes */
    int start;

    /** Number of vertex in this mesh */
    int count;

    /**
        Default constructor
    */
    MeshInfo() {
      start = 0;
      count = 0;
    }

    /**
        Extended constructor with specified offset and vertex count.
        @param theStart - offset in bytes for a described mesh.
        @param theCount - number of vertices in a described mesh.
    */
    MeshInfo(int theStart, int theCount) {
      start = theStart;
      count = theCount;
    }
  };

  /** Engine which is used for rendering */
  Engine *engine;

  /** VBO for indices */
  VideoBuffer *indexVBO;

  /** VBO for vertices */
  VideoBuffer *vertexVBO;

  /** VBO for texture coords */
  VideoBuffer *textureVBO;

  /** VBO for normals */
  VideoBuffer *normalVBO;

  /** List of meshes this model consist of */
  std::vector<Mesh> meshList;

  /** Additional information about meshes layout in the index VBO */
  std::vector<MeshInfo> meshInfoList;

  /** It is used to set buffers for rendering */
  BuffersState buffersState;

protected:
  /**
      Generates normals for given list of faces. Faces are defined as triples in the indices
      array. The first triple of indices describes first face, the second triple describes second face
      and so on.
      @param indices - Vector of face indices.
      @param vertices - Vector of vertices.
      @param normals - Vector of normal coordinates which will be generated in this function.
      @return OK everytime.
  */
  Outcome generateNormalMap(std::vector<unsigned short> indices, std::vector<float> vertices, std::vector<float> &normals);

public:
  /**
      Default constructor.
      @param engine - Engine object which creates this model.
  */
  Model(Engine *engine);

  /**
      Renders mesh of this model.
      @param index - Number of the mesh to render (from 0 to getMeshesCount() - 1).
      @return OK if mesh was rendered successfully.
      @return non-OK if engine error occurred.
  */
  Outcome renderMesh(uint index);

  /**
      Updates list of meshes for this model. Creates VBO for these meshes,
      load data, compute normals.
      @param meshList - Meshes this model consists of.
      @return OK if loading succeeded.
      @return non-OK if error occurred.
  */
  Outcome update(std::vector<Mesh*> meshList);

  /**
      Get number of meshes in this model.
      @return Number of meshes in this model.
  */
  uint getMeshesCount();

  /**
      Returns center of a mesh.
      @param index - Number of mesh to return center for.
      @return Center of a mesh.
  */
  Vector3f getMeshCenter(uint index);
};

}

#endif // __VE_MODEL_H__
