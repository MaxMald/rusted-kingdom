#pragma once

#include "rkPrerequisites.h"
#include "rkIService.h"
#include "rkFactionType.h"
#include "rkArmyControlType.h"

namespace rk
{
  class Army;

  class ArmyManager : public IService
  {
  public:
    SharedPtr<Army> getArmy(UInt32 armyId);
    SharedPtr<Army> getArmy(const String& name);
    void setArmiesAsAllies(UInt32 armyIdA, UInt32 armyIdB);
    void setArmiesAsHostiles(UInt32 armyIdA, UInt32 armyIdB);
    const UnorderedMap<UInt32, SharedPtr<Army>>& getAllArmies() const;

    SharedPtr<Army> createArmy(
      const String& name,
      factionType::Type factionType,
      armyControlType::Type controlType
    );
    void clear();

  protected:
    void init(ServiceLocator& serviceLocator) override;
    void destroy() override;

  private:
    UnorderedMap<UInt32, SharedPtr<Army>> m_armies;
  };
}