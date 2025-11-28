#pragma once

#include "rkScriptComponent.h"

namespace rk
{
  class ViewComponent;

  class ViewControllerScript : public ScriptComponent
  {
  public:
    ViewControllerScript(GameObject& gameObject);
    virtual ~ViewControllerScript();

  protected:
    virtual void onCreate() override;
    virtual void onUpdate(float deltaTime) override;

  protected:
    ViewComponent* m_viewComponent;
  };
}