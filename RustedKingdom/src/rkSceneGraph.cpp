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

    m_root->updateTransform();
  }

  void SceneGraph::draw(RenderTarget& target, RenderStates states) const
  {
    m_root->draw(target, states);
  }
}