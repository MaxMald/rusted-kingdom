#include "rkTiledObjectSpriteDescriptor.h"

namespace rk
{
  TiledObjectSpriteDescriptor::TiledObjectSpriteDescriptor() :
    m_gid(0),
    m_textureKey(),
    m_rect(),
    m_origin(0.0f, 0.0f)
  {
  }

  TiledObjectSpriteDescriptor::TiledObjectSpriteDescriptor(
    Int32 gid,
    const String& textureKey,
    const IntRect& rect,
    const Vector2f& origin
  ) :
    m_gid(gid),
    m_textureKey(textureKey),
    m_rect(rect),
    m_origin(origin)
  {
  }

  TiledObjectSpriteDescriptor::~TiledObjectSpriteDescriptor()
  {
  }

  TiledObjectSpriteDescriptor::TiledObjectSpriteDescriptor(
    const TiledObjectSpriteDescriptor& other
  ) : m_gid(other.m_gid),
    m_textureKey(other.m_textureKey),
    m_rect(other.m_rect),
    m_origin(other.m_origin)
  {
  }

  TiledObjectSpriteDescriptor& TiledObjectSpriteDescriptor::operator=(
    const TiledObjectSpriteDescriptor& other
    )
  {
    if (this != &other)
    {
      m_gid = other.m_gid;
      m_textureKey = other.m_textureKey;
      m_rect = other.m_rect;
      m_origin = other.m_origin;
    }
    return *this;
  }

  TiledObjectSpriteDescriptor::TiledObjectSpriteDescriptor(
    TiledObjectSpriteDescriptor&& other
  ) noexcept :
    m_gid(other.m_gid),
    m_textureKey(std::move(other.m_textureKey)),
    m_rect(other.m_rect),
    m_origin(other.m_origin)
  {
    other.m_gid = 0;
    other.m_rect = IntRect();
    other.m_origin = Vector2f();
  }

  TiledObjectSpriteDescriptor& TiledObjectSpriteDescriptor::operator=(
    TiledObjectSpriteDescriptor&& other
    ) noexcept
  {
    if (this != &other)
    {
      m_gid = other.m_gid;
      m_textureKey = std::move(other.m_textureKey);
      m_rect = other.m_rect;
      m_origin = other.m_origin;
      other.m_gid = 0;
      other.m_rect = IntRect();
      other.m_origin = Vector2f();
    }
    return *this;
  }
}
