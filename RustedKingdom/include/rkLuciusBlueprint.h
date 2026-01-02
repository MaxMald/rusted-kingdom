#pragma once

#include "rkPrerequisites.h"
#include "rkGameObjectBlueprint.h"
#include "rkIPositionTransformer.h"

namespace rk
{
  class GameObjectBuilder;
  class SpriteComponentFactory;
  class AnimationFactory;
  class RigidBodyComponentFactory;
  class ColliderComponentFactory;
  class Pathfinder;

  class LuciusBlueprint : public GameObjectBlueprint
  {
  public:
    LuciusBlueprint(
      GameObjectBuilder& gameObjectBuilder,
      SpriteComponentFactory& spriteComponentFactory,
      AnimationFactory& animationFactory,
      RigidBodyComponentFactory& rigidBodyComponentFactory,
      ColliderComponentFactory& colliderComponentFactory,
      SharedPtr<Pathfinder> pathfinder,
      SharedPtr<IPositionTransformer> positionTransform
    );
    ~LuciusBlueprint() override;

    virtual void apply(GameObject& gameObject) const override;

  private:
    GameObjectBuilder& m_gameObjectBuilder;
    SpriteComponentFactory& m_spriteComponentFactory;
    ColliderComponentFactory& m_colliderComponentFactory;
    AnimationFactory& m_animationFactory;
    RigidBodyComponentFactory& m_rigidBodyComponentFactory;
    SharedPtr<Pathfinder> m_pathfinder;
    SharedPtr<IPositionTransformer> m_positionTransform;
  };
}