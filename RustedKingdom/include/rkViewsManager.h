#pragma once

#include "rkPrerequisites.h"
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

namespace rk
{
  /**
   * @brief Manages the main world camera (SFML view).
   */
  class ViewsManager
  {
  public:

    /**
     * @brief Construct a new ViewsManager.
     *
     * Initializes the internal view using the provided world rectangle.
     *
     * @param worldRect Rectangle that defines the world extents (origin, size)
     * used to initialize the view. The referenced object must remain valid for
     * the lifetime of this ViewsManager.
     */
    ViewsManager(sf::FloatRect& worldRect);

    /**
     * @brief Destroy the ViewsManager.
     */
    ~ViewsManager();

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

  private:
    /// The SFML view representing the camera for the world.
    sf::View m_worldView;
  };
}