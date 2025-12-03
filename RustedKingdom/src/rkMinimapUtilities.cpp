#include "rkMinimapUtilities.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <TMR/tmrTiledMap.h>
#include <TMR/tmrLayer.h>

#include "rkTexture.h"
#include "rkGameObject.h"
#include "rkSceneGraph.h"
#include "rkMinimapTextureCreator.h"
#include "rkSpriteComponent.h"
#include "rkServiceLocator.h"
#include "rkAssetManager.h"
#include "rkGameObjectUtilities.h"
#include "rkTiledPropertiesHandler.h"
#include "rkRectUtilities.h"

#include "scripts/rkMinimapScript.h"

using sf::Vector2i;

namespace rk
{
  namespace minimapUtilities
  {
    static Vector<String> getMinimapLayerNames(const tmr::TiledMap* tiledMap);

    static Vector<GameObject*> getMapGameObjects(
      const tmr::TiledMap* tiledMap,
      SceneGraph& sceneGraph
    );

    static FloatRect calculateMapBounds(
      const Vector<GameObject*>& mapGameObjects
    );

    static Vector2f getMinimapSize(
      const GameObject* minimapGameObject
    );
  }
}

namespace rk
{
  namespace minimapUtilities
  {
    void prepare(
      GameObject* minimapGameObject,
      const tmr::TiledMap* tiledMap,
      SceneGraph& sceneGraph
    )
    {
      if (!minimapGameObject)
        throw RuntimeErrorException("Minimap GameObject pointer is null");

      if (!tiledMap)
        throw RuntimeErrorException("TiledMap pointer is null");

      if (!minimapGameObject->hasComponent<SpriteComponent>())
        throw RuntimeErrorException("Minimap GameObject must have a SpriteComponent");

      if (!minimapGameObject->hasComponent<MinimapScript>())
        throw RuntimeErrorException("Minimap GameObject must have a MinimapScript");

      Vector<GameObject*> mapGameObjects = getMapGameObjects(tiledMap, sceneGraph);
      FloatRect mapBounds = calculateMapBounds(mapGameObjects);
      Vector2f minimapSize = getMinimapSize(minimapGameObject);

      // Create Minimap Texture

      sf::Texture minimapTexture =
        minimapTextureCreator::create(
          tiledMap,
          mapGameObjects,
          mapBounds,
          minimapSize,
          sceneGraph
        );

      // Register Minimap Texture

      SharedPtr<AssetManager> assetManager = ServiceLocator::Instance()
        .getService<AssetManager>();
      TypedAssetGroup<Texture>& textures = assetManager->getAssetGroup<Texture>();

      if (textures.has(minimapUtilities::MINIMAP_TEXTURE_KEY))
        textures.unload(minimapUtilities::MINIMAP_TEXTURE_KEY);

      SharedPtr<Texture> rkMinimapTexture = MakeShared<Texture>(minimapTexture);
      textures.registerAsset(minimapUtilities::MINIMAP_TEXTURE_KEY, rkMinimapTexture);

      // Apply Minimap Texture to Game Object

      SpriteComponent* spriteComp =
        minimapGameObject->getComponent<SpriteComponent>();

      sf::Sprite& sfmlSprite = spriteComp->getSprite();
      sfmlSprite.setTexture(rkMinimapTexture->getSFMLTexture());

      // Prepare Minimap Script

      MinimapScript* minimapScript =
        minimapGameObject->getComponent<MinimapScript>();

      minimapScript->setMapRect(mapBounds);
      minimapScript->setMinimapSize(minimapSize);
    }

    static Vector<GameObject*> getMapGameObjects(
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

    static FloatRect calculateMapBounds(
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

    Vector2f getMinimapSize(const GameObject* minimapGameObject)
    {
      const SpriteComponent* spriteComp =
        minimapGameObject->getComponent<SpriteComponent>();

      const sf::Sprite& sfmlSprite = spriteComp->getSprite();
      Vector2i minimapSize = sfmlSprite.getTextureRect().size;

      return Vector2f(
        static_cast<float>(minimapSize.x),
        static_cast<float>(minimapSize.y)
      );
    }
  }
}