#include "rkGameObjectUtilities.h"
#include "rkGameObject.h"
#include "rkSpriteComponent.h"

namespace rk
{
  namespace gameObjectUtilities
  {
    void setOrigin(GameObject& gameObject, float x, float y)
    {
      SpriteComponent* spriteComponent = gameObject.getComponent<SpriteComponent>(
        componentType::Sprite
      );

      if (!spriteComponent)
        return;

      sf::IntRect textureRect = spriteComponent->getSprite().getTextureRect();
      gameObject.setOrigin(
        sf::Vector2f(
          textureRect.size.x * x,
          textureRect.size.y * y
        )
      );
    }
  }
}