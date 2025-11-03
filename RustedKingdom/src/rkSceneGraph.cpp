#include "rkSceneGraph.h"
#include <algorithm>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

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

  void SceneGraph::update(float deltaTime)
  {
    if (m_root)
      m_root->update(deltaTime);
  }

  void SceneGraph::draw(RenderTarget& target, RenderStates states) const
  {
    m_root->updateTransform();

    Vector<GameObject*> sortedGameObjects;
    getAllGameObjectsRecursively(m_root.get(), sortedGameObjects);
    sortGameObjectsByYPosition(sortedGameObjects);

    for (GameObject* gameObject : sortedGameObjects)
      target.draw(*gameObject, states);
  }

  void SceneGraph::getAllGameObjectsRecursively(
    GameObject* parent,
    Vector<GameObject*>& gameObjects
  ) const
  {
    if (!parent)
      return;

    gameObjects.push_back(parent);

    for (const auto& childPtr : parent->getChildren())
    {
      getAllGameObjectsRecursively(childPtr.get(), gameObjects);
    }
  }

  void SceneGraph::sortGameObjectsByYPosition(
    Vector<GameObject*>& gameObjects
  ) const
  {
    std::sort(
      gameObjects.begin(),
      gameObjects.end(),
      [](GameObject* a, GameObject* b)
      {
        const sf::Vector2f aWorld = a->m_worldTransform.transformPoint(sf::Vector2f(0.0f, 0.0f));
        const sf::Vector2f bWorld = b->m_worldTransform.transformPoint(sf::Vector2f(0.0f, 0.0f));

        if (aWorld.y != bWorld.y)
          return aWorld.y < bWorld.y;

        // tie-breaker by world X (left objects drawn first) for deterministic
        // order
        if (aWorld.x != bWorld.x)
          return aWorld.x < bWorld.x;

        // final tie-breaker by pointer address
        return a < b;
      });
  }
}