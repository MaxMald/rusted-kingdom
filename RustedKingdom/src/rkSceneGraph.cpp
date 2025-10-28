#include "rkSceneGraph.h"
#include <algorithm>

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

  void SceneGraph::draw()
  {
    Vector<GameObject*> gameObjects;
    getAllGameObjectsRecursively(m_root.get(), gameObjects);
    sortGameObjectsByYPosition(gameObjects);

    for (GameObject* gameObject : gameObjects)
      // gameObject->draw(); TODO draw using a render target and render states
  }

  void SceneGraph::getAllGameObjectsRecursively(
    GameObject* parent,
    Vector<GameObject*>& gameObjects
  )
  {
    if (!parent)
      return;

    gameObjects.push_back(parent);

    for (const auto& childPtr : parent->getChildren())
    {
      getAllGameObjectsRecursively(childPtr.get(), gameObjects);
    }
  }

  void SceneGraph::sortGameObjectsByYPosition(Vector<GameObject*>& gameObjects)
  {
    std::sort(
      gameObjects.begin(),
      gameObjects.end(),
      [](GameObject* a, GameObject* b)
      {
        return a->getPosition().y < b->getPosition().y;
      });
  }
}