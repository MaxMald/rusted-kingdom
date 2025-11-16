#include "rkNodeMesh.h"

namespace rk
{
  NodeMesh::NodeMesh(
    UInt32 width,
    UInt32 height,
    UInt32 xSpacing,
    UInt32 ySpacing
  ) :
    m_width(width),
    m_height(height),
    m_xSpacing(xSpacing),
    m_ySpacing(ySpacing)
  {
    m_nodes.reserve(width * height);
    for (UInt32 y = 0; y < height; ++y)
    {
      for (UInt32 x = 0; x < width; ++x)
      {
        m_nodes.push_back(MakeShared<Node>(
          Vector2f(
            static_cast<float>(x * xSpacing),
            static_cast<float>(y * ySpacing))
          )
        );
      }
    }

    for (UInt32 x = 0; x < width; ++x)
    {
      for (UInt32 y = 0; y < height; ++y)
      {
        SharedPtr<Node> currentNode = getNodeAt(x, y);

        if (x + 1 < width) // right neighbor
        {
          currentNode->addChild(getNodeAt(x + 1, y));
        }
        if (y + 1 < height) // bottom neighbor
        {
          currentNode->addChild(getNodeAt(x, y + 1));
        }
        if (x > 0) // left neighbor
        {
          currentNode->addChild(getNodeAt(x - 1, y));
        }
        if (y > 0) // top neighbor
        {
          currentNode->addChild(getNodeAt(x, y - 1));
        }
      }
    }
  }

  NodeMesh::~NodeMesh()
  {
  }

  SharedPtr<Node> NodeMesh::getNodeAt(UInt32 x, UInt32 y)
  {
    assertValidCoordinates(x, y);
    return m_nodes[m_width * y + x];
  }

  const SharedPtr<Node> NodeMesh::getNodeAt(UInt32 x, UInt32 y) const
  {
    assertValidCoordinates(x, y);
    return m_nodes[m_width * y + x];
  }

  void NodeMesh::assertValidCoordinates(UInt32 x, UInt32 y) const
  {
    if (x >= m_width || y >= m_height)
    {
      throw OutOfRangeException(
        "NodeMesh::assertValidCoordinates - Coordinates out of range"
      );
    }
  }
}