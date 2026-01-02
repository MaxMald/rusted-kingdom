#pragma once

#include <SFML/Graphics/Rect.hpp>

#include "rkIComponentFactory.h"

namespace rk
{
  class SpriteComponent;
  class AssetManager;
  class GameObject;

  class SpriteComponentFactory : public IComponentFactory
  {
  public:
    SpriteComponentFactory(AssetManager& assetManager);
    ~SpriteComponentFactory();

    UniquePtr<SpriteComponent> createSpriteComponent(
      GameObject& gameObject,
      const String& textureKey
    );

    UniquePtr<SpriteComponent> createSpriteComponent(
      GameObject& gameObject,
      const String& textureKey,
      const sf::IntRect& textureRect
    );

  private:
    AssetManager* m_assetManager;
  };
}