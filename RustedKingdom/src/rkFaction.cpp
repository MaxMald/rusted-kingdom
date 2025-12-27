#include "rkFaction.h"

namespace rk
{
  Faction::Faction()
    : m_name("")
    , m_factionAssetsPath("")
    , m_type(factionType::Undefined)
  {
  }

  Faction::Faction(
    factionType::Type type,
    String name,
    Path factionAssetsPath
  )
    : m_name(std::move(name))
    , m_factionAssetsPath(factionAssetsPath)
    , m_type(type)
  {
  }

  Faction::Faction(const Faction& other)
    : m_name(other.m_name)
    , m_factionAssetsPath(other.m_factionAssetsPath)
    , m_type(other.m_type)
  {
  }

  Faction::Faction(Faction&& other) noexcept
    : m_name(std::move(other.m_name))
    , m_factionAssetsPath(std::move(other.m_factionAssetsPath))
    , m_type(other.m_type)
  {
  }

  Faction::~Faction() = default;

  Faction& Faction::operator=(const Faction& other)
  {
    if (this != &other)
    {
      m_name = other.m_name;
      m_factionAssetsPath = other.m_factionAssetsPath;
      m_type = other.m_type;
    }
    return *this;
  }

  Faction& Faction::operator=(Faction&& other) noexcept
  {
    if (this != &other)
    {
      m_name = std::move(other.m_name);
      m_factionAssetsPath = std::move(other.m_factionAssetsPath);
      m_type = other.m_type;
    }
    return *this;
  }

  const String& Faction::getName() const
  {
    return m_name;
  }

  const Path& Faction::getFactionAssetsPath() const
  {
    return m_factionAssetsPath;
  }

  factionType::Type Faction::getType() const
  {
    return m_type;
  }
}