#include "rkImguiRuntimeDevTools.h"

#include "imgui.h"
#include "imgui-SFML.h"
#include "rkSceneGraphRuntimeDevToolView.h"
#include "rkAssetManagerRuntimeDevToolView.h"
#include "rkScenesManager.h"
#include "rkAssetManager.h"

namespace rk
{
  void ImguiRuntimeDevTools::prepare(
    sf::RenderWindow& window,
    ServiceLocator& serviceLocator
  )
  {
    if (!ImGui::SFML::Init(window))
      throw RuntimeErrorException("Failed to initialize ImGui-SFML");

    m_views.push_back(
      MakeShared<SceneGraphRuntimeDevToolView>(
        serviceLocator.getService<ScenesManager>()
      )
    );

    m_views.push_back(
      MakeShared<AssetManagerRuntimeDevToolView>(
        serviceLocator.getService<AssetManager>()
      )
    );
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

    SizeT numViews = m_views.size();
    for (SizeT i = 0; i < numViews; ++i)
      m_views[i]->update(window, elapsed);

    //ImGui::ShowDemoWindow();
  }

  void ImguiRuntimeDevTools::draw(sf::RenderWindow& window)
  {
    ImGui::Begin("Runtime Development Tools", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::Text("Toggle Views:");
    for (SizeT i = 0; i < m_views.size(); ++i) 
    {
      auto& view = m_views[i];
      ImGui::Checkbox(view->getName().c_str(), &view->isOpen);
    }

    ImGui::End();

    SizeT numViews = m_views.size();
    for (SizeT i = 0; i < numViews; ++i)
      m_views[i]->draw(window);

    ImGui::SFML::Render(window);
  }

  void ImguiRuntimeDevTools::destroy()
  {
  }
}