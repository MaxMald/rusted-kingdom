#pragma once

#include <TMR/tmrOrientation.h>
#include <TMR/tmrRenderOrder.h>
#include "rkPrerequisites.h"
#include "rkTileSetsManager.h"
#include "rkIsometricPositionTransformer.h"

namespace tmr
{
  class TiledMap;
  class MapLayer;
};

namespace rk
{
  /**
  * @class TiledMap
  * @brief Wrapper around a parsed Tiled map used by the engine.
  *
  * This class owns or references the parsed representation returned by the
  * project's TMR reader and coordinates creation/loading of engine-facing
  * tileset wrappers via rk::TileSetsManager.
  */
  class TiledMap
  {
  public:
    TiledMap();
    ~TiledMap();
    
    bool loadFromFile(const Path& filename);
    bool isInfinite() const;
    Int32 getHeight() const;
    Int32 getWidth() const;
    Int32 getNextLayerId() const;
    Int32 getNextObjectId() const;
    Int32 getTileHeight() const;
    Int32 getTileWidth() const;
    tmr::orientation::Type getOrientation() const;
    tmr::renderOrder::Type getRenderOrder() const;
    String getTiledVersion() const;
    String getType() const;
    String getVersion() const;
    SizeT getLayersCount() const;
    const tmr::MapLayer* getLayerAt(const SizeT& index) const;
    TileSetsManager& getTileSetsManager();
    const TileSetsManager& getTileSetsManager() const;
    const IsometricPositionTransformer& getIsometricPositionTransformer() const;

  private:
    tmr::TiledMap* m_tmrTiledMap;
    TileSetsManager m_tileSetsManager;
    IsometricPositionTransformer m_isometricPositionTransformer;

    void clear();
    void updateIsometricPositionTransformer();
  };
}