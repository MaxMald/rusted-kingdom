#include "rkLuciusBlueprint.h"

#include <SFML/System/Angle.hpp>

#include "rkGameObjectBuilder.h"
#include "rkAnimationStateMachineBuilder.h"
#include "rkSpriteComponentFactory.h"
#include "rkSpriteComponent.h"
#include "rkAnimationStateMachineComponent.h"
#include "rkAnimationStateMachine.h"
#include "scripts/rkLucius.h"

using sf::IntRect;
using sf::Vector2i;

namespace rk
{
  LuciusBlueprint::LuciusBlueprint(
    GameObjectBuilder& gameObjectBuilder, 
    SpriteComponentFactory& spriteComponentFactory, 
    AnimationFactory& animationFactory, 
    const RenderWindow& renderWindow
  ) :
    m_gameObjectBuilder(gameObjectBuilder),
    m_spriteComponentFactory(spriteComponentFactory),
    m_animationFactory(animationFactory),
    m_renderWindow(renderWindow)
  {
  }

  LuciusBlueprint::~LuciusBlueprint()
  {
  }

  GameObject* LuciusBlueprint::instantiate(GameObject& parent)
  {
    GameObject* lucius = m_gameObjectBuilder
      .createGameObject("lucius")
      .buildWithParent(parent);

    lucius->addComponent(
      m_spriteComponentFactory.createSpriteComponent(
        *lucius,
        "lucius-walking",
        IntRect(Vector2i(0, 0), Vector2i(100, 100))
      )
    );

    AnimationStateMachineBuilder animBuilder(m_animationFactory);
    UniquePtr<AnimationStateMachine> animStateMachine = animBuilder
      .createStateMachine("running")
      .withAngle("directionAngle", sf::radians(0.0f))
      .withFloat("speedModifierKey", 1.0f)
      .withEightDirectionAnimationState("running", "lucius-walking-anim")
      .build();

    lucius->addComponent(
      MakeUnique<AnimationStateMachineComponent>(
        *lucius,
        std::move(animStateMachine)
      )
    );

    lucius->addComponent(
      MakeUnique<Lucius>(*lucius, m_renderWindow)
    );

    return lucius;
  }
}