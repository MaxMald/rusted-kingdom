#pragma once

#include "rkScriptComponent.h"

namespace rk
{
  class UnitsSelectionController;

  class UnitsCommanderScript : public ScriptComponent
  {
  public:
    UnitsCommanderScript(GameObject& gameObject);
    virtual ~UnitsCommanderScript();

    void moveSelectedUnitsTo(const sf::Vector2f& position);

  protected:
    virtual void onCreate() override;

  private:
    UnitsSelectionController* m_unitsSelectionController;
  };
}