#include "rkTiledColliderComponentFactory.h"

#include <TMR/tmrEllipseObject.h>

#include "rkPhysicWorld.h"
#include "rkColliderComponentFactory.h"
#include "rkColliderComponent.h"

namespace rk
{
  TiledColliderComponentFactory::TiledColliderComponentFactory(
    ColliderComponentFactory& colliderComponentFactory
  ) :
    m_colliderComponentFactory(colliderComponentFactory)
  {
  }

  TiledColliderComponentFactory::~TiledColliderComponentFactory()
  {
  }

  UniquePtr<ColliderComponent> TiledColliderComponentFactory::create(
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

  UniquePtr<ColliderComponent> TiledColliderComponentFactory::createCircle(
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

    return m_colliderComponentFactory.createCircle(
      gameObject,
      center,
      radius,
      colliderGroupKey
    );
  }
}