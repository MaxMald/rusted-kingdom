#pragma once

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"

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

  class TiledColliderComponentFactory : public NonCopyable
  {
  public:
    TiledColliderComponentFactory(
      ColliderComponentFactory&
    );
    ~TiledColliderComponentFactory();

    UniquePtr<ColliderComponent> create(
      const tmr::Object*,
      GameObject&,
      const String& colliderGroupKey
    );

    UniquePtr<CircleColliderComponent> createCircle(
      const tmr::EllipseObject*,
      GameObject&,
      const String& colliderGroupKey
    );

  private:
    ColliderComponentFactory& m_colliderComponentFactory;
  };
}