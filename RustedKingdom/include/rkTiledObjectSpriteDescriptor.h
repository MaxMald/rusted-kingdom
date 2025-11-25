#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include "rkPrerequisites.h"

using sf::IntRect;
using sf::Vector2f;

namespace rk
{
  class TiledObjectSpriteDescriptor
  {
  public:
    TiledObjectSpriteDescriptor();
    TiledObjectSpriteDescriptor(
      Int32 gid,
      const String& textureKey,
      const IntRect& rect,
      const Vector2f& origin
    );
    ~TiledObjectSpriteDescriptor();

    TiledObjectSpriteDescriptor(const TiledObjectSpriteDescriptor& other);
    TiledObjectSpriteDescriptor& operator=(const TiledObjectSpriteDescriptor& other);

    TiledObjectSpriteDescriptor(TiledObjectSpriteDescriptor&& other) noexcept;
    TiledObjectSpriteDescriptor& operator=(TiledObjectSpriteDescriptor&& other) noexcept;

    Int32 getGid() const { return m_gid; }
    const String& getTextureKey() const { return m_textureKey; }
    const IntRect& getRect() const { return m_rect; }
    const Vector2f& getOrigin() const { return m_origin; }
    void setOrigin(float x, float y) { m_origin = Vector2f(x, y); }

  private:
    Int32 m_gid;
    String m_textureKey;
    IntRect m_rect;
    Vector2f m_origin;
  };
}