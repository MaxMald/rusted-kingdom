#include "rkInputManager.h"

#include "rkWindowManager.h"
#include "rkServiceLocator.h"

namespace rk
{
  InputManager::InputManager() :
    m_mouseInputManager()
  {
  }

  InputManager::~InputManager()
  {
  }

  MouseInputManager& InputManager::getMouseInputManager()
  {
    return m_mouseInputManager;
  }

  const MouseInputManager& InputManager::getMouseInputManager() const
  {
    return m_mouseInputManager;
  }

  void InputManager::update()
  {
    m_mouseInputManager.update();
  }

  void InputManager::init(ServiceLocator& serviceLocator)
  {
    SharedPtr<WindowManager> windowManager = serviceLocator
      .getService<WindowManager>();

    m_mouseInputManager.prepare(windowManager);
  }

  void InputManager::destroy()
  {
  }
}