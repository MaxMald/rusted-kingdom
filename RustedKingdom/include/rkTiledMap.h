#pragma once

#include <TMR/tmrOrientation.h>
#include <TMR/tmrRenderOrder.h>

#include "rkIAsset.h"
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
  class TiledMap : public IAsset
  {
  public:
    TiledMap();
    ~TiledMap();

    const tmr::TiledMap* getTmrTiledMap() const { return m_tmrTiledMap; }
    tmr::TiledMap* getTmrTiledMap() { return m_tmrTiledMap; }

  protected:
    virtual bool loadFromFile(const Path& filename) override;
    virtual void unload() override;

  private:
    tmr::TiledMap* m_tmrTiledMap;
  };
}