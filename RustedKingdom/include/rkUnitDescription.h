#pragma once

#include "rkPrerequisites.h"

namespace rk
{
  class UnitDescription
  {
  public:
    UnitDescription();
    UnitDescription(const UnitDescription& other);
    UnitDescription(UnitDescription&& other) noexcept;
    ~UnitDescription();

    UnitDescription& operator=(const UnitDescription& other);
    UnitDescription& operator=(UnitDescription&& other) noexcept;

    const String& getName() const;
    void setName(const String& name);
    const String& getDisplayName() const;
    void setDisplayName(const String& displayName);
    float getVelocity() const;
    void setVelocity(float velocity);
    UInt16 getHealth() const;
    void setHealth(UInt16 health);
    UInt16 getArmor() const;
    void setArmor(UInt16 armor);

  private:
    String m_name;
    String m_displayName;
    float m_velocity;
    UInt16 m_health;
    UInt16 m_armor;
  };
}
