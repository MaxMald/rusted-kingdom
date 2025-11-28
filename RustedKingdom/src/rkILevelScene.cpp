#include "rkILevelScene.h"

#include "rkServiceLocator.h"
#include "rkViewsManager.h"
#include "rkViewComponentFactory.h"
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

  void ILevelScene::onLoad()
  {
    createView();
  }

  void ILevelScene::onUnload()
  {
    m_pathfinderManager.clear();
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
}