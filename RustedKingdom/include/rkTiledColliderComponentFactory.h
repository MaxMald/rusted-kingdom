#pragma once

#include "rkPrerequisites.h"

namespace tmr
{
  class Object;
  class EllipseObject;
}

namespace rk
{
  class GameObject;
  class ColliderComponent;
  class CircleColliderComponent;
  class ColliderComponentFactory;

  namespace tiledColliderComponentFactory
  {
    UniquePtr<ColliderComponent> create(
      const tmr::Object*,
      GameObject&,
      const String& colliderGroupKey
    );

    UniquePtr<ColliderComponent> createCircle(
      const tmr::EllipseObject*,
      GameObject&,
      const String& colliderGroupKey
    );
  }
}