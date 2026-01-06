#pragma once

#include "rkARuntimeDevToolView.h"

namespace rk
{
  class FactionManager;
  class Faction;

  class FactionManagerRuntimeDevToolView : public ARuntimeDevToolView
  {
  public:
    FactionManagerRuntimeDevToolView(SharedPtr<FactionManager> factionManager);
    virtual ~FactionManagerRuntimeDevToolView();

  protected:
    void onUpdate(sf::RenderWindow& window, const sf::Time& elapsed) override;
    void onDraw(sf::RenderWindow& window) override;

  private:
    SharedPtr<FactionManager> m_factionManager;

    void drawFactionElement(const Faction& faction);
  };
}