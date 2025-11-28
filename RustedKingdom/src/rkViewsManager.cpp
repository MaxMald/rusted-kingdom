#include "rkViewsManager.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "rkWindowManager.h"
#include "rkServiceLocator.h"

namespace rk
{
  ViewsManager::ViewsManager() :
    m_renderWindow(nullptr),
    m_activeView(),
    m_views()
  {
  }

  ViewsManager::~ViewsManager()
  {
  }

  void ViewsManager::addView(const SharedPtr<ViewController>& view)
  {
    if (view != nullptr)
      m_views[view->getName()] = view;
  }

  void ViewsManager::removeView(const String& name)
  {
    if (m_activeView != nullptr)
    {
      if (m_activeView->getName() == name)
        m_activeView = nullptr;
    }

    if (hasView(name))
      m_views.erase(name);
  }

  void ViewsManager::setActiveView(const String& name)
  {
    if (!hasView(name))
    {
      throw RuntimeErrorException(
        "ViewsManager::setActiveView: View '" + name + "' not found."
      );
    }

    m_activeView = m_views.at(name);
    updateRenderWindowView();
  }

  SharedPtr<ViewController> ViewsManager::getActiveView()
  {
    return m_activeView;
  }

  SharedPtr<ViewController> ViewsManager::getView(const String& name)
  {
    if (m_views.find(name) != m_views.end())
      return m_views.at(name);

    throw RuntimeErrorException(
      "ViewsManager::getView: View '" + name + "' not found."
    );
  }

  bool ViewsManager::hasView(const String& name)
  {
    return m_views.find(name) != m_views.end();
  }

  const View& ViewsManager::getDefaultSfmlView() const
  {
    if (m_renderWindow == nullptr)
    {
      throw RuntimeErrorException(
        "ViewsManager::getDefaultSfmlView: RenderWindow is null."
      );
    }

    return m_renderWindow->getDefaultView();
  }

  void ViewsManager::updateRenderWindowView()
  {
    if (m_renderWindow == nullptr || m_activeView == nullptr)
      return;

    m_renderWindow->setView(m_activeView->getView());
  }

  void ViewsManager::init(ServiceLocator& serviceLocator)
  {
    SharedPtr<WindowManager> windowManager =
      serviceLocator.getService<WindowManager>();

    RenderWindow& renderWindow = windowManager->getRenderWindow();
    m_renderWindow = &renderWindow;
  }

  void ViewsManager::destroy()
  {
    m_renderWindow = nullptr;
  }
}