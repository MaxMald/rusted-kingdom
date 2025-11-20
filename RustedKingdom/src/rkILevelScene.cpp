#include "rkILevelScene.h"

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
    // TODO
  }

  void ILevelScene::onUnload()
  {
    m_pathfinderManager.clear();
  }
}