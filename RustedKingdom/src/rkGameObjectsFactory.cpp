#include "rkGameObjectsFactory.h"
#include <SFML/Graphics/Texture.hpp>
#include "rkSceneGraph.h"
#include "rkAssetManager.h"
#include "rkSpriteGameObject.h"

namespace rk
{
  GameObjectsFactory::GameObjectsFactory(
    SceneGraph* sceneGraph,
    const AssetManager* assetsManager
  ) :
    m_sceneGraph(sceneGraph),
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

    auto obj = MakeUnique<SpriteGameObject>(texture);
    SpriteGameObject* rawPtr = obj.get();
    m_sceneGraph->getRoot()->addChild(std::move(obj));
    return rawPtr;
  }

  SpriteGameObject* GameObjectsFactory::createSpriteGameObject(
    const String& textureKey,
    const sf::IntRect& textureRect
  )
  {
    const sf::Texture* texture = m_assetsManager->getTexture(textureKey);
    if (!texture)
      return nullptr;

    auto obj = MakeUnique<SpriteGameObject>(texture, textureRect);
    SpriteGameObject* rawPtr = obj.get();
    m_sceneGraph->getRoot()->addChild(std::move(obj));
    return rawPtr;
  }
}