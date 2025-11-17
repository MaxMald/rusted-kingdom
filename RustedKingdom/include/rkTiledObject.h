#pragma once

#include <SFML/System/Vector2.hpp>
#include "rkPrerequisites.h"

using sf::Vector2f;

namespace tmr
{
  class Object;
}

namespace rk
{
  class TiledObject
  {
  public:
    TiledObject();
    TiledObject(const tmr::Object&);
    TiledObject(const TiledObject&);
    TiledObject(TiledObject&&) noexcept;
    ~TiledObject();

    TiledObject& operator=(const TiledObject&);
    TiledObject& operator=(TiledObject&&) noexcept;

    UInt32 getId() const { return m_id; }
    const Vector2f& getPosition() const { return m_position; }
    const Vector2f& getSize() const { return m_size; }
    bool isEllipse() const { return m_ellipse; }
    bool isVisible() const { return m_visible; }
    const String& getType() const { return m_type; }
    const String& getName() const { return m_name; }
    float getRotation() const { return m_rotation; }

  private:
    UInt32 m_id;
    Vector2f m_position;
    Vector2f m_size;
    bool m_ellipse;
    bool m_visible;
    String m_type;
    String m_name;
    float m_rotation;
  };
}