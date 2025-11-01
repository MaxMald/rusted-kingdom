#include "rkTiledMap.h"
#include <TMR/tmrTiledMapReader.h>
#include <TMR/tmrTiledMap.h>
#include <TMR/tmrTileSet.h>

namespace rk
{
  TiledMap::TiledMap() :
    m_tmrTiledMap(nullptr),
    m_tileSetsManager()
  {
  }

  TiledMap::~TiledMap()
  {
    clear();
  }

  bool TiledMap::loadFromFile(const Path& filename)
  {
    clear();

    try
    {
      tmr::TiledMapReader tiledMapReader;
      tmr::TiledMap* loadedTiledMap = tiledMapReader.readFromFile(
        filename.string().c_str()
      );

      if (!loadedTiledMap)
        return false;

      m_tmrTiledMap = loadedTiledMap;

      Path rootDirectory = filename.parent_path();
      m_tileSetsManager.load(rootDirectory, loadedTiledMap);
    }
    catch (const std::exception& /*e*/)
    {
      clear();
      return false;
    }
    catch (...)
    {
      clear();
      return false;
    }

    return true;
  }

  bool TiledMap::isInfinite() const
  {
    return m_tmrTiledMap->isInfinite();
  }

  Int32 TiledMap::getHeight() const
  {
    return m_tmrTiledMap->getHeight();
  }

  Int32 TiledMap::getWidth() const
  {
    return m_tmrTiledMap->getWidth();
  }

  Int32 TiledMap::getNextLayerId() const
  {
    return m_tmrTiledMap->getNextLayerId();
  }

  Int32 TiledMap::getNextObjectId() const
  {
    return m_tmrTiledMap->getNextObjectId();
  }

  Int32 TiledMap::getTileHeight() const
  {
    return m_tmrTiledMap->getTileHeight();
  }

  Int32 TiledMap::getTileWidth() const
  {
    return m_tmrTiledMap->getTileWidth();
  }

  tmr::orientation::Type TiledMap::getOrientation() const
  {
    return m_tmrTiledMap->getOrientation();
  }

  tmr::renderOrder::Type TiledMap::getRenderOrder() const
  {
    return m_tmrTiledMap->getRenderOrder();
  }

  String TiledMap::getTiledVersion() const
  {
    return String(m_tmrTiledMap->getTiledVersion());
  }

  String TiledMap::getType() const
  {
    return String(m_tmrTiledMap->getType());
  }

  String TiledMap::getVersion() const
  {
    return String(m_tmrTiledMap->getVersion());
  }

  SizeT TiledMap::getLayersCount() const
  {
    return m_tmrTiledMap->getLayersCount();
  }

  const tmr::MapLayer* TiledMap::getLayerAt(const SizeT& index) const
  {
    return m_tmrTiledMap->getLayerAt(index);
  }

  TileSetsManager& TiledMap::getTileSetsManager()
  {
    return m_tileSetsManager;
  }

  const TileSetsManager& TiledMap::getTileSetsManager() const
  {
    return m_tileSetsManager;
  }

  void TiledMap::clear()
  {
    if (m_tmrTiledMap)
    {
      delete m_tmrTiledMap;
      m_tmrTiledMap = nullptr;
    }

    m_tileSetsManager.clear();
  }
}