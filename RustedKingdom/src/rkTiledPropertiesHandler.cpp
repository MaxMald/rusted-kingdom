#include "rkTiledPropertiesHandler.h"

#include <TMR/tmrBoolProperty.h>
#include <TMR/tmrColorProperty.h>
#include <TMR/tmrFileProperty.h>
#include <TMR/tmrFloatProperty.h>
#include <TMR/tmrIntProperty.h>
#include <TMR/tmrObjectProperty.h>
#include <TMR/tmrStringProperty.h>
#include <TMR/tmrProperties.h>

namespace rk
{
  TiledPropertiesHandler::TiledPropertiesHandler() :
    m_properties(nullptr)
  {
  }

  TiledPropertiesHandler::TiledPropertiesHandler(
    const tmr::Properties* properties
  ) : m_properties(properties)
  {
  }

  TiledPropertiesHandler::~TiledPropertiesHandler()
  {
  }

  TiledPropertiesHandler::TiledPropertiesHandler(
    const TiledPropertiesHandler& other
  ) : m_properties(other.m_properties)
  {
  }

  TiledPropertiesHandler& TiledPropertiesHandler::operator=(
    const TiledPropertiesHandler& other
  )
  {
    if (this != &other)
      m_properties = other.m_properties;

    return *this;
  }

  TiledPropertiesHandler::TiledPropertiesHandler(
    TiledPropertiesHandler&& other
  ) noexcept : m_properties(other.m_properties)
  {
    other.m_properties = nullptr;
  }

  TiledPropertiesHandler& TiledPropertiesHandler::operator=(
    TiledPropertiesHandler&& other
  ) noexcept
  {
    if (this != &other)
    {
      m_properties = other.m_properties;
      other.m_properties = nullptr;
    }

    return *this;
  }

  bool TiledPropertiesHandler::hasProperty(const String& name) const
  {
    return findPropertyByName(name) != nullptr;
  }

  bool TiledPropertiesHandler::tryGetBool(
    const String& name,
    bool& outValue
  ) const
  {
    const tmr::Property* property = findPropertyByName(name);
    if (!property)
      return false;

    if (property->getType() != tmr::propertyType::Bool)
      return false;

    outValue = static_cast<const tmr::BoolProperty*>(property)->getValue();
    return true;
  }

  bool TiledPropertiesHandler::tryGetColor(
    const String& name,
    String& outValue
  ) const
  {
    const tmr::Property* property = findPropertyByName(name);
    if (!property)
      return false;

    if (property->getType() != tmr::propertyType::Color)
      return false;

    outValue = static_cast<const tmr::ColorProperty*>(property)->getValue();
    return true;
  }

  bool TiledPropertiesHandler::tryGetFile(
    const String& name,
    String& outValue
  ) const
  {
    const tmr::Property* property = findPropertyByName(name);
    if (!property)
      return false;

    if (property->getType() != tmr::propertyType::File)
      return false;

    outValue = static_cast<const tmr::FileProperty*>(property)->getValue();
    return true;
  }

  bool TiledPropertiesHandler::tryGetFloat(
    const String& name,
    float& outValue
  ) const
  {
    const tmr::Property* property = findPropertyByName(name);
    if (!property)
      return false;

    if (property->getType() != tmr::propertyType::Float)
      return false;

    outValue = static_cast<const tmr::FloatProperty*>(property)->getValue();
    return true;
  }

  bool TiledPropertiesHandler::tryGetInt(
    const String& name,
    Int32& outValue
  ) const
  {
    const tmr::Property* property = findPropertyByName(name);
    if (!property)
      return false;

    if (property->getType() != tmr::propertyType::Int)
      return false;

    outValue = static_cast<const tmr::IntProperty*>(property)->getValue();
    return true;
  }

  bool TiledPropertiesHandler::tryGetObject(
    const String& name,
    Int32& outValue
  ) const
  {
    const tmr::Property* property = findPropertyByName(name);
    if (!property)
      return false;

    if (property->getType() != tmr::propertyType::Object)
      return false;

    outValue = static_cast<const tmr::ObjectProperty*>(property)->getValue();
    return true;
  }

  bool TiledPropertiesHandler::tryGetString(
    const String& name,
    String& outValue
  ) const
  {
    const tmr::Property* property = findPropertyByName(name);
    if (!property)
      return false;

    if (property->getType() != tmr::propertyType::String)
      return false;

    outValue = static_cast<const tmr::StringProperty*>(property)->getValue();
    return true;
  }

  SizeT TiledPropertiesHandler::getSize() const
  {
    if (!m_properties)
      return 0;

    return m_properties->getPropertyCount();
  }

  const tmr::Property* TiledPropertiesHandler::findPropertyByName(
    const String& name
  ) const
  {
    if (!m_properties)
      return nullptr;

    SizeT propertyCount = m_properties->getPropertyCount();
    for (SizeT i = 0; i < propertyCount; ++i)
    {
      tmr::Property* property = m_properties->getPropertyAt(i);
      if (property && name == property->getName())
        return property;
    }

    return nullptr;
  }
}