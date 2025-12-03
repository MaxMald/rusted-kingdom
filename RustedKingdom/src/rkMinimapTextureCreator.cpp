#include "rkMinimapTextureCreator.h"

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <TMR/tmrTiledMap.h>
#include <TMR/tmrLayer.h>

#include "rkGameObject.h"
#include "rkRectUtilities.h"
#include "rkSceneGraph.h"

using sf::RenderTexture;
using sf::Vector2u;
using sf::Vector2f;

namespace rk
{
  namespace minimapTextureCreator
  {
    static void drawGameObjectToRenderTexture(
      RenderTexture& renderTexture,
      const GameObject* gameObject,
      const FloatRect& offsetBounds
    );
  }
}

namespace rk
{
  namespace minimapTextureCreator
  {
    sf::Texture create(
      const tmr::TiledMap*,
      const Vector<GameObject*>& mapGameObjects,
      const FloatRect& mapBounds,
      const Vector2f& minimapSize,
      SceneGraph&
    )
    {
      // Base render texture at original size

      RenderTexture baseRender(
        Vector2u(
          static_cast<unsigned int>(mapBounds.size.x), 
          static_cast<unsigned int>(mapBounds.size.y)
        )
      );
      baseRender.clear(sf::Color::Transparent);

      for (GameObject* obj : mapGameObjects)
        drawGameObjectToRenderTexture(baseRender, obj, mapBounds);

      baseRender.display();

      // Minimap render texture at desired size

      sf::RenderTexture minimapRender(
        Vector2u(
          static_cast<unsigned int>(minimapSize.x),
          static_cast<unsigned int>(minimapSize.y)
        )
      );
      minimapRender.clear(sf::Color::Transparent);

      sf::Sprite baseSprite(baseRender.getTexture());
      baseSprite.setScale(
        Vector2f(
          minimapSize.x / mapBounds.size.x,
          minimapSize.y / mapBounds.size.y
        )
      );
      minimapRender.draw(baseSprite);
      minimapRender.display();

      return minimapRender.getTexture();
    }

    static void drawGameObjectToRenderTexture(
      RenderTexture& renderTexture,
      const GameObject* gameObject,
      const FloatRect& offsetBounds
    )
    {
      sf::RenderStates states;

      // Offset so top-left of bounds is (0,0)
      states.transform.translate(
        Vector2f(-offsetBounds.position.x, -offsetBounds.position.y)
      );

      gameObject->draw(renderTexture, states);
    }
  }
}