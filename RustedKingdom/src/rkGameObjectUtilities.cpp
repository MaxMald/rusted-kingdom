#include "rkGameObjectUtilities.h"

#include "rkGameObject.h"
#include "rkSpriteComponent.h"
#include "rkRectUtilities.h"

using sf::Vector2f;

namespace rk
{
  namespace gameObjectUtilities
  {
    static void calculateBounds(const GameObject& gameObject, Vector<FloatRect>& outBounds);
  }
}

namespace rk
{
  namespace gameObjectUtilities
  {
    void setSpriteOrigin(GameObject& gameObject, float x, float y)
    {
      SpriteComponent* spriteComponent = gameObject.getComponent<SpriteComponent>();

      if (!spriteComponent)
        return;

      sf::IntRect textureRect = spriteComponent->getSprite().getTextureRect();
      spriteComponent->setOrigin(
        sf::Vector2f(
          textureRect.size.x * x,
          textureRect.size.y * y
        )
      );
    }

    FloatRect calculateAggregateBounds(const GameObject& gameObject)
    {
      Vector<FloatRect> boundsList;
      calculateBounds(gameObject, boundsList);

      if (boundsList.empty())
        return FloatRect(Vector2f(0.f, 0.f), Vector2f(0.f, 0.f));

      FloatRect combinedBounds;
      bool first = true;
      for (const FloatRect& bounds : boundsList)
      {
        if (first)
        {
          combinedBounds = bounds;
          first = false;
        }
        else
        {
          combinedBounds = rectUtilities::unify(combinedBounds, bounds);
        }
      }

      return combinedBounds;
    }

    static void calculateBounds(
      const GameObject& gameObject,
      Vector<FloatRect>& outBounds
    )
    {
      if (gameObject.hasComponent<SpriteComponent>())
        outBounds.push_back(getGameObjectSpriteGlobalBounds(gameObject));

      for (const UniquePtr<GameObject>& child : gameObject.getChildren())
        calculateBounds(*child, outBounds);
    }

    FloatRect getGameObjectSpriteGlobalBounds(const GameObject& gameObject)
    {
      if (!gameObject.hasComponent<SpriteComponent>())
      {
        return FloatRect(
          gameObject.getWorldPosition(),
          Vector2f(0.f, 0.f)
        );
      }

      const SpriteComponent* spriteComponent 
        = gameObject.getComponent<SpriteComponent>();

      const sf::Sprite& sprite = spriteComponent->getSprite();
      sf::FloatRect localBounds = sprite.getLocalBounds();
      sf::Transform transform = gameObject.getWorldTransform();

      sf::Vector2f topLeft = transform.transformPoint(
        Vector2f(localBounds.position.x, localBounds.position.y)
      );
      sf::Vector2f topRight = transform.transformPoint(
        Vector2f(localBounds.position.x + localBounds.size.x, localBounds.position.y)
      );
      sf::Vector2f bottomLeft = transform.transformPoint(
        Vector2f(localBounds.position.x, localBounds.position.y + localBounds.size.y)
      );
      sf::Vector2f bottomRight = transform.transformPoint(
        Vector2f(localBounds.position.x + localBounds.size.x, localBounds.position.y + localBounds.size.y)
      );

      float minX = std::min({ topLeft.x, topRight.x, bottomLeft.x, bottomRight.x });
      float maxX = std::max({ topLeft.x, topRight.x, bottomLeft.x, bottomRight.x });
      float minY = std::min({ topLeft.y, topRight.y, bottomLeft.y, bottomRight.y });
      float maxY = std::max({ topLeft.y, topRight.y, bottomLeft.y, bottomRight.y });

      return FloatRect(
        Vector2f(minX, minY),
        Vector2f(maxX - minX, maxY - minY)
      );
    }
  }
}