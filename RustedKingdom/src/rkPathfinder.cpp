#include "rkPathfinder.h"

#include <cmath>

#include "rkSearchNode.h"
#include "rkNode.h"
#include "rkNodeLink.h"

using std::round;

namespace 
{
  constexpr rk::UInt32 QuadTreeNodeCapacity = 4;
}

namespace rk
{
  Pathfinder::Pathfinder() :
    NodeMesh(),
    m_quadTree(nullptr)
  {
  }

  Pathfinder::Pathfinder(
    UInt32 width,
    UInt32 height,
    UInt32 xSpacing,
    UInt32 ySpacing
  ) : NodeMesh()
  {
    init(width, height, xSpacing, ySpacing);
  }

  Pathfinder::~Pathfinder()
  {
  }

  void Pathfinder::init(
    UInt32 width,
    UInt32 height,
    UInt32 xSpacing,
    UInt32 ySpacing
  )
  {
    NodeMesh::init(width, height, xSpacing, ySpacing);

    if (width == 0 || height == 0 || xSpacing == 0 || ySpacing == 0)
    {
      throw InvalidArgumentException(
        "Pathfinder::init: width, height, xSpacing, and ySpacing must be greater than zero."
      );
    }

    updateQuadTree();
  }

  void Pathfinder::clear()
  {
    NodeMesh::clear();
    clearLists();
    m_quadTree = nullptr;
  }

  Vector<Vector2f> Pathfinder::findPath(
    const Vector2f& start,
    const Vector2f& end
  )
  {
    if (m_nodes.empty())
      return {};

    clearLists();

    SharedPtr<Node> startNode = getClosestNodeToPosition(start);
    SharedPtr<Node> endNode = getClosestNodeToPosition(end);

    if (!startNode || !endNode)
      return {};

    openList.push_back(createStartSearchNode(startNode, end));

    while (!openList.empty())
    {
      sortOpenListByFCost();
      SharedPtr<SearchNode> currentNode = getNextNodeFromOpenList();

      // Goal check
      if (currentNode->getNode() == endNode)
      {
        Vector<Vector2f> path = reconstructPath(currentNode);
        removeEndNodePositionIfNotWalkable(path, endNode);
        addStartAndEndPositionsToPath(path, start, end);
        return path;
      }

      // For each child (neighbor)
      for (const auto& nodeLink : currentNode->getNode()->getChildren())
      {
        // Skip nodes already in closed list
        if (isNodeInList(nodeLink->getNode(), closedList))
          continue;

        // Skip non-walkable nodes (except the end node)
        if (nodeLink->getNode() != endNode && !nodeLink->getNode()->isWalkable())
          continue;

        // Check if already in open list
        auto openIt = std::find_if(
          openList.begin(), openList.end(),
          [&](const SharedPtr<SearchNode>& n) { return n->getNode() == nodeLink->getNode(); }
        );

        if (openIt == openList.end())
        {
          // Not in open list, add new search node
          SharedPtr<SearchNode> neighborNode = createSearchNode(
            nodeLink,
            currentNode,
            end
          );

          openList.push_back(neighborNode);
        }
        else
        {
          float tentativeGCost = calculateGCost(currentNode, nodeLink);

          // In open list, check if this path is better
          if (tentativeGCost < (*openIt)->getGCost())
          {
            (*openIt)->setParent(currentNode);
            (*openIt)->setGCost(tentativeGCost);
          }
        }
      }
    }

    // No path found
    return {};
  }

  void Pathfinder::updateQuadTree()
  {
    m_quadTree = nullptr;

    FloatRect bounds = getNodeMeshBounds();
    if (bounds.size.x == 0.0f || bounds.size.y == 0.0f)
      return;

    auto positionGetter = [&](SharedPtr<Node> node) {
      return node->getPosition();
    };

    m_quadTree = MakeShared<QuadTree<SharedPtr<Node>>>(
      bounds,
      QuadTreeNodeCapacity,
      positionGetter
    );

    for (const auto& node : m_nodes)
      m_quadTree->insert(node);
  }

  void Pathfinder::clearLists()
  {
    openList.clear();
    closedList.clear();
  }

  void Pathfinder::sortOpenListByFCost()
  {
    std::sort(
      openList.begin(),
      openList.end(),
      [](const SharedPtr<SearchNode>& a, const SharedPtr<SearchNode>& b)
      {
        float aFCost = a->getFCost();
        float bFCost = b->getFCost();

        if (aFCost != bFCost)
          return aFCost < bFCost;
        else
          return a->getHCost() < b->getHCost();
      }
    );
  }

  SharedPtr<SearchNode> Pathfinder::getNextNodeFromOpenList()
  {
    if (openList.empty())
    {
      throw RuntimeErrorException(
        "Pathfinder::getNextNodeFromOpenList: open list is empty."
      );
    }

    SharedPtr<SearchNode> currentNode = openList.front();
    openList.erase(openList.begin());
    closedList.push_back(currentNode);

    return currentNode;
  }

  FloatRect Pathfinder::getNodeMeshBounds() const
  {
    Vector2f minPos(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
    Vector2f maxPos(std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest());
    bool found = false;

    for (UInt32 y = 0; y < m_height; ++y)
    {
      for (UInt32 x = 0; x < m_width; ++x)
      {
        SharedPtr<Node> node = getNodeAt(x, y);
        if (node)
        {
          found = true;
          Vector2f nodePos = node->getPosition();
          minPos.x = std::min(minPos.x, nodePos.x);
          minPos.y = std::min(minPos.y, nodePos.y);
          maxPos.x = std::max(maxPos.x, nodePos.x);
          maxPos.y = std::max(maxPos.y, nodePos.y);
        }
      }
    }

    if (!found)
      return FloatRect();

    return FloatRect(
      minPos,
      Vector2f(
        maxPos.x - minPos.x,
        maxPos.y - minPos.y
      )
    );
  }

  bool Pathfinder::isNodeInList(
    const SharedPtr<Node>& node,
    const Vector<SharedPtr<SearchNode>>& list
  ) const
  {
    return std::any_of(
      list.begin(), list.end(),
      [&](const SharedPtr<SearchNode>& n) { return n->getNode() == node; }
    );
  }

  Vector<Vector2f> Pathfinder::reconstructPath(
    const SharedPtr<SearchNode>& endNode
  ) const
  {
    Vector<Vector2f> path;
    SharedPtr<SearchNode> currentNode = endNode;
    while (currentNode)
    {
      path.push_back(currentNode->getNode()->getPosition());
      currentNode = currentNode->getParent();
    }
    std::reverse(path.begin(), path.end());
    return path;
  }

  SharedPtr<SearchNode> Pathfinder::createStartSearchNode(
    const SharedPtr<Node>& node,
    const Vector2f& endPosition
  )
  {
    if (!node)
    {
      throw InvalidArgumentException(
        "Pathfinder::createSearchNode: node pointer is null."
      );
    }

    return MakeShared<SearchNode>(
      node,
      0.0f,
      calculateHeuristicCost(node->getPosition(), endPosition)
    );
  }

  SharedPtr<SearchNode> Pathfinder::createSearchNode(
    const SharedPtr<NodeLink>& nodeLink,
    const SharedPtr<SearchNode>& parent,
    const Vector2f& endPosition
  ) const
  {
    if (!nodeLink || !parent)
    {
      throw InvalidArgumentException(
        "Pathfinder::createSearchNode: node or parent pointer is null."
      );
    }

    SharedPtr<Node> node = nodeLink->getNode();
    return MakeShared<SearchNode>(
      node,
      parent,
      calculateGCost(parent, nodeLink),
      calculateHeuristicCost(node->getPosition(), endPosition)
    );
  }

  float Pathfinder::calculateHeuristicCost(
    const Vector2f& fromPosition,
    const Vector2f& toPosition
  ) const
  {
    Vector2f diff = toPosition - fromPosition;
    return diff.length();
  }

  float Pathfinder::calculateGCost(
    const SharedPtr<SearchNode>& parent,
    const SharedPtr<NodeLink>& nodeLink
  ) const
  {
    return parent->getGCost() +
      nodeLink->getNode()->getWeight() +
      nodeLink->getCost();
  }

  SharedPtr<Node> Pathfinder::getClosestNodeToPosition(
    const Vector2f& position
  ) const
  {
    if (!m_quadTree)
      return nullptr;

    Vector<SharedPtr<Node>> foundNodes;
    m_quadTree->query(position, foundNodes);

    if (foundNodes.empty())
      return nullptr;

    float closestDistance = std::numeric_limits<float>::max();
    SharedPtr<Node> closestNode = nullptr;

    for (const auto& node : foundNodes)
    {
      Vector2f nodePos = node->getPosition();
      float distance = (nodePos - position).length();
      if (distance < closestDistance)
      {
        closestDistance = distance;
        closestNode = node;
      }
    }

    return closestNode;
  }

  void Pathfinder::removeEndNodePositionIfNotWalkable(
    Vector<Vector2f>& path,
    const SharedPtr<Node>& endNode
  ) const
  {
    if (!endNode->isWalkable())
      path.pop_back();
  }

  void Pathfinder::addStartAndEndPositionsToPath(
    Vector<Vector2f>& path,
    const Vector2f& start,
    const Vector2f& end
  ) const
  {
    if (path.size() < 2)
      return;

    // If the distance between the first node and the start position is less than
    // the distance between the first node and the next node, replace the first
    // node with the start position.

    Vector2f firstNodePos = path.front();
    Vector2f nextNodePos = path[1];

    float dtFirstToNext = (nextNodePos - firstNodePos).length();
    float dtStartToNext = (firstNodePos - start).length();

    if (dtStartToNext < dtFirstToNext)
      path[0] = start;

    // If the distance between the last node and the end position is less than
    // the distance between the last node and the previous node, replace the last
    // node with the end position. Otherwise, append the end position.

    Vector2f lastNodePos = path.back();
    Vector2f prevNodePos = path[path.size() - 2];

    float dtLastToPrev = (lastNodePos - prevNodePos).length();
    float dtLastToEnd = (lastNodePos - end).length();

    if (dtLastToEnd < dtLastToPrev)
      path.back() = end;
    else
      path.push_back(end);
  }
}