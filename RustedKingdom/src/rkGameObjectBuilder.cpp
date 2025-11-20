#include "rkGameObjectBuilder.h"
#include "rkAssetManager.h"
#include "rkSpriteComponent.h"
#include "rkEightDirAnimationDesc.h"

namespace rk
{
  GameObjectBuilder::GameObjectBuilder()
    : m_current(nullptr)
  {
  }

  GameObjectBuilder::~GameObjectBuilder()
  {
    if (m_current)
    {
      delete m_current;
      m_current = nullptr;
    }
  }

  GameObjectBuilder& GameObjectBuilder::createGameObject()
  {
    assertCurrentIsNull();
    m_current = new GameObject();
    return *this;
  }

  GameObjectBuilder& GameObjectBuilder::createGameObject(const String& name)
  {
    assertCurrentIsNull();
    m_current = new GameObject(name.c_str());
    return *this;
  }

  GameObjectBuilder& GameObjectBuilder::withPosition(const sf::Vector2f& position)
  {
    assertCurrentIsNotNull();
    m_current->setPosition(position);
    return *this;
  }

  GameObjectBuilder& GameObjectBuilder::withComponent(UniquePtr<Component> component)
  {
    assertCurrentIsNotNull();
    m_current->addComponent(std::move(component));
    return *this;
  }

  GameObject* GameObjectBuilder::buildWithParent(GameObject& parent)
  {
    assertCurrentIsNotNull();

    GameObject* builtGameObject = m_current;
    parent.addChild(UniquePtr<GameObject>(m_current));
    m_current = nullptr;

    return builtGameObject;
  }

  UniquePtr<GameObject> GameObjectBuilder::build()
  {
    assertCurrentIsNotNull();
    UniquePtr<GameObject> result(m_current);
    m_current = nullptr;
    return result;
  }

  void GameObjectBuilder::assertCurrentIsNull() const
  {
    if (m_current)
      throw RuntimeErrorException(
        "GameObjectBuilder error: Current GameObject is not null."
      );
  }

  void GameObjectBuilder::assertCurrentIsNotNull() const
  {
    if (!m_current)
      throw RuntimeErrorException(
        "GameObjectBuilder error: Current GameObject is null."
      );
  }
}