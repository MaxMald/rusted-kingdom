#pragma once

#include "TMR/tmrPrerequisites.h"
#include "TMR/tmrOrientation.h"
#include "TMR/tmrRenderOrder.h"
#include "TMR/tmrNonCopyable.h"

namespace tmr
{
  class TileMapLayer;
  class ObjectGroup;
  class TileSet;

  /**
   * @class TiledMap
   * @brief Represents a Tiled map and its properties.
   */
  class TMR_API TiledMap : public NonCopyable
  {
  public:
    TiledMap(
      bool infinite,
      int32_t height,
      int32_t width,
      int32_t nextLayerId,
      int32_t nextObjectId,
      int32_t tileHeight,
      int32_t tileWidth,
      orientation::Type orientation,
      renderOrder::Type renderOrder,
      const char* tiledVersion,
      const char* type,
      const char* version,
      TileMapLayer** layers,
      const size_t& layersCount,
      ObjectGroup** objectGroups,
      const size_t& objectGroupsCount,
      TileSet** tileSets,
      const size_t& tileSetsCount
    );
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

    /**
     * @brief Gets the number of layers in the map.
     * @return The number of layers.
     */
    const std::size_t& getLayersCount() const { return m_layersCount; }

    /**
     * @brief Gets the map layer at the specified index.
     * 
     * @param index Index of the layer to retrieve.
     * @return Pointer to the TileMapLayer at the specified index.
     */
    const TileMapLayer* getLayerAt(const std::size_t& index) const;

    /**
     * @brief Gets the number of object groups in the map.
     * 
     * @return The number of object groups.
     */
    const std::size_t& getObjectGroupsCount() const { return m_objectGroupsCount; }

    /**
     * @brief Gets the object group at the specified index.
     * 
     * @param index Index of the object group to retrieve.
     * @return Pointer to the ObjectGroup at the specified index.
     */
    const ObjectGroup* getObjectGroupAt(const std::size_t& index) const;

    /**
     * @brief Gets the number of tile sets in the map.
     * @return The number of tile sets.
     */
    const std::size_t& getTileSetsCount() const { return m_tileSetsCount; }

    /**
     * @brief Gets the tile set at the specified index.
     * 
     * @param index Index of the tile set to retrieve.
     * @return Pointer to the TileSet at the specified index.
     */
    const TileSet* getTileSetAt(const std::size_t& index) const;

    /**
     * @brief Gets the tile set at the specified index (non-const version).
     * 
     * @param index Index of the tile set to retrieve.
     * @return Pointer to the TileSet at the specified index.
     */
    TileSet* getTileSetAt(const std::size_t& index);

    /**
     * @brief Replaces the tile set at the specified index with a new tile set.
     * 
     * @param index Index of the tile set to replace.
     * @param tileSet Pointer to the new TileSet to set.
     */
    void replaceTileSetAt(const size_t& index, TileSet* tileSet);

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
    TileMapLayer** m_layers;
    std::size_t m_layersCount;
    ObjectGroup** m_objectGroups;
    std::size_t m_objectGroupsCount;
    TileSet** m_tileSets;
    std::size_t m_tileSetsCount;
  };
}