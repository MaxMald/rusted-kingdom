#pragma once

#include "rkPrerequisites.h"

namespace tmr
{
  class TileSetTile;
}

namespace rk
{
  class TileSetTile
  {
  public:
    TileSetTile();
    TileSetTile(const TileSetTile& other);
    TileSetTile& operator=(const TileSetTile& other);
    TileSetTile(TileSetTile&& other) noexcept;
    TileSetTile& operator=(TileSetTile&& other) noexcept;
    TileSetTile(const Path& mapRootDirectory, const tmr::TileSetTile& tileSetTile);
    ~TileSetTile();

    UInt32 getId() const { return m_id; }
    UInt32 getImageWidth() const { return m_imageWidth; }
    UInt32 getImageHeight() const { return m_imageHeight; }
    const Path& getImagePath() const { return m_imagePath; }

  private:
    UInt32 m_id;
    UInt32 m_imageWidth;
    UInt32 m_imageHeight;
    Path m_imagePath;
  };
}