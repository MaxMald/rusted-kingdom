#pragma once

#include <SFML/Graphics/Rect.hpp>

#include "rkPrerequisites.h"

using sf::FloatRect;

namespace rk
{
  class GameObject;

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

    FloatRect calculateBounds(const GameObject& gameObject);
  }
}