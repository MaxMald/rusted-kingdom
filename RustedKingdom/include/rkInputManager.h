#pragma once

#include "rkIService.h"
#include "rkMouseInputManager.h"

namespace rk
{
  class InputManager : public IService
  {
  public:
    InputManager();
    virtual ~InputManager();

    MouseInputManager& getMouseInputManager();
    const MouseInputManager& getMouseInputManager() const;

    void update();

  protected:
    virtual void init(ServiceLocator& serviceLocator) override;
    virtual void destroy() override;

  private:
    MouseInputManager m_mouseInputManager;
  };
}