#pragma once

#include "TMR/tmrPrerequisites.h"
#include "TMR/tmrMapLayerType.h"

namespace tmr
{
  /**
   * @class TiledMapLayer
   * @brief Represents a layer in a Tiled map, such as a tile layer or object group.
   */
  class TMR_API MapLayer
  {
  public:
    /**
     * @brief Constructs a TiledMapLayer with the specified properties.
     *
     * @param type The type of the layer (e.g., TileLayer, ObjectGroup).
     * @param id The unique identifier for the layer.
     * @param x The x-coordinate of the layer.
     * @param y The y-coordinate of the layer.
     * @param visible Whether the layer is visible.
     * @param opacity The opacity of the layer (0.0f to 1.0f).
     * @param name The name of the layer.
     */
    MapLayer(
      const mapLayerType::Type& type,
      const std::int32_t& id,
      const std::int32_t& x,
      const std::int32_t& y,
      const bool& visible,
      const float& opacity,
      const char* name
    );

    /**
     * @brief Virtual destructor for safe polymorphic use.
     */
    virtual ~MapLayer();

    /**
     * @brief Gets the type of the layer.
     * @return The layer type.
     */
    const mapLayerType::Type& getType() const { return m_type; }

    /**
     * @brief Gets the unique identifier of the layer.
     * @return The layer ID.
     */
    const std::int32_t& getId() const { return m_id; }

    /**
     * @brief Gets the x-coordinate of the layer.
     * @return The x position.
     */
    const std::int32_t& getX() const { return m_x; }

    /**
     * @brief Gets the y-coordinate of the layer.
     * @return The y position.
     */
    const std::int32_t& getY() const { return m_y; }

    /**
     * @brief Checks if the layer is visible.
     * @return True if visible, false otherwise.
     */
    const bool& isVisible() const { return m_visible; }

    /**
     * @brief Gets the opacity of the layer.
     * @return The opacity value (0.0f to 1.0f).
     */
    const float& getOpacity() const { return m_opacity; }

    /**
     * @brief Gets the name of the layer.
     * @return The layer name as a C-style string.
     */
    const char* getName() const { return m_name; }

  protected:
    mapLayerType::Type m_type;      ///< The type of the layer.
    std::int32_t m_id;              ///< The unique identifier for the layer.
    std::int32_t m_x;               ///< The x-coordinate of the layer.
    std::int32_t m_y;               ///< The y-coordinate of the layer.
    bool m_visible;                 ///< Whether the layer is visible.
    float m_opacity;                ///< The opacity of the layer.
    char* m_name;                   ///< The name of the layer.
  };
}