#include "rkScriptComponent.h"

namespace rk
{
  ScriptComponent::ScriptComponent(GameObject& gameObject, const String& scriptName)
    : Component(gameObject, componentType::Script),
    m_scriptName(scriptName)
  {
  }

  ScriptComponent::~ScriptComponent()
  {
  }
} // namespace rk