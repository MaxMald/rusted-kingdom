#pragma once

#include <SFML/Graphics/Rect.hpp>

#include "rkPrerequisites.h"

using sf::FloatRect;

namespace rk
{
  class GameObject;

  /**
   * @namespace rk::gameObjectUtilities
   * @brief Utility functions for manipulating and querying GameObject properties.
   */
  namespace gameObjectUtilities
  {
    /**
     * @brief Sets the origin of a GameObject's sprite based on normalized
     * coordinates.
     *
     * This function retrieves the SpriteComponent from the specified GameObject.
     * If the component exists, it calculates the origin using the sprite's
     * texture rectangle size, otherwise it does nothing.
     *
     * @param gameObject Reference to the GameObject whose sprite origin will be
     * set.
     * @param x Normalized horizontal origin (0.0 = left, 1.0 = right).
     * @param y Normalized vertical origin (0.0 = top, 1.0 = bottom).
     */
    void setSpriteOrigin(GameObject& gameObject, float x, float y);

    /**
     * @brief Calculates the aggregate local bounds of the specified GameObject
     * and all its children.
     *
     * This function returns the bounding rectangle that encompasses the
     * GameObject's sprite and the sprites of all its children, in local
     * coordinates. If the GameObject and its children do not have
     * SpriteComponents, the returned rectangle will be empty.
     *
     * @param gameObject Reference to the GameObject whose aggregate bounds will
     * be calculated.
     * @return FloatRect representing the aggregate local bounds of the
     * GameObject and its children.
     */
    FloatRect calculateAggregateBounds(const GameObject& gameObject);

    /**
     * @brief Gets the global bounds of the specified GameObject's sprite.
     *
     * This function returns the bounding rectangle of the GameObject's sprite in
     * global coordinates. If the GameObject does not have a SpriteComponent, the
     * returned rectangle will be empty.
     *
     * @param gameObject Reference to the GameObject whose global sprite bounds
     * will be retrieved.
     * @return FloatRect representing the global bounds of the sprite.
     */
    FloatRect getGameObjectSpriteGlobalBounds(const GameObject& gameObject);
  }
}