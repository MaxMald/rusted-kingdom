#pragma once

#include "rkScriptComponent.h"

namespace rk
{
  class Army;

  class UnitController : public ScriptComponent
  {
  public:
    UnitController(GameObject&, const String& armyName);
    virtual ~UnitController();

    SharedPtr<Army> getArmy();
    void setArmy(SharedPtr<Army> army);

  protected:
    void onCreate() override;
    void onDelete() override;

  private:
    SharedPtr<Army> m_army;
  };
}