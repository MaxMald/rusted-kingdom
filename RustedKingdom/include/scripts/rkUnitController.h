#pragma once

#include "rkScriptComponent.h"
#include "rkUnitDescription.h"

namespace rk
{
  class Army;

  class UnitController : public ScriptComponent
  {
  public:
    UnitController(
      GameObject&,
      const UnitDescription&
    );
    virtual ~UnitController();

    SharedPtr<Army> getArmy();
    void setArmy(SharedPtr<Army> army);
    const UnitDescription& getUnitDescription() const;
    UInt16 getCurrentHealth() const;
    void addDamage(UInt16 damage);
    void addHealth(UInt16 health);

  protected:
    void onCreate() override;
    void onDelete() override;

  private:
    SharedPtr<Army> m_army;
    UnitDescription m_unitDescription;
    UInt16 m_currentHealth;
  };
}