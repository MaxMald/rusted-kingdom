#pragma once

#include <SFML/Graphics/Rect.hpp>
#include "rkTileSet.h"

namespace tmr
{
  class SpriteSheetTileSet;
}

namespace rk
{
  class SpriteSheetTileSet : public TileSet
  {
  public:

    SpriteSheetTileSet(
      const Path& mapRootDirectory,
      const tmr::SpriteSheetTileSet& tmrSpriteSheetTileSet
    );
    virtual ~SpriteSheetTileSet();

    Bool isGidInRange(const Int32& gid) const override;
    TileDescription getTileDescriptionAt(const Int32& localId) const override;

    const String& getName() const { return m_name; }
    const String getImageKey() const { return m_imageKey; }
    const Path& getImageFilepath() const { return m_imageFilepath; }
    Int32 getMargin() const { return m_margin; }
    UInt32 getColumns() const { return m_columns; }
    UInt32 getImageHeight() const { return m_imageHeight; }
    UInt32 getImageWidth() const { return m_imageWidth; }
    UInt32 getSpacing() const { return m_spacing; }
    UInt32 getTileCount() const { return m_tileCount; }
    UInt32 getTileHeight() const { return m_tileHeight; }
    UInt32 getTileWidth() const { return m_tileWidth; }

    /**
     * @brief Computes the texture rectangle for the specified local tile id.
     *
     * @param localId Local tile id within the tileset (zero-based).
     *
     * @return Rectangle (in pixels) within the tileset image that contains the
     * tile graphic.
     */
    sf::IntRect getTileTextureRect(const Int32& localId) const;

  private:
    String m_name;
    String m_imageKey;
    Path m_imageFilepath;
    Int32 m_margin;
    UInt32 m_columns;
    UInt32 m_imageHeight;
    UInt32 m_imageWidth;
    UInt32 m_spacing;
    UInt32 m_tileCount;
    UInt32 m_tileHeight;
    UInt32 m_tileWidth;
  };
}