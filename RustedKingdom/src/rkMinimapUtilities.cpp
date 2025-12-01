#include "rkMinimapUtilities.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <TMR/tmrTiledMap.h>

#include "rkTexture.h"
#include "rkGameObject.h"
#include "rkSceneGraph.h"
#include "rkMinimapTextureCreator.h"
#include "rkSpriteComponent.h"
#include "rkServiceLocator.h"
#include "rkAssetManager.h"

using sf::Vector2i;

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

      SpriteComponent* spriteComp =
        minimapGameObject->getComponent<SpriteComponent>();

      sf::Sprite& sfmlSprite = spriteComp->getSprite();
      Vector2i minimapSize = sfmlSprite.getTextureRect().size;

      sf::Texture minimapTexture =
        minimapTextureCreator::create(
          tiledMap,
          sceneGraph,
          Vector2f(
            static_cast<float>(minimapSize.x),
            static_cast<float>(minimapSize.y)
          )
        );

      SharedPtr<AssetManager> assetManager = ServiceLocator::Instance()
        .getService<AssetManager>();
      TypedAssetGroup<Texture>& textures = assetManager->getAssetGroup<Texture>();

      if (textures.has(minimapUtilities::MINIMAP_TEXTURE_KEY))
        textures.unload(minimapUtilities::MINIMAP_TEXTURE_KEY);

      SharedPtr<Texture> rkMinimapTexture = MakeShared<Texture>(minimapTexture);
      textures.registerAsset(minimapUtilities::MINIMAP_TEXTURE_KEY, rkMinimapTexture);

      sfmlSprite.setTexture(rkMinimapTexture->getSFMLTexture());
    }
  }
}