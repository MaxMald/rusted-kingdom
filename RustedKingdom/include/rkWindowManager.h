#pragma once

#include "rkIService.h"

namespace sf
{
  class RenderWindow;
}

using sf::RenderWindow;

namespace rk
{
  class WindowManager : public IService 
  {
  public:
    WindowManager();
    ~WindowManager();

    RenderWindow& getRenderWindow();
    const RenderWindow& getRenderWindow() const;

  protected:
    virtual void init(ServiceLocator& serviceLocator) override;
    virtual void destroy() override;

  private:
    RenderWindow* m_renderWindow;

    void createWindow();

    friend class Application;
  };
}