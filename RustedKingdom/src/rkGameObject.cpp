#include "rkGameObject.h"

#include <SFML/Graphics/RenderStates.hpp>

#include "rkComponent.h"
#include "rkScriptComponent.h"

namespace rk
{
  GameObject::GameObject() :
    m_name("Unnamed"),
    m_parent(nullptr),
    m_children(),
    m_worldTransform(),
    m_components()
  {
  }

  GameObject::GameObject(const char* name) :
    m_name(name),
    m_parent(nullptr),
    m_children(),
    m_worldTransform(),
    m_components()
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

  void GameObject::addComponent(UniquePtr<Component> component)
  {
    if (component)
      m_components.push_back(std::move(component));
  }

  bool GameObject::hasComponent(componentType::Type type) const
  {
    for (const auto& comp : m_components)
    {
      if (comp->getType() == type)
        return true;
    }
    return false;
  }

  bool GameObject::hasScriptComponentWithName(const String& scriptName) const
  {
    Vector<const ScriptComponent*> scripts = getComponents<ScriptComponent>(
      componentType::Type::Script
    );

    for (const auto& script : scripts)
    {
      if (script->getScriptName() == scriptName)
        return true;
    }

    return false;
  }

  ScriptComponent* GameObject::getScriptComponentWithName(const String& scriptName)
  {
    Vector<ScriptComponent*> scripts = getComponents<ScriptComponent>(
      componentType::Type::Script
    );

    for (const auto& script : scripts)
    {
      if (script->getScriptName() == scriptName)
        return script;
    }

    return nullptr;
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
    for (auto& component: m_components)
      component->onUpdate(deltaTime);

    for (auto& child : m_children)
      child->update(deltaTime);
  }

  void GameObject::draw(RenderTarget& target, RenderStates states) const
  {
    states.transform *= m_worldTransform;

    for (auto& component : m_components)
      component->onDraw(target, states);

    for (auto& child : m_children)
      child->draw(target, states);
  }

  void GameObject::onDelete()
  {
    for (auto& component : m_components)
      component->onDelete();
    m_components.clear();
  }
}