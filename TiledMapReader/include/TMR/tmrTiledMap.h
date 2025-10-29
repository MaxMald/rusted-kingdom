#pragma once

#include "TMR/tmrPrerequisites.h"
#include "TMR/tmrOrientation.h"
#include "TMR/tmrRenderOrder.h"

namespace tmr
{
  /**
   * @class TiledMap
   * @brief Represents a Tiled map and its properties.
   */
  class TMR_API TiledMap
  {
  public:
    /**
      * @brief Constructs a TiledMap object with initialization.
      * 
      * @param infinite True if the map is infinite.
      * @param height Height of the map in tiles.
      * @param width Width of the map in tiles.
      * @param nextLayerId Next available layer ID.
      * @param nextObjectId Next available object ID.
      * @param tileHeight Height of a tile in pixels.
      * @param tileWidth Width of a tile in pixels.
      * @param orientation Orientation of the map.
      * @param renderOrder Render order of the map.
      * @param tiledVersion Tiled version string.
      * @param type Type string of the map.
      * @param version Version string of the map.
      */
    TiledMap(
      bool infinite,
      std::int32_t height,
      std::int32_t width,
      std::int32_t nextLayerId,
      std::int32_t nextObjectId,
      std::int32_t tileHeight,
      std::int32_t tileWidth,
      orientation::Type orientation,
      renderOrder::Type renderOrder,
      const char* tiledVersion,
      const char* type,
      const char* version
    );

    /**
     * @brief Destroys the TiledMap object.
     */
    ~TiledMap();

    /**
     * @brief Checks if the map is infinite.
     * 
     * @return True if the map is infinite, false otherwise.
     */
    bool isInfinite() const { return m_infinite; }

    /**
     * @brief Gets the height of the map in tiles.
     * 
     * @return The map height.
     */
    std::int32_t getHeight() const { return m_height; }

    /**
     * @brief Gets the width of the map in tiles.
     * 
     * @return The map width.
     */
    std::int32_t getWidth() const { return m_width; }

    /**
     * @brief Gets the next available layer ID.
     * 
     * @return The next layer ID.
     */
    std::int32_t getNextLayerId() const { return m_nextLayerId; }

    /**
     * @brief Gets the next available object ID.
     * 
     * @return The next object ID.
     */
    std::int32_t getNextObjectId() const { return m_nextObjectId; }

    /**
     * @brief Gets the height of a tile in pixels.
     * 
     * @return The tile height.
     */
    std::int32_t getTileHeight() const { return m_tileHeight; }

    /**
     * @brief Gets the width of a tile in pixels.
     * 
     * @return The tile width.
     */
    std::int32_t getTileWidth() const { return m_tileWidth; }

    /**
     * @brief Gets the orientation of the map.
     * 
     * @return The map orientation.
     */
    orientation::Type getOrientation() const { return m_orientation; }

    /**
     * @brief Gets the render order of the map.
     * 
     * @return The map render order.
     */
    renderOrder::Type getRenderOrder() const { return m_renderOrder; }

    /**
     * @brief Gets the Tiled version string.
     * 
     * @return The Tiled version.
     */
    const char* getTiledVersion() const { return m_tiledVersion; }

    /**
     * @brief Gets the type string of the map.
     * 
     * @return The map type.
     */
    const char* getType() const { return m_type; }

    /**
     * @brief Gets the version string of the map.
     * 
     * @return The map version.
     */
    const char* getVersion() const { return m_version; }

  private:
    bool m_infinite;
    std::int32_t m_height;
    std::int32_t m_width;
    std::int32_t m_nextLayerId;
    std::int32_t m_nextObjectId;
    std::int32_t m_tileHeight;
    std::int32_t m_tileWidth;
    orientation::Type m_orientation;
    renderOrder::Type m_renderOrder;
    char* m_tiledVersion;
    char* m_type;
    char* m_version;
  };
}