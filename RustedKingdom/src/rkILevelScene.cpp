#include "rkILevelScene.h"

#include "rkServiceLocator.h"
#include "rkViewsManager.h"
#include "rkViewComponentFactory.h"
#include "rkViewController.h"
#include "scripts/rkViewControllerScript.h"

namespace rk
{
  ILevelScene::ILevelScene()
    : IScene(),
    m_pathfinderManager()
  {
  }
  
  ILevelScene::~ILevelScene()
  {
  }

  void ILevelScene::init(ServiceLocator& serviceLocator)
  {
    m_viewsManager = serviceLocator.getService<ViewsManager>();
  }

  void ILevelScene::onLoad()
  {
    createView();
  }

  void ILevelScene::onUnload()
  {
    m_pathfinderManager.clear();
    m_uiSceneGraph.destroy();
  }

  void ILevelScene::preUpdate(float)
  {
    // Implement in derived classes if needed
  }

  void ILevelScene::postUpdate(float deltaTime)
  {
    updateUi(deltaTime);
  }

  void ILevelScene::postDraw(
    RenderTarget& window,
    RenderStates states
  ) const
  {
    drawUi(window, states);
  }

  void ILevelScene::createView()
  {
    ViewComponentFactory viewComponentFactory(
      ServiceLocator::Instance().getService<ViewsManager>()
    );

    UniquePtr<GameObject> viewGameObject = MakeUnique<GameObject>("main-view");

    UniquePtr<ViewComponent> viewComponent = viewComponentFactory.create(
      *viewGameObject,
      "main-view"
    );
    viewGameObject->addComponent(std::move(viewComponent));
    viewGameObject->addComponent(MakeUnique<ViewControllerScript>(*viewGameObject));

    m_sceneGraph.registerGameObject(std::move(viewGameObject));
  }

  void ILevelScene::updateUi(float deltaTime)
  {
    m_uiSceneGraph.update(deltaTime);
  }

  void ILevelScene::drawUi(RenderTarget& window, RenderStates states) const
  {
    View defaultView = m_viewsManager->getDefaultSfmlView();
    window.setView(defaultView);

    m_uiSceneGraph.draw(window, states);

    m_viewsManager->updateRenderWindowView();
  }
}