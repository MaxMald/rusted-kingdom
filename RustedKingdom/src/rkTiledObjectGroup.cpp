#include "rkTiledObjectGroup.h"

#include <TMR/tmrObjectGroup.h>

namespace rk
{
  TiledObjectGroup::TiledObjectGroup() :
    m_id(0),
    m_position(0, 0),
    m_visible(true),
    m_opacity(1.0f),
    m_name(""),
    m_drawOrder(tmr::drawOrder::Type::TopDown)
  {
  }

  TiledObjectGroup::TiledObjectGroup(const tmr::ObjectGroup& objectGroup) :
    m_id(objectGroup.getId()),
    m_position(objectGroup.getX(), objectGroup.getY()),
    m_visible(objectGroup.isVisible()),
    m_opacity(objectGroup.getOpacity()),
    m_name(objectGroup.getName()),
    m_drawOrder(objectGroup.getDrawOrder())
  {
    SizeT objSize = objectGroup.getObjectSize();
    m_objects.reserve(objSize);

    for (SizeT objIndex = 0; objIndex < objSize; ++objIndex)
    {
      const tmr::Object* tmrObject = objectGroup
        .getObjectAt(static_cast<UInt32>(objIndex));

      TiledObject tiledObject(*tmrObject);
      m_objects.push_back(tiledObject);
    }
  }

  TiledObjectGroup::TiledObjectGroup(const TiledObjectGroup& other) :
    m_id(other.m_id),
    m_position(other.m_position),
    m_visible(other.m_visible),
    m_opacity(other.m_opacity),
    m_name(other.m_name),
    m_objects(other.m_objects),
    m_drawOrder(other.m_drawOrder)
  {
  }

  TiledObjectGroup::TiledObjectGroup(TiledObjectGroup&& other) noexcept :
    m_id(other.m_id),
    m_position(std::move(other.m_position)),
    m_visible(other.m_visible),
    m_opacity(other.m_opacity),
    m_name(std::move(other.m_name)),
    m_objects(std::move(other.m_objects)),
    m_drawOrder(other.m_drawOrder)
  {
  }

  TiledObjectGroup::~TiledObjectGroup()
  {
  }

  TiledObjectGroup& TiledObjectGroup::operator=(const TiledObjectGroup& other)
  {
    if (this != &other)
    {
      m_id = other.m_id;
      m_position = other.m_position;
      m_visible = other.m_visible;
      m_opacity = other.m_opacity;
      m_name = other.m_name;
      m_objects = other.m_objects;
      m_drawOrder = other.m_drawOrder;
    }
    return *this;
  }

  TiledObjectGroup& TiledObjectGroup::operator=(TiledObjectGroup&& other) noexcept
  {
    if (this != &other)
    {
      m_id = other.m_id;
      m_position = std::move(other.m_position);
      m_visible = other.m_visible;
      m_opacity = other.m_opacity;
      m_name = std::move(other.m_name);
      m_objects = std::move(other.m_objects);
      m_drawOrder = other.m_drawOrder;
    }
    return *this;
  }
}