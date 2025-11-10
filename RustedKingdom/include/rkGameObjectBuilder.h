#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include "rkPrerequisites.h"

namespace rk
{
  class Component;
  class GameObject;
  class AssetManager;

  class GameObjectBuilder
  {
  public:

    GameObjectBuilder(const AssetManager& assetsManager);
    ~GameObjectBuilder();

    GameObjectBuilder(const GameObjectBuilder&) = delete;
    GameObjectBuilder& operator=(const GameObjectBuilder&) = delete;
    GameObjectBuilder(GameObjectBuilder&&) noexcept = delete;
    GameObjectBuilder& operator=(GameObjectBuilder&&) noexcept = delete;

    GameObjectBuilder& createGameObject();
    GameObjectBuilder& createGameObject(const String& name);

    GameObjectBuilder& position(const sf::Vector2f& position);

    GameObjectBuilder& addSpriteComponent(const String& textureKey);
    GameObjectBuilder& addSpriteComponent(const String& textureKey,
      const sf::IntRect& textureRect
    );
    
    void buildWithParent(GameObject& parent);
    UniquePtr<GameObject> build();
    

  private:
    GameObject* m_current;
    const AssetManager* m_assetsManager;

    void assertCurrentIsNull() const;
    void assertCurrentIsNotNull() const;
  };
}