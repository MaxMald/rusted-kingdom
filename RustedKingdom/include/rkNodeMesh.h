#pragma once

#include "rkNode.h"
#include "rkNonCopyable.h"

namespace rk
{
  class NodeMesh : public NonCopyable
  {
  public:
    NodeMesh();
    NodeMesh(
      UInt32 width,
      UInt32 height,
      UInt32 xSpacing,
      UInt32 ySpacing
    );
    virtual ~NodeMesh();

    SharedPtr<Node> getNodeAt(UInt32 x, UInt32 y);
    const SharedPtr<Node> getNodeAt(UInt32 x, UInt32 y) const;
    UInt32 getWidth() const { return m_width; }
    UInt32 getHeight() const { return m_height; }

    virtual void init(
      UInt32 width,
      UInt32 height,
      UInt32 xSpacing,
      UInt32 ySpacing
    );

    virtual void clear();

  protected:
    UInt32 m_width;
    UInt32 m_height;
    UInt32 m_xSpacing;
    UInt32 m_ySpacing;
    Vector<SharedPtr<Node>> m_nodes;

    void assertValidCoordinates(UInt32 x, UInt32 y) const;
  };
}