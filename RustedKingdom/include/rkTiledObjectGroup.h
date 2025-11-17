#pragma once

#include <SFML/System/Vector2.hpp>
#include <TMR/tmrDrawOrder.h>
#include "rkPrerequisites.h"
#include "rkTiledObject.h"

using sf::Vector2i;

namespace tmr
{
  class ObjectGroup;
}

namespace rk
{
  class TiledObjectGroup
  {
  public:
    TiledObjectGroup();
    TiledObjectGroup(const tmr::ObjectGroup&);
    TiledObjectGroup(const TiledObjectGroup& other);
    TiledObjectGroup(TiledObjectGroup&& other) noexcept;
    ~TiledObjectGroup();

    TiledObjectGroup& operator=(const TiledObjectGroup& other);
    TiledObjectGroup& operator=(TiledObjectGroup&& other) noexcept;

    tmr::drawOrder::Type getDrawOrder() const { return m_drawOrder; }
    const Vector<TiledObject>& getObjects() const { return m_objects; }
    Vector<TiledObject>& getObjects() { return m_objects; }
    SizeT getSize() const { return m_objects.size(); }
    Int32 getId() const { return m_id; }
    const Vector2i& getPosition() const { return m_position; }
    bool isVisible() const { return m_visible; }
    float getOpacity() const { return m_opacity; }
    const String& getName() const { return m_name; }

  private:
    Int32 m_id;
    Vector2i m_position;
    bool m_visible;
    float m_opacity;
    String m_name;
    Vector<TiledObject> m_objects;
    tmr::drawOrder::Type m_drawOrder;
  };
}
