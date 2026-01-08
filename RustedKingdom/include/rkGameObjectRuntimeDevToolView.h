#pragma once

#include "rkARuntimeDevToolView.h"

namespace rk
{
  class GameObject;

  class GameObjectRuntimeDevToolView : public ARuntimeDevToolView
  {
  public:
    GameObjectRuntimeDevToolView();
    virtual ~GameObjectRuntimeDevToolView();

    void setActiveGameObject(GameObject* gameObject);

  protected:
    virtual void onUpdate(sf::RenderWindow& window, const sf::Time& elapsed) override;
    virtual void onDraw(sf::RenderWindow& window) override;

  private:
    GameObject* m_activeGameObject;

    void drawBaseInformation();
  };
}