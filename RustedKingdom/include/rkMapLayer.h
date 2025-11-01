#pragma once

#include "rkPrerequisites.h"
#include <TMR/tmrMapLayer.h>
#include <SFML/System/Vector2.hpp>

namespace rk
{
  /**
   * @brief Thin wrapper around a Tiled map layer.
   */
  class MapLayer
  {
  public:

    /**
     * @brief Constructs a MapLayer wrapping the given Tiled map layer.
     *
     * @param tmrMapLayer Pointer to the Tiled map layer to wrap. Ownership
     * is NOT transferred.
     */
    MapLayer(tmr::MapLayer* tmrMapLayer);
    virtual ~MapLayer();

    /**
     * @brief Get the Tiled layer type.
     *
     * @return const reference to the underlying Type value.
     */
    const tmr::mapLayerType::Type& getType() const {
      return m_tmrMapLayer->getType();
    }

    /**
     * @brief Get the Tiled layer identifier.
     *
     * @return const reference to the underlying Id value.
     */
    const Int32& getId() const { return m_tmrMapLayer->getId(); }

    /**
     * @brief Get the Tiled layer name.
     *
     * @return const reference to the underlying name value.
     */
    const String& getName() const { return m_name; }

    /**
     * @brief Get the Tiled layer position.
     *
     * @return const reference to the underlying position value.
     */
    const sf::Vector2i& getPosition() const { return m_position; }

    /**
     * @brief Check if the Tiled layer is visible.
     *
     * @return const reference to the underlying visibility value.
     */
    const bool& isVisible() const { return m_tmrMapLayer->isVisible(); }

  protected:
    String m_name;
    sf::Vector2i m_position;
    tmr::MapLayer* m_tmrMapLayer;
  };
}