#pragma once

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"

namespace rk
{
  class Node;

  class NodeLink : public NonCopyable
  {
  public:
    NodeLink(SharedPtr<Node> node, float cost);
    virtual ~NodeLink();

    SharedPtr<Node> getNode() const;
    float getCost() const;

  private:
    SharedPtr<Node> m_node;
    float m_cost;
  };
}