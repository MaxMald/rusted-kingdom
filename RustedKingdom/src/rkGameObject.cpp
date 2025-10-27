#include "rkGameObject.h"

namespace rk
{
  GameObject::GameObject() :
    m_name("Unnamed"),
    m_parent(nullptr),
    m_children()
  {
  }

  GameObject::GameObject(const char* name) :
    m_name(name),
    m_parent(nullptr),
    m_children()
  {
  }

  GameObject::~GameObject()
  {
    clearChildren();
  }

  const char* GameObject::getName() const
  {
    return m_name;
  }

  void GameObject::update(float deltaTime)
  {
    OnUpdate();
   
    for (auto& child : m_children)
    {
      child->update(deltaTime);
    }
  }

  void GameObject::addChild(UniquePtr<GameObject> child)
  {
    if (child)
    {
      child->m_parent = this;
      m_children.push_back(std::move(child));
    }
  }

  void GameObject::clearChildren()
  {
    m_children.clear();
  }

  GameObject* GameObject::getParent() const
  {
    return m_parent;
  }

  const Vector<UniquePtr<GameObject>>& GameObject::getChildren() const
  {
    return m_children;
  }

  void GameObject::OnUpdate()
  {
    // Custom update logic can be implemented in derived classes
  }

  void GameObject::destroy()
  {
    // Custom destruction logic if needed
    clearChildren();
    // Actual deletion should be managed by the owner (scene graph/manager)
  }
}