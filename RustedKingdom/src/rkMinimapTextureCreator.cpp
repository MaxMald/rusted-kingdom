#include "rkMinimapTextureCreator.h"

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <TMR/tmrTiledMap.h>
#include <TMR/tmrLayer.h>

#include "rkTiledPropertiesHandler.h"
#include "rkGameObject.h"
#include "rkGameObjectUtilities.h"
#include "rkRectUtilities.h"
#include "rkSceneGraph.h"

using sf::RenderTexture;
using sf::Vector2u;
using sf::Vector2f;

namespace rk
{
  namespace minimapTextureCreator
  {
    static Vector<String> getMinimapLayerNames(const tmr::TiledMap* tiledMap);
    
    static Vector<GameObject*> getGameObjectsForMinimapLayers(
      const tmr::TiledMap* tiledMap,
      SceneGraph& sceneGraph
    );

    static FloatRect calculateLayersBounds(
      const Vector<GameObject*>& minimapGameObjects
    );

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
      const tmr::TiledMap* tiledMap,
      SceneGraph& sceneGraph,
      const Vector2f& size
    )
    {
      Vector<GameObject*> minimapGameObjects =
        getGameObjectsForMinimapLayers(tiledMap, sceneGraph);

      FloatRect layersBounds = calculateLayersBounds(minimapGameObjects);

      // Base render texture at original size

      RenderTexture baseRender(
        Vector2u(
          static_cast<unsigned int>(layersBounds.size.x), 
          static_cast<unsigned int>(layersBounds.size.y)
        )
      );
      baseRender.clear(sf::Color::Transparent);

      for (GameObject* obj : minimapGameObjects)
        drawGameObjectToRenderTexture(baseRender, obj, layersBounds);

      baseRender.display();

      // Minimap render texture at desired size

      sf::RenderTexture minimapRender(
        Vector2u(
          static_cast<unsigned int>(size.x),
          static_cast<unsigned int>(size.y)
        )
      );
      minimapRender.clear(sf::Color::Transparent);

      sf::Sprite baseSprite(baseRender.getTexture());
      baseSprite.setScale(
        Vector2f(
          size.x / layersBounds.size.x,
          size.y / layersBounds.size.y
        )
      );
      minimapRender.draw(baseSprite);
      minimapRender.display();

      return minimapRender.getTexture();
    }

    static Vector<GameObject*> getGameObjectsForMinimapLayers(
      const tmr::TiledMap* tiledMap,
      SceneGraph& sceneGraph
    )
    {
      Vector<String> minimapLayerNames = getMinimapLayerNames(tiledMap);
      Vector<GameObject*> minimapGameObjects;

      for (const String& layerName : minimapLayerNames)
      {
        GameObject* layerGameObject = sceneGraph.getRoot()->findChildByName(layerName);

        if (layerGameObject)
          minimapGameObjects.push_back(layerGameObject);
      }

      return minimapGameObjects;
    }

    static Vector<String> getMinimapLayerNames(const tmr::TiledMap* tiledMap)
    {
      SizeT numLayers = tiledMap->getLayersCount();
      Vector<String> minimapLayerNames;

      for (SizeT i = 0; i < numLayers; ++i)
      {
        const tmr::Layer* layer = tiledMap->getLayerAt(i);
        TiledPropertiesHandler propertiesHandler(layer->getProperties());

        bool isMinimapLayer = false;
        propertiesHandler.tryGetBool("minimap", isMinimapLayer);

        if (isMinimapLayer)
          minimapLayerNames.push_back(layer->getName());
      }

      return minimapLayerNames;
    }

    static FloatRect calculateLayersBounds(
      const Vector<GameObject*>& minimapGameObjects
    )
    {
      FloatRect combinedBounds;
      bool first = true;
      for (const GameObject* gameObject : minimapGameObjects)
      {
        FloatRect bounds = gameObjectUtilities::calculateBounds(*gameObject);
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