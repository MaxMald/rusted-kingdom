#include "scripts/rkViewControllerScript.h"

#include <SFML/Window/Keyboard.hpp>

#include "rkServiceLocator.h"
#include "rkViewsManager.h"
#include "rkViewComponent.h"
#include "rkGameObject.h"

namespace rk
{
  ViewControllerScript::ViewControllerScript(GameObject& gameObject) :
    ScriptComponent(gameObject, "view-controller"),
    m_viewComponent(nullptr)
  {
  }

  ViewControllerScript::~ViewControllerScript()
  {
  }

  void ViewControllerScript::onCreate()
  {
    m_viewComponent = m_gameObject->getComponent<ViewComponent>();
    
    SharedPtr<ViewsManager> viewsManager = ServiceLocator::Instance()
      .getService<ViewsManager>();
    viewsManager->setActiveView(m_viewComponent->getViewName());
  }

  void ViewControllerScript::onUpdate(float deltaTime)
  {
    sf::Vector2f moveOffset(0.f, 0.f);
    const float moveSpeed = 400.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
      moveOffset.y -= moveSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
      moveOffset.y += moveSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
      moveOffset.x -= moveSpeed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
      moveOffset.x += moveSpeed;

    if (moveOffset.length() > 0.f)
      moveOffset = moveOffset.normalized() * moveSpeed;

    m_viewComponent->move(moveOffset * deltaTime);
  }
}