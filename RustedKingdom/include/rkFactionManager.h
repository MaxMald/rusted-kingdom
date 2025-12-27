#pragma once

#include "rkPrerequisites.h"
#include "rkIService.h"
#include "rkFaction.h"

namespace rk
{
  class FactionManager : public IService
  {
  public:
    void addFaction(const Faction& faction);
    const Faction& getFaction(factionType::Type type) const;

  protected:
    void init(ServiceLocator& serviceLocator) override;
    void destroy() override;

  private:
    UnorderedMap<factionType::Type, Faction> m_factions;
  };
}