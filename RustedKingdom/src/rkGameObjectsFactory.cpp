#include "rkGameObjectsFactory.h"

#include <SFML/Graphics/Texture.hpp>

#include "rkSceneGraph.h"
#include "rkAssetManager.h"
#include "rkSpriteGameObject.h"
#include "rkLayerGameObject.h"

namespace rk
{
  GameObjectsFactory::GameObjectsFactory(
    const AssetManager* assetsManager
  ) :
    m_assetsManager(assetsManager)
  {
  }

  SpriteGameObject* GameObjectsFactory::createSpriteGameObject(
    const String& textureKey
  )
  {
    const sf::Texture* texture = m_assetsManager->getTexture(textureKey);
    if (!texture)
      return nullptr;

    return new SpriteGameObject(texture);
  }

  SpriteGameObject* GameObjectsFactory::createSpriteGameObject(
    const String& textureKey,
    const sf::IntRect& textureRect
  )
  {
    const sf::Texture* texture = m_assetsManager->getTexture(textureKey);
    if (!texture)
      return nullptr;

    return new SpriteGameObject(texture, textureRect);
  }
}