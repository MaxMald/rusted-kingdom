#pragma once

#include "rkNodeMesh.h"

namespace rk
{
  class SearchNode;
  class NodeLink;

  class Pathfinder : public NodeMesh
  {
  public:
    Pathfinder();
    Pathfinder(
      UInt32 width,
      UInt32 height,
      UInt32 xSpacing,
      UInt32 ySpacing
    );
    virtual ~Pathfinder();

    virtual void init(
      UInt32 width,
      UInt32 height,
      UInt32 xSpacing,
      UInt32 ySpacing
    ) override;

    virtual void clear() override;

    Vector<Vector2f> findPath(
      const Vector2f& start,
      const Vector2f& end
    );

  private:
    Vector<SharedPtr<SearchNode>> openList;
    Vector<SharedPtr<SearchNode>> closedList;
    float m_meshWidth;
    float m_meshHeight;
    float m_1OverXSpacing;
    float m_1OverYSpacing;

    void clearLists();
    void sortOpenListByFCost();
    SharedPtr<SearchNode> getNextNodeFromOpenList();

    bool isNodeInList(
      const SharedPtr<Node>& node,
      const Vector<SharedPtr<SearchNode>>& list
    ) const;

    Vector<Vector2f> reconstructPath(
      const SharedPtr<SearchNode>& endNode
    ) const;

    SharedPtr<SearchNode> createStartSearchNode(
      const SharedPtr<Node>& node,
      const Vector2f& endPosition
    );

    SharedPtr<SearchNode> createSearchNode(
      const SharedPtr<NodeLink>& nodeLink,
      const SharedPtr<SearchNode>& parent,
      const Vector2f& endPosition
    ) const;

    float calculateHeuristicCost(
      const Vector2f& fromPosition,
      const Vector2f& toPosition
    ) const;

    float calculateGCost(
      const SharedPtr<SearchNode>& parent,
      const SharedPtr<NodeLink>& targetNode
    ) const;

    SharedPtr<Node> getClosestNodeToPosition(
      const Vector2f& position
    ) const;

    void removeEndNodePositionIfNotWalkable(
      Vector<Vector2f>& path,
      const SharedPtr<Node>& endNode
    ) const;

    void addStartAndEndPositionsToPath(
      Vector<Vector2f>& path,
      const Vector2f& start,
      const Vector2f& end
    ) const;
  };
}