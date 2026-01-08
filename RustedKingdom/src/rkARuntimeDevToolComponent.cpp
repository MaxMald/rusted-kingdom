#include "rkARuntimeDevToolComponent.h"
#include "imgui.h"

namespace rk
{
  void ARuntimeDevToolComponent::update(
    sf::RenderWindow& window,
    const sf::Time& elapsed
  )
  {
    this->onUpdate(window, elapsed);
  }

  void ARuntimeDevToolComponent::draw(sf::RenderWindow& window)
  {
    if (ImGui::CollapsingHeader(m_componentName.c_str()))
      this->onDraw(window);
  }

  ARuntimeDevToolComponent::ARuntimeDevToolComponent(const String& name) :
    m_componentName(name)
  {
  }
}