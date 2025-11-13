#pragma once

#include "rkPrerequisites.h"
#include "rkGameObject.h"

namespace rk
{
  class Component;

  class GameObjectBuilder
  {
  public:

    GameObjectBuilder();
    ~GameObjectBuilder();

    GameObjectBuilder(const GameObjectBuilder&) = delete;
    GameObjectBuilder& operator=(const GameObjectBuilder&) = delete;
    GameObjectBuilder(GameObjectBuilder&&) noexcept = delete;
    GameObjectBuilder& operator=(GameObjectBuilder&&) noexcept = delete;

    GameObjectBuilder& createGameObject();
    GameObjectBuilder& createGameObject(const String& name);

    GameObjectBuilder& withPosition(const sf::Vector2f& position);
    GameObjectBuilder& withComponent(UniquePtr<Component> component);
    
    /**
     * @brief Finalizes the construction of the GameObject and adds it as a child
     * to the specified parent GameObject.
     * @param parent The parent GameObject to which the newly built GameObject
     * will be added as a child.
     * @return A raw pointer to the newly built GameObject, owned by the parent.
     */
    GameObject* buildWithParent(GameObject& parent);
    UniquePtr<GameObject> build();

  private:
    GameObject* m_current;

    void assertCurrentIsNull() const;
    void assertCurrentIsNotNull() const;
  };
}