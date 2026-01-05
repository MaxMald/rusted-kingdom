#include "rkSpriteComponentFactory.h"

#include <SFML/Graphics/Texture.hpp>

#include "rkServiceLocator.h"
#include "rkAssetManager.h"
#include "rkGameObject.h"
#include "rkSpriteComponent.h"
#include "rkTexture.h"

namespace rk
{
  namespace spriteComponentFactory
  {
    UniquePtr<SpriteComponent> createSpriteComponent(
      GameObject& gameObject,
      const String& textureKey
    )
    {
      const SharedPtr<AssetManager> assetManager =
        ServiceLocator::Instance().getService<AssetManager>();

      const SharedPtr<rk::Texture> texture =
        assetManager->getAssetGroup<rk::Texture>().get(textureKey);

      return  MakeUnique<SpriteComponent>(gameObject, texture->getSFMLTexture());
    }

    UniquePtr<SpriteComponent> createSpriteComponent(
      GameObject& gameObject,
      const String& textureKey,
      const sf::IntRect& textureRect
    )
    {
      const SharedPtr<AssetManager> assetManager =
        ServiceLocator::Instance().getService<AssetManager>();

      const SharedPtr<rk::Texture> texture =
        assetManager->getAssetGroup<rk::Texture>().get(textureKey);

      return MakeUnique<SpriteComponent>(
        gameObject,
        texture->getSFMLTexture(),
        textureRect
      );
    }
  }
}