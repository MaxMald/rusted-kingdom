#pragma once

#include "rkARuntimeDevToolView.h"

namespace rk
{
  class Faction;
  class FactionManager;
  class ArmyManager;
  class Army;

  class ArmyManagerRuntimeDevToolView : public ARuntimeDevToolView
  {
  public:
    ArmyManagerRuntimeDevToolView(
      SharedPtr<ArmyManager> armyManager,
      SharedPtr<FactionManager> factionManager
    );
    virtual ~ArmyManagerRuntimeDevToolView();

  protected:
    void onUpdate(sf::RenderWindow&, const sf::Time&) override;
    void onDraw(sf::RenderWindow&) override;

  private:
    SharedPtr<ArmyManager> m_armyManager;
    SharedPtr<FactionManager> m_factionManager;

    void drawArmyElement(const Army& army);
    const String& getArmyFactionName(const Army& army);
  };
}