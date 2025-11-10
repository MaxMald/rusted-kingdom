#pragma once

#include "rkGameObject.h"

namespace rk
{
  class LayerGameObject : public GameObject
  {
  public:
    LayerGameObject(const char* name);
    virtual ~LayerGameObject();

    virtual void update(float deltaTime) override;

  protected:
    void sortChildrenByYPosition();
  };
}
