#include "rkSceneGraph.h"

#include <algorithm>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "rkGameObjectBlueprint.h"

namespace rk
{
  SceneGraph::SceneGraph()
    : m_root(std::make_unique<GameObject>("Root"))
  {
    m_root->m_name = "Root";
  }

  SceneGraph::~SceneGraph()
  {
    // m_root and all children are automatically cleaned up by UniquePtr
  }

  GameObject* SceneGraph::getRoot() const
  {
    return m_root.get();
  }

  GameObject* SceneGraph::instantiateGameObject(
    const GameObjectBlueprint& blueprint,
    const Vector2f& position
  )
  {
    GameObject* newGameObject = blueprint.instantiate("", *m_root);
    newGameObject->updateTransform();
    newGameObject->setPosition(position);
    newGameObject->onCreate();
    return newGameObject;
  }

  GameObject* SceneGraph::instantiateGameObject(
    const GameObjectBlueprint& blueprint,
    const Vector2f& position,
    GameObject& parent
  )
  {
    return instantiateGameObject(blueprint, "", position, parent);
  }

  GameObject* SceneGraph::instantiateGameObject(
    const GameObjectBlueprint& blueprint,
    const String& name,
    const Vector2f& position,
    GameObject& parent
  )
  {
    GameObject* newGameObject = blueprint.instantiate(name, parent);
    newGameObject->setPosition(position);
    newGameObject->onCreate();
    return newGameObject;
  }

  void SceneGraph::update(float deltaTime)
  {
    if (m_root)
      m_root->update(deltaTime);

    m_root->updateTransform();
  }

  void SceneGraph::draw(RenderTarget& target, RenderStates states) const
  {
    m_root->draw(target, states);
  }

  void SceneGraph::destroy()
  {
    m_root = nullptr;
  }
}