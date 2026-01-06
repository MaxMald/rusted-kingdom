#pragma once

#include "rkARuntimeDevToolView.h"

namespace rk
{
  class ScenesManager;
  class GameObject;

  class SceneGraphRuntimeDevToolView : public ARuntimeDevToolView
  {
  public:
    SceneGraphRuntimeDevToolView(SharedPtr<ScenesManager>);
    ~SceneGraphRuntimeDevToolView();

  protected:
    SharedPtr<ScenesManager> m_scenesManager;

    void onUpdate(sf::RenderWindow& window, const sf::Time& elapsed) override;
    void onDraw(sf::RenderWindow& window) override;

  private:
    void drawGameObjectTree(const GameObject& root);
    String getGameObjectName(const GameObject& gameObject);
  };
}