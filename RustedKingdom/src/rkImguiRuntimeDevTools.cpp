#include "rkImguiRuntimeDevTools.h"

#include "imgui.h"
#include "imgui-SFML.h"

namespace rk
{
  void ImguiRuntimeDevTools::prepare(
    sf::RenderWindow& window,
    ServiceLocator&
  )
  {
    if (!ImGui::SFML::Init(window))
      throw RuntimeErrorException("Failed to initialize ImGui-SFML");
  }

  void ImguiRuntimeDevTools::processEvent(
    const sf::Window& window,
    const sf::Event& event
  )
  {
    ImGui::SFML::ProcessEvent(window, event);
  }

  void ImguiRuntimeDevTools::update(
    sf::RenderWindow& window,
    const sf::Time& elapsed
  )
  {
    ImGui::SFML::Update(window, elapsed);

    ImGui::ShowDemoWindow();
  }

  void ImguiRuntimeDevTools::draw(sf::RenderWindow& window)
  {
    ImGui::SFML::Render(window);
  }

  void ImguiRuntimeDevTools::destroy()
  {
  }
}