#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include "rkPrerequisites.h"
#include "rkGameObject.h"

namespace rk
{
  class Component;
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

    GameObjectBuilder& withSpriteComponent(const String& textureKey);
    GameObjectBuilder& withSpriteComponent(const String& textureKey,
      const sf::IntRect& textureRect
    );

    GameObjectBuilder& withAnimationComponent();
    GameObjectBuilder& withAnimationComponent(const String& animationKey);

    template<typename T, typename... Args>
    GameObjectBuilder& withComponent(Args&&... args);
    
    void buildWithParent(GameObject& parent);
    UniquePtr<GameObject> build();
    

  private:
    GameObject* m_current;
    const AssetManager* m_assetsManager;

    void assertCurrentIsNull() const;
    void assertCurrentIsNotNull() const;
    void assertAssetManagerHasTexture(const String& textureKey) const;
  };

  template<typename T, typename... Args>
  GameObjectBuilder& GameObjectBuilder::withComponent(Args&&... args)
  {
    assertCurrentIsNotNull();
    UniquePtr<Component> component = MakeUnique<T>(*m_current, std::forward<Args>(args)...);
    m_current->addComponent(std::move(component));
    return *this;
  }
}