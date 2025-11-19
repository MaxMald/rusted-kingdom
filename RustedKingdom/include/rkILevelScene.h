#pragma once

#include "rkIScene.h"
#include "rkPathfinderManager.h"

namespace rk
{
  class ILevelScene : public IScene
  {
  public:
    ILevelScene(const String& key, ServiceLocator&);
    virtual ~ILevelScene();

  protected:
    PathfinderManager m_pathfinderManager;

    virtual void onLoad() override;
    virtual void onUnload() override;
  };
}