#pragma once

#include "rkARuntimeDevToolView.h"
#include "rkGameObjectRuntimeDevToolView.h"

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
    GameObjectRuntimeDevToolView m_gameObjectView;
    GameObject* m_selectedGameObject;

    void onUpdate(sf::RenderWindow& window, const sf::Time& elapsed) override;
    void onDraw(sf::RenderWindow& window) override;

  private:
    void drawGameObjectTree(GameObject& root);
    String getGameObjectName(const GameObject& gameObject);
  };
}