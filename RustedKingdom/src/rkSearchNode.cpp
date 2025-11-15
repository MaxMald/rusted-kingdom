#include "rkSearchNode.h"
#include "rkNode.h"

namespace rk
{
  SearchNode::SearchNode(
    const SharedPtr<Node>& node,
    float gCost,
    float hCost
  ) :
    m_hCost(hCost),
    m_gCost(gCost)
  {
    if (!node)
    {
      throw InvalidArgumentException(
        "SearchNode::SearchNode: node pointer is null."
      );
    }

    m_node = node;
    m_parent = nullptr;
    m_fCost = m_gCost + m_hCost;
  }

  SearchNode::SearchNode(
    const SharedPtr<Node>& node,
    const SharedPtr<SearchNode>& parent,
    float gCost,
    float hCost
  ) :
    m_hCost(hCost),
    m_gCost(gCost)
  {
    if (!node || !parent)
    {
      throw InvalidArgumentException(
        "SearchNode::SearchNode: node or parent pointer is null."
      );
    }

    m_node = node;
    m_parent = parent;
    m_fCost = m_gCost + m_hCost;
  }

  SearchNode::~SearchNode()
  {
  }

  void SearchNode::setGCost(float gCost)
  {
    m_gCost = gCost;
    m_fCost = m_gCost + m_hCost;
  }
}