#pragma once

#include "rkPrerequisites.h"

namespace rk
{
  class Collider;

  class PhysicWorldListener
  {
  public:
    virtual ~PhysicWorldListener() = default;

    virtual void onColliderChanged(Collider* collider) = 0;
  };
}