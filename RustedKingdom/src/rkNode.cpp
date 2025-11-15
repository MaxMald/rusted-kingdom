#include "rkNode.h"
#include "rkNodeLink.h"

namespace rk
{
  Node::Node() :
    m_position(0.0f, 0.0f),
    m_weight(0.0f)
  {
  }

  Node::Node(const Vector2f& position) :
    m_position(position),
    m_weight(0.0f)
  {
  }

  Node::~Node()
  {
  }

  void Node::addChild(SharedPtr<Node> child)
  {
    if (child)
    {
      float distance = (child->getPosition() - m_position).length();
      m_children.push_back(MakeShared<NodeLink>(child, distance));
    }
  }

  const Vector<SharedPtr<NodeLink>>& Node::getChildren() const
  {
    return m_children;
  }
}