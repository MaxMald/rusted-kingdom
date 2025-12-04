#pragma once

#include "rkIScene.h"
#include "rkPathfinderManager.h"

namespace tmr
{
  class TiledMap;
}

namespace rk
{
  class ViewsManager;

  class ILevelScene : public IScene
  {
  public:
    ILevelScene();
    virtual ~ILevelScene();

  protected:
    PathfinderManager m_pathfinderManager;
    SceneGraph m_uiSceneGraph;

    virtual void init(ServiceLocator& serviceLocator) override;
    virtual void onLoad() override;
    virtual void onUnload() override;
    virtual void preUpdate(float deltaTime) override;
    virtual void postUpdate(float deltaTime) override;
    virtual void postDraw(RenderTarget& window, RenderStates states) const override;

    void prepareMinimap(const tmr::TiledMap* tiledMap);
    void createBoxSelector();

  private:
    SharedPtr<ViewsManager> m_viewsManager;

    void createView();
    void updateUi(float deltaTime);
    void drawUi(RenderTarget& window, RenderStates renderStates) const;
  };
}