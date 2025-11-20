#pragma once

#include <SFML/Graphics/RenderStates.hpp>

#include "rkIService.h"

namespace sf
{
  class RenderTarget;
}

using sf::RenderTarget;
using sf::RenderStates;

namespace rk
{
  class IScene;

  class ScenesManager : public IService
  {
  public:
    ScenesManager();
    virtual ~ScenesManager();

    void registerScene(const String& key, SharedPtr<IScene> scene);
    void setNextScene(const String& key);

  protected:
    virtual void init(ServiceLocator& serviceLocator) override;
    virtual void destroy() override;

  private:
    void update(float deltaTime);
    void draw(RenderTarget& window, RenderStates states) const;
    void initScenes(ServiceLocator&);

    UnorderedMap<String, SharedPtr<IScene>> m_scenes;
    SharedPtr<IScene> m_activeScene;
    SharedPtr<IScene> m_nextScene;

    friend class Application;
  };
}