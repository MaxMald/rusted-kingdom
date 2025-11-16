#pragma once

#include "rkPrerequisites.h"
#include "rkGameObjectBlueprint.h"
#include "rkIsometricPositionTransformer.h"

namespace sf
{
  class RenderWindow;
}

using sf::RenderWindow;

namespace rk
{
  class GameObjectBuilder;
  class SpriteComponentFactory;
  class AnimationFactory;
  class RigidBodyComponentFactory;
  class Pathfinder;

  class LuciusBlueprint : public GameObjectBlueprint
  {
  public:
    LuciusBlueprint(
      GameObjectBuilder& gameObjectBuilder,
      SpriteComponentFactory& spriteComponentFactory,
      AnimationFactory& animationFactory,
      RigidBodyComponentFactory& rigidBodyComponentFactory,
      SharedPtr<Pathfinder> pathfinder,
      const IsometricPositionTransformer isometricPositionTransformer,
      const RenderWindow& renderWindow
    );
    ~LuciusBlueprint() override;

  protected:
    virtual GameObject* instantiate(GameObject& parent) const override;

  private:
    GameObjectBuilder& m_gameObjectBuilder;
    SpriteComponentFactory& m_spriteComponentFactory;
    AnimationFactory& m_animationFactory;
    RigidBodyComponentFactory& m_rigidBodyComponentFactory;
    SharedPtr<Pathfinder> m_pathfinder;
    IsometricPositionTransformer m_isometricPositionTransformer;
    const RenderWindow& m_renderWindow;
  };
}