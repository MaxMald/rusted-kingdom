#include "rkFactionManager.h"

namespace rk
{
  void FactionManager::addFaction(const Faction& faction)
  {
    m_factions[faction.getType()] = faction;
  }

  const Faction& FactionManager::getFaction(factionType::Type type) const
  {
    auto it = m_factions.find(type);
    if (it != m_factions.end())
    {
      return it->second;
    }

    throw RuntimeErrorException("Faction not found");
  }

  void FactionManager::init(ServiceLocator&)
  {
    addFaction(
      Faction(
        factionType::Corps,
        "La Corporación",
        "assets/factions/corps/"
      )
    );

    addFaction(
      Faction(
        factionType::Bios,
        "Los Biosintéticos",
        "assets/factions/bios/"
      )
    );
  }

  void FactionManager::destroy()
  {
    m_factions.clear();
  }
}