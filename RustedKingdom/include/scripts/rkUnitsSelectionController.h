#pragma once

#include "rkScriptComponent.h"
#include "scripts/rkIBoxSelectorScriptListener.h"

namespace rk
{
  class Army;

  class UnitsSelectionController :
    public ScriptComponent,
    public IBoxSelectorScriptListener
  {
  public:
    UnitsSelectionController(GameObject& gameObject);
    virtual ~UnitsSelectionController();

    virtual void onBoxSelectionStarted(
      const Vector2f& boxP1,
      const Vector2f& boxP2
    ) override;

    virtual void onBoxSelectionUpdated(
      const Vector2f& boxP1,
      const Vector2f& boxP2
    ) override;

    virtual void onBoxSelectionEnded(
      const Vector2f& boxP1,
      const Vector2f& boxP2
    ) override;

    void setArmy(SharedPtr<Army> army);
    const Vector<GameObject*>& getCurrentlySelectedUnits() const;

  protected:
    virtual void onCreate() override;

  private:
    SharedPtr<Army> m_army;
    Vector<GameObject*> m_currentlySelectedUnits;

    void registerEvents();
    void selectsUnitsOnArea(const Vector2f& boxP1, const Vector2f& boxP2);
  };
}