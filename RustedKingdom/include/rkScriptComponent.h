#pragma once

#include "rkComponent.h"

namespace rk
{
  class ScriptComponent : public Component
  {
  public:
    ScriptComponent(GameObject& gameObject, const String& scriptName);
    virtual ~ScriptComponent();

    const String& getScriptName() const { return m_scriptName; }

  private:
    String m_scriptName;
  };
}