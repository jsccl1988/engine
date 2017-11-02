// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#include "models/sphere.h"
#include "models/mesh.h"
#include "engines/engine.h"

namespace ve {

/**
    Default constructor. No data is generated in this constructor.
*/
Sphere::Sphere() {
}

/**
    Generates vertices and texture coordinates for the sphere with specified
    parameters. Vary numbers of slices and stacks to generate spherical
    objects with different precision.
    @param radius - Radius of the sphere.
    @param slices - Number of slices in the sphere.
    @param stacks - Number of stacks in the sphere.
*/
Sphere::Sphere(float radius, int slices, int stacks) {
  generate(radius, slices, stacks);
}

/**
    Generates vertices and texture coordinates for the sphere with specified
    parameters. Vary numbers of slices and stacks to generate spherical
    objects with different precision.
    @param radius - Radius of the sphere.
    @param slices - Number of slices in the sphere.
    @param stacks - Number of stacks in the sphere.
*/
void Sphere::generate(float radius, int slices, int stacks) {
  vertices.clear();
  texCoords.clear();
  faces.clear();

  for (int row = 0; row < slices; row++) {
    float thetha = (float)row / (slices - 1) * Maths::PI;
    float new_radius = sin(thetha) * radius;
    float cos_thetha = cos(thetha);

    for (int col = 0; col < stacks; col++) {
      float phi = (float)col / (stacks - 1) * 2 * Maths::PI;
      float x = cos(phi) * new_radius;
      float y = sin(phi) * new_radius;
      float z = cos_thetha * radius;
      float s = (float)col / (stacks - 1);
      float t = 1.0f - (float)row / (slices - 1);

      vertices.push_back(Vector3f(x, y, z));
      texCoords.push_back(Vector2f(s, t));

      if (row != 0 && col != stacks - 1) {
        faces.push_back(row * stacks + col);
        faces.push_back((row - 1) * stacks + col + 1);
        faces.push_back((row - 1) * stacks + col);

        faces.push_back(row * stacks + col);
        faces.push_back(row * stacks + col + 1);
        faces.push_back((row - 1) * stacks + col + 1);
      }
    }
  }
}

/**
    Constructs Model object for the generated sphere.
    @return Model object that represents the generated sphere.
*/
Model* Sphere::getModel(Engine *engine) {
  Mesh *newMesh = new Mesh();
  newMesh->setCenter(Vector3f(0, 0, 0));
  newMesh->setVertexList(vertices.size(), &vertices[0]);
  newMesh->setTextureList(texCoords.size(), &texCoords[0]);
  newMesh->setFaceList(faces.size() / 3, &faces[0]);

  Model *newModel = new Model(engine);
  std::vector<Mesh*> meshes;
  meshes.push_back(newMesh);

  if (newModel->update(meshes) != OK) {
    LOG_ERROR(L"Update Mesh failed");

    delete newModel;
    delete newMesh;
  }

  /* No need in mesh since we copied all the data to the Model instance */
  delete newMesh;

  return newModel;
}

/**
    Returns vertex coordinates for the generated sphere.
    @return Array of vertices.
*/
std::vector<Vector3f> Sphere::getVertices() {
  return vertices;
}

/**
    Returns texture coordinates for the generated sphere.
    @return Array of texture coordinates.
*/
std::vector<Vector2f> Sphere::getTextureCoordinates() {
  return texCoords;
}


}
