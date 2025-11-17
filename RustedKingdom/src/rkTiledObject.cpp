#include "rkTiledObject.h"

#include <TMR/tmrObject.h>

namespace rk
{
    TiledObject::TiledObject() :
      m_id(0),
      m_position(0.0f, 0.0f),
      m_size(0.0f, 0.0f),
      m_ellipse(false),
      m_visible(true),
      m_type(""),
      m_name(""),
      m_rotation(0.0f)
    {
    }

    TiledObject::TiledObject(const tmr::Object& tmrObject) :
    m_id(tmrObject.getId()),
    m_position(tmrObject.getX(), tmrObject.getY()),
    m_size(
      static_cast<float>(tmrObject.getWidth()),
      static_cast<float>(tmrObject.getHeight())
    ),
    m_ellipse(tmrObject.isEllipse()),
    m_visible(tmrObject.isVisible()),
    m_type(tmrObject.getType()),
    m_name(tmrObject.getName()),
    m_rotation(tmrObject.getRotation())
  {
  }

  TiledObject::TiledObject(const TiledObject& other) :
    m_id(other.m_id),
    m_position(other.m_position),
    m_size(other.m_size),
    m_ellipse(other.m_ellipse),
    m_visible(other.m_visible),
    m_type(other.m_type),
    m_name(other.m_name),
    m_rotation(other.m_rotation)
  {
  }

  TiledObject::TiledObject(TiledObject&& other) noexcept :
    m_id(other.m_id),
    m_position(std::move(other.m_position)),
    m_size(std::move(other.m_size)),
    m_ellipse(other.m_ellipse),
    m_visible(other.m_visible),
    m_type(std::move(other.m_type)),
    m_name(std::move(other.m_name)),
    m_rotation(other.m_rotation)
  {
  }

  TiledObject::~TiledObject()
  {
  }

  TiledObject& TiledObject::operator=(const TiledObject& other)
  {
    if (this != &other)
    {
      m_id = other.m_id;
      m_position = other.m_position;
      m_size = other.m_size;
      m_ellipse = other.m_ellipse;
      m_visible = other.m_visible;
      m_type = other.m_type;
      m_name = other.m_name;
      m_rotation = other.m_rotation;
    }
    return *this;
  }

  TiledObject& TiledObject::operator=(TiledObject&& other) noexcept
  {
    if (this != &other)
    {
      m_id = other.m_id;
      m_position = std::move(other.m_position);
      m_size = std::move(other.m_size);
      m_ellipse = other.m_ellipse;
      m_visible = other.m_visible;
      m_type = std::move(other.m_type);
      m_name = std::move(other.m_name);
      m_rotation = other.m_rotation;
    }
    return *this;
  }
}