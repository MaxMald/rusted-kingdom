#pragma once

#include <SFML/System/Vector2.hpp>

#include "rkScriptComponent.h"
#include "rkUnitDescription.h"

using sf::Vector2f;

namespace rk
{
  class Army;
  class PathfinderComponent;
  class AgentPathMovement;

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

    void goTo(const Vector2f& position);

    void addDamage(UInt16 damage);
    void addHealth(UInt16 health);

  protected:
    void onCreate() override;
    void onDelete() override;

  private:
    SharedPtr<Army> m_army;
    PathfinderComponent* m_pathfinderComponent;
    AgentPathMovement* m_agentPathMovement;
    UnitDescription m_unitDescription;
    UInt16 m_currentHealth;
  };
}