#pragma once

#include "rkILevelScene.h"

namespace rk
{
  class AssetManager;
  class WindowManager;
  class PathfinderCollisionMaskUpdater;

  class MainScene : public ILevelScene
  {
  public:
    MainScene();
    virtual ~MainScene();

  protected:
    virtual void init(ServiceLocator&) override;
    virtual void onLoad() override;
    virtual void onUnload() override;

  private:
    SharedPtr<AssetManager> m_assetManager;
    SharedPtr<WindowManager> m_windowManager;
    UniquePtr<PathfinderCollisionMaskUpdater> m_pathfinderCollisionMaskUpdater;

    void loadAssets();
    void createArmies();
    void createScene();
    void createPathfinders();
  };
}