#include "rkUnitDescription.h"

namespace rk
{
  UnitDescription::UnitDescription()
    : m_name("")
    , m_displayName("")
    , m_velocity(0.0f)
    , m_health(0)
    , m_armor(0)
  {
  }

  UnitDescription::UnitDescription(const UnitDescription& other)
    : m_name(other.m_name)
    , m_displayName(other.m_displayName)
    , m_velocity(other.m_velocity)
    , m_health(other.m_health)
    , m_armor(other.m_armor)
  {
  }

  UnitDescription::UnitDescription(UnitDescription&& other) noexcept
    : m_name(std::move(other.m_name))
    , m_displayName(std::move(other.m_displayName))
    , m_velocity(other.m_velocity)
    , m_health(other.m_health)
    , m_armor(other.m_armor)
  {
  }

  UnitDescription::~UnitDescription()
  {
  }

  UnitDescription& UnitDescription::operator=(const UnitDescription& other)
  {
    if (this != &other) {
      m_name = other.m_name;
      m_displayName = other.m_displayName;
      m_velocity = other.m_velocity;
      m_health = other.m_health;
      m_armor = other.m_armor;
    }
    return *this;
  }

  UnitDescription& UnitDescription::operator=(UnitDescription&& other) noexcept
  {
    if (this != &other) {
      m_name = std::move(other.m_name);
      m_displayName = std::move(other.m_displayName);
      m_velocity = other.m_velocity;
      m_health = other.m_health;
      m_armor = other.m_armor;
    }
    return *this;
  }

  const String& UnitDescription::getName() const
  {
    return m_name;
  }

  void UnitDescription::setName(const String& name)
  {
    m_name = name;
  }

  const String& UnitDescription::getDisplayName() const
  {
    return m_displayName;
  }

  void UnitDescription::setDisplayName(const String& displayName)
  {
    m_displayName = displayName;
  }

  float UnitDescription::getVelocity() const
  {
    return m_velocity;
  }

  void UnitDescription::setVelocity(float velocity)
  {
    m_velocity = velocity;
  }

  UInt16 UnitDescription::getHealth() const
  {
    return m_health;
  }

  void UnitDescription::setHealth(UInt16 health)
  {
    m_health = health;
  }

  UInt16 UnitDescription::getArmor() const
  {
    return m_armor;
  }

  void UnitDescription::setArmor(UInt16 armor)
  {
    m_armor = armor;
  }
}