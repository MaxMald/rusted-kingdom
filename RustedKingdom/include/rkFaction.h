#pragma once

#include "rkPrerequisites.h"
#include "rkFactionType.h"

namespace rk
{
  class Faction
  {
  public:
    Faction();
    Faction(factionType::Type type, String name, Path factionAssetsPath);
    Faction(const Faction& other);
    Faction(Faction&& other) noexcept;
    ~Faction();

    Faction& operator=(const Faction& other);
    Faction& operator=(Faction&& other) noexcept;

    const String& getName() const;
    const Path& getFactionAssetsPath() const;
    factionType::Type getType() const;

  private:
    String m_name;
    Path m_factionAssetsPath;
    factionType::Type m_type;
  };
}