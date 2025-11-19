#include "rkILevelScene.h"

namespace rk
{
  ILevelScene::ILevelScene(const String& key, ServiceLocator& serviceLocator)
    : IScene(key, serviceLocator),
    m_pathfinderManager()
  {
  }
  
  ILevelScene::~ILevelScene()
  {
  }

  void ILevelScene::onLoad()
  {
    // TODO
  }

  void ILevelScene::onUnload()
  {
    m_pathfinderManager.clear();
  }
}