#include "TMR/tmrTiledMap.h"

#include <cstring>
#include <stdexcept>

#include "TMR/tmrMapLayer.h"
#include "TMR/tmrTileSet.h"

namespace tmr
{
  TiledMap::TiledMap(
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
    const char* version,
    MapLayer** layers,
    const std::size_t& layersCount,
    TileSet** tileSets,
    const std::size_t& tileSetsCount
  ) :
    m_infinite(infinite),
    m_height(height),
    m_width(width),
    m_nextLayerId(nextLayerId),
    m_nextObjectId(nextObjectId),
    m_tileHeight(tileHeight),
    m_tileWidth(tileWidth),
    m_orientation(orientation),
    m_renderOrder(renderOrder),
    m_layers(layers),
    m_layersCount(layersCount),
    m_tileSets(tileSets),
    m_tileSetsCount(tileSetsCount)
  {
    m_tiledVersion = tiledVersion ? new char[std::strlen(tiledVersion) + 1] : nullptr;
    if (m_tiledVersion)
    {
      std::strcpy(m_tiledVersion, tiledVersion);
    }

    m_type = type ? new char[std::strlen(type) + 1] : nullptr;
    if (m_type)
    {
      std::strcpy(m_type, type);
    }

    m_version = version ? new char[std::strlen(version) + 1] : nullptr;
    if (m_version)
    {
      std::strcpy(m_version, version);
    }
  }

  TiledMap::~TiledMap()
  {
    delete[] m_tiledVersion;
    delete[] m_type;
    delete[] m_version;

    if (m_layers)
    {
      for (std::size_t i = 0; i < m_layersCount; ++i)
        delete m_layers[i];

      delete[] m_layers;
      m_layers = nullptr;
      m_layersCount = 0;
    }

    if (m_tileSets)
    {
      for (std::size_t i = 0; i < m_tileSetsCount; ++i)
        delete m_tileSets[i];

      delete[] m_tileSets;
      m_tileSets = nullptr;
      m_tileSetsCount = 0;
    }
  }

  const MapLayer* TiledMap::getLayerAt(const std::size_t& index) const
  {
    if (index >= m_layersCount)
    {
      throw std::out_of_range("TiledMap::getLayerAt: Index out of range.");
    }
    return m_layers[index];
  }

  const TileSet* TiledMap::getTileSetAt(const std::size_t& index) const
  {
    if (index >= m_tileSetsCount)
    {
      throw std::out_of_range("TiledMap::getTileSetAt: Index out of range.");
    }
    return m_tileSets[index];
  }
}