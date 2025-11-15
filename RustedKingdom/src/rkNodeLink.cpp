#include "rkNodeLink.h"
#include "rkNode.h"

namespace rk
{
  NodeLink::NodeLink(SharedPtr<Node> node, float cost) :
    m_node(node),
    m_cost(cost)
  {
  }

  NodeLink::~NodeLink()
  {
  }

  SharedPtr<Node> NodeLink::getNode() const
  {
    return m_node;
  }

  float NodeLink::getCost() const
  {
    return m_cost;
  }
}