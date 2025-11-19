#pragma once

#include <SFML/System/Vector2.hpp>

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"

using sf::Vector2f;

namespace rk
{
  class NodeLink;

  class Node : public NonCopyable
  {
  public:
    Node();
    Node(const Vector2f& position);
    ~Node();

    Vector2f& getPosition() { return m_position; }
    Vector2f getPosition() const { return m_position; }
    float getWeight() const { return m_weight; }
    void setWeight(float weight) { m_weight = weight; }
    bool isWalkable() const { return m_walkable; }
    void setWalkable(bool walkable) { m_walkable = walkable; }

    void addChild(SharedPtr<Node> child);
    const Vector<SharedPtr<NodeLink>>& getChildren() const;

  protected:
    Vector<SharedPtr<NodeLink>> m_children;
    Vector2f m_position;
    float m_weight;
    bool m_walkable;
  };
}
