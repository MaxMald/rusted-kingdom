#pragma once

#include "rkPrerequisites.h"

namespace tmr
{
  class Properties;
  class Property;
}

namespace rk
{
  class TiledPropertiesHandler
  {
  public:
    TiledPropertiesHandler();
    TiledPropertiesHandler(const tmr::Properties* properties);
    ~TiledPropertiesHandler();

    TiledPropertiesHandler(const TiledPropertiesHandler& other);
    TiledPropertiesHandler& operator=(const TiledPropertiesHandler& other);
    TiledPropertiesHandler(TiledPropertiesHandler&& other) noexcept;
    TiledPropertiesHandler& operator=(TiledPropertiesHandler&& other) noexcept;

    bool hasProperty(const String& name) const;
    bool tryGetBool(const String& name, bool& outValue) const;
    bool tryGetColor(const String& name, String& outValue) const;
    bool tryGetFile(const String& name, String& outValue) const;
    bool tryGetFloat(const String& name, float& outValue) const;
    bool tryGetInt(const String& name, Int32& outValue) const;
    bool tryGetObject(const String& name, Int32& outValue) const;
    bool tryGetString(const String& name, String& outValue) const;
    SizeT getSize() const;

  private:
    const tmr::Properties* m_properties;

    const tmr::Property* findPropertyByName(const String& name) const;
  };
}