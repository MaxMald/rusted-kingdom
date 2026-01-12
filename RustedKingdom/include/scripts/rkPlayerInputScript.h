#pragma once

#include "rkScriptComponent.h"
#include "rkIMouseInputManagerListener.h"

namespace rk
{
  class UnitsCommanderScript;
  class InputManager;

  class PlayerInputScript :
    public ScriptComponent,
    public IMouseInputManagerListener
  {
  public:
    PlayerInputScript(GameObject& gameObject);
    virtual ~PlayerInputScript();

  protected:
    virtual void onCreate() override;
    virtual void onDelete() override;
    virtual void onMouseButtonPressed(MouseButtonEvent&) override;
    virtual void onMouseButtonReleased(MouseButtonEvent&) override;

  private:
    UnitsCommanderScript* m_unitsCommanderScript;
    SharedPtr<InputManager> m_inputManager;
  };
}