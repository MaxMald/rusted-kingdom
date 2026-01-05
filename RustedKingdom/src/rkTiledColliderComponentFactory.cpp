#include "rkTiledColliderComponentFactory.h"

#include <TMR/tmrEllipseObject.h>

#include "rkPhysicWorld.h"
#include "rkColliderComponentFactory.h"
#include "rkColliderComponent.h"

namespace rk
{
  namespace tiledColliderComponentFactory
  {
    UniquePtr<ColliderComponent> create(
      const tmr::Object* tmrObject,
      GameObject& gameObject,
      const String& colliderGroupKey
    )
    {
      tmr::objectType::Type objectType = tmrObject->getObjectType();
      switch (objectType)
      {
      case tmr::objectType::Type::Ellipse:
        return createCircle(
          static_cast<const tmr::EllipseObject*>(tmrObject),
          gameObject,
          colliderGroupKey
        );
      default:
        return nullptr;
      }
    }

    UniquePtr<ColliderComponent> createCircle(
      const tmr::EllipseObject* ellipse,
      GameObject& gameObject,
      const String& colliderGroupKey
    )
    {
      if (ellipse == nullptr)
        return nullptr;

      UInt32 size = std::max(ellipse->getWidth(), ellipse->getHeight());
      float radius = static_cast<float>(size) * 0.5f;
      Vector2f center(
        ellipse->getX() + static_cast<float>(ellipse->getWidth()) * 0.5f,
        ellipse->getY() + static_cast<float>(ellipse->getHeight()) * 0.5f
      );

      return colliderComponentFactory::createCircle(
        gameObject,
        center,
        radius,
        colliderGroupKey
      );
    }
  }
}