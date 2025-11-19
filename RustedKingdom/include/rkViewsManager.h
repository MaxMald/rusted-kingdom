#pragma once

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include "rkIService.h"

namespace sf
{
  class RenderWindow;
}

using sf::RenderWindow;

namespace rk
{
  /**
   * @brief Manages the main world camera (SFML view).
   */
  class ViewsManager : public IService
  {
  public:

    /**
     * @brief Construct a new ViewsManager.
     */
    ViewsManager();

    /**
     * @brief Destroy the ViewsManager.
     */
    virtual ~ViewsManager();

    /**
     * @brief Get a const reference to the current world view.
     *
     * @return const sf::View& Current world view (const).
     */
    const sf::View& getWorldView() const;

    /**
     * @brief Move the world view by the specified offset.
     *
     * @param offset Offset vector to move the view by (in world coordinates).
     */
    void moveWorldView(const sf::Vector2f& offset);

    /**
     * @brief Per-frame update step for the view.
     *
     * @param deltaTime Elapsed time since last frame, in seconds.
     */
    void update(const float& deltaTime);

  protected:

    virtual void init(ServiceLocator& serviceLocator) override;
    virtual void destroy() override;

  private:
    sf::View m_worldView;
    RenderWindow* m_renderWindow;

    void updateRenderWindowView();
  };
}