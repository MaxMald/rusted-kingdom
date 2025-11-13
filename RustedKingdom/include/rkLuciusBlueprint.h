#pragma once

#include "rkPrerequisites.h"
#include "rkBlueprint.h"

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

  class LuciusBlueprint : public Blueprint
  {
  public:
    LuciusBlueprint(
      GameObjectBuilder& gameObjectBuilder,
      SpriteComponentFactory& spriteComponentFactory,
      AnimationFactory& animationFactory,
      const RenderWindow& renderWindow
    );
    ~LuciusBlueprint() override;

    virtual GameObject* instantiate(GameObject& parent) override;

  private:
    GameObjectBuilder& m_gameObjectBuilder;
    SpriteComponentFactory& m_spriteComponentFactory;
    AnimationFactory& m_animationFactory;
    const RenderWindow& m_renderWindow;
  };
}