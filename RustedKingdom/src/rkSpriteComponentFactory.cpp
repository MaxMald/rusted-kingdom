#include "rkSpriteComponentFactory.h"
#include "rkAssetManager.h"
#include "rkGameObject.h"
#include "rkSpriteComponent.h"

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
    assertAssetManagerHasTexture(textureKey);
    const Texture& texture = m_assetManager->getTexture(textureKey);
    return  MakeUnique<SpriteComponent>(gameObject, texture);
  }

  UniquePtr<SpriteComponent> SpriteComponentFactory::createSpriteComponent(
    GameObject& gameObject,
    const String& textureKey,
    const sf::IntRect& textureRect
  )
  {
    assertAssetManagerHasTexture(textureKey);
    const Texture& texture = m_assetManager->getTexture(textureKey);
    return MakeUnique<SpriteComponent>(
      gameObject,
      texture,
      textureRect
    );
  }

  void SpriteComponentFactory::assertAssetManagerHasTexture(
    const String& textureKey
  ) const
  {
    if (!m_assetManager->hasTexture(textureKey))
    {
      throw RuntimeErrorException(
        String::Format(
          "Texture with key '%s' not found in AssetManager.",
          textureKey.c_str()
        )
      );
    }
  }
}