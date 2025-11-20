#include "rkSpriteComponentFactory.h"

#include <SFML/Graphics/Texture.hpp>

#include "rkAssetManager.h"
#include "rkGameObject.h"
#include "rkSpriteComponent.h"
#include "rkTexture.h"

namespace rk
{
  SpriteComponentFactory::SpriteComponentFactory(AssetManager& assetManager) :
    m_assetManager(&assetManager)
  {
  }

  SpriteComponentFactory::~SpriteComponentFactory()
  {
  }

  UniquePtr<SpriteComponent> SpriteComponentFactory::createSpriteComponent(
    GameObject& gameObject,
    const String& textureKey
  )
  {
    const SharedPtr<rk::Texture> texture = m_assetManager->getAssetGroup<rk::Texture>()
      .get(textureKey);

    return  MakeUnique<SpriteComponent>(gameObject, texture->getSFMLTexture());
  }

  UniquePtr<SpriteComponent> SpriteComponentFactory::createSpriteComponent(
    GameObject& gameObject,
    const String& textureKey,
    const sf::IntRect& textureRect
  )
  {
    const SharedPtr<rk::Texture> texture = m_assetManager->getAssetGroup<rk::Texture>()
      .get(textureKey);

    return MakeUnique<SpriteComponent>(
      gameObject,
      texture->getSFMLTexture(),
      textureRect
    );
  }
}