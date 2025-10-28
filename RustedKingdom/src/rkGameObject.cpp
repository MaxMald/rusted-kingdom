#include "rkGameObject.h"
#include <SFML/Graphics/RenderStates.hpp>

namespace rk
{
  GameObject::GameObject() :
    m_name("Unnamed"),
    m_parent(nullptr),
    m_children(),
    m_worldTransform()
  {
  }

  GameObject::GameObject(const char* name) :
    m_name(name),
    m_parent(nullptr),
    m_children(),
    m_worldTransform()
  {
  }

  GameObject::~GameObject()
  {
    onDelete();
    clearChildren();
  }

  const char* GameObject::getName() const
  {
    return m_name;
  }

  void GameObject::addChild(UniquePtr<GameObject> child)
  {
    if (!child)
      return;

    if (child->m_parent == this)
      return;

    child->m_parent = this;
    m_children.push_back(std::move(child));
  }

  UniquePtr<GameObject> GameObject::removeChild(GameObject* child)
  {
    for (auto it = m_children.begin(); it != m_children.end(); ++it)
    {
      if (it->get() == child)
      {
        child->m_parent = nullptr;
        UniquePtr<GameObject> removedChild = std::move(*it);
        m_children.erase(it);
        return removedChild;
      }
    }

    return nullptr;
  }

  UniquePtr<GameObject> GameObject::detachFromParent()
  {
    if (m_parent)
      return m_parent->removeChild(this);

    return nullptr;
  }

  void GameObject::clearChildren()
  {
    m_children.clear();
  }

  GameObject* GameObject::findChildByName(const char* name)
  {
    for (auto& child : m_children)
    {
      if (child->getName() && std::strcmp(child->getName(), name) == 0)
        return child.get();

      GameObject* found = child->findChildByName(name);
      if (found)
        return found;
    }
    return nullptr;
  }

  GameObject* GameObject::getParent() const
  {
    return m_parent;
  }

  const Vector<UniquePtr<GameObject>>& GameObject::getChildren() const
  {
    return m_children;
  }

  void GameObject::updateTransform()
  {
    if (m_parent)
      m_worldTransform = m_parent->getTransform() * getTransform();
    else
      m_worldTransform = getTransform();

    for (auto& child : m_children)
      child->updateTransform();
  }

  void GameObject::update(float deltaTime)
  {
    onUpdate(deltaTime);

    for (auto& child : m_children)
      child->update(deltaTime);
  }

  void GameObject::draw(RenderTarget& target, RenderStates states) const
  {
    (void)target;
    (void)states;

    // Custom drawing logic for derived classes can be implemented here.
  }

  void GameObject::onUpdate(float deltaTime)
  {
    (void)deltaTime;

    // Custom update logic for derived classes can be implemented here.
  }

  void GameObject::onDelete()
  {
    // Custom deletion logic for derived classes can be implemented here.
  }
}