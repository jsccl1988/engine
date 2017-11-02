// Copyright (c) 2017 The Smart Authors.
// All rights reserved.

#ifndef __VE_MODEL_INSTANCE_H__
#define __VE_MODEL_INSTANCE_H__

#include <string>

#include "visible_object.h"
#include "math/matrix4f.h"
#include "models/model.h"

namespace ve {

/**
    For future usage.
*/
class ModelInstance : public VisibleObject {
private:
  Matrix4f modelView;
  Model* model;

public:
  ModelInstance();
  /* Inherited from VisibleObject */
  virtual Outcome preRender(RenderQueue *renderQueue);
  virtual Outcome render(RenderQueueItem *item);
  /* General functions */
  void scale(float factor);
  void translate(const Vector4f &translation);
  /* Set functions */
  Outcome setModel(Model *model);
  Outcome setModelViewMatrix(const Matrix4f &newMatrix);
  /* Get functions */
  Model* getModel();
  Matrix4f getModelViewMatrix();
  int getFacesCount();
};

}

#endif // __VE_MODEL_INSTANCE_H__
