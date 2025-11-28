#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include "rkIService.h"
#include "rkViewController.h"

namespace sf
{
  class RenderWindow;
}

using sf::RenderWindow;
using sf::View;

namespace rk
{
  /**
   * @brief Manages the main world camera (SFML view).
   */
  class ViewsManager : public IService
  {
  public:
    ViewsManager();
    virtual ~ViewsManager();

    void addView(const SharedPtr<ViewController>& view);
    void removeView(const String& name);
    void setActiveView(const String& name);
    SharedPtr<ViewController> getActiveView();
    SharedPtr<ViewController> getView(const String& name);
    bool hasView(const String& name);
    const View& getDefaultSfmlView() const;
    void updateRenderWindowView();

  protected:
    virtual void init(ServiceLocator& serviceLocator) override;
    virtual void destroy() override;

  private:
    RenderWindow* m_renderWindow;
    UnorderedMap<String, SharedPtr<ViewController>> m_views;
    SharedPtr<ViewController> m_activeView;
  };
}