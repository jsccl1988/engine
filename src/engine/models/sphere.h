// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_SPHERE_H__
#define __VE_SPHERE_H__

#include <vector>

#include "math/maths.h"
#include "math/vector3f.h"
#include "math/vector2f.h"
#include "models/model.h"

namespace ve {

class Engine;

/**
    Constructor for spherical objects with a given radius. It
    is used to generatere geometry for sphere objects.
*/
class Sphere {
private:
  std::vector<Vector3f> vertices;
  std::vector<Vector2f> texCoords;
  std::vector<ushort> faces;

public:
  /**
      Default constructor. No data is generated in this constructor.
  */
  Sphere();

  /**
      Generates vertices and texture coordinates for the sphere with specified
      parameters. Vary numbers of slices and stacks to generate spherical
      objects with different precision.
      @param radius - Radius of the sphere.
      @param slices - Number of slices in the sphere.
      @param stacks - Number of stacks in the sphere.
  */
  Sphere(float radius, int slices, int stacks);

  /**
      Generates vertices and texture coordinates for the sphere with specified
      parameters. Vary numbers of slices and stacks to generate spherical
      objects with different precision.
      @param radius - Radius of the sphere.
      @param slices - Number of slices in the sphere.
      @param stacks - Number of stacks in the sphere.
  */
  void generate(float radius, int slices, int stacks);

  /**
      Constructs Model object for the generated sphere.
      @return Model object that represents the generated sphere.
  */
  Model *getModel(Engine *engine);

  /**
      Returns vertex coordinates for the generated sphere.
      @return Array of vertices.
  */
  std::vector<Vector3f> getVertices();

  /**
      Returns texture coordinates for the generated sphere.
      @return Array of texture coordinates.
  */
  std::vector<Vector2f> getTextureCoordinates();

  /**
      Returns faces for the generated sphere.
      @return Array of indices for faces (three indices per face).
  */
  std::vector<ushort> getFaces();
};

}

#endif // __VE_SPHERE_H__
