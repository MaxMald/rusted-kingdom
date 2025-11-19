#pragma once

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"

namespace rk
{
  class Node;

  class SearchNode : public NonCopyable
  {
  public:
    SearchNode(
      const SharedPtr<Node>& node,
      float gCost,
      float hCost
    );
    SearchNode(
      const SharedPtr<Node>& node,
      const SharedPtr<SearchNode>& parent,
      float gCost,
      float hCost
    );
    ~SearchNode();

    SharedPtr<Node> getNode() const { return m_node; }
    SharedPtr<SearchNode> getParent() const { return m_parent; }
    void setParent(const SharedPtr<SearchNode>& parent) { m_parent = parent; }
    float getGCost() const { return m_gCost; }
    void setGCost(float gCost);
    float getHCost() const { return m_hCost; }
    float getFCost() const { return m_fCost; }
    bool isWalkable() const;

  protected:
    SharedPtr<Node> m_node;
    SharedPtr<SearchNode> m_parent;
    float m_gCost;
    float m_hCost;
    float m_fCost;
  };
}