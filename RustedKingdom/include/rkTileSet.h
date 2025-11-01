#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <TMR/tmrTileSet.h>
#include "rkPrerequisites.h"

namespace tmr
{
  class TileSet;
}

namespace rk
{
  /**
   * @class TileSet
   * @brief Lightweight wrapper around a parsed Tiled tileset used by the
   * engine.
   */
  class TileSet
  {
  public:

    /**
     * @brief Constructs a TileSet wrapper.
     *
     * Combines the provided \p mapRootDirectory with the image path from \p
     * tmrTileSet to form an absolute or normalized image filepath used by the
     * engine.
     *
     * @param mapRootDirectory Filesystem path that is used as the base when
     * resolving relative image paths from the tileset.
     * @param tmrTileSet Pointer to the parsed tileset from the TMR reader. Not
     * owned;
     */
    TileSet(
      const Path& mapRootDirectory,
      const tmr::TileSet* tmrTileSet
    );

    /**
     * @brief Destructor.
     *
     * Does not delete the wrapped \p tmr::TileSet pointer (ownership is not
     * transferred to rk::TileSet).
     */
    ~TileSet();

    /** @return margin in pixels */
    Int32 getMargin() const
    {
      return m_tmrTileSet->getMargin();
    }

    /** @return first global tile id */
    Int32 getFirstGid() const
    {
      return m_tmrTileSet->getFirstGid();
    }

    /** @return number of columns in the source image */
    UInt32 getColumns() const
    {
      return m_tmrTileSet->getColumns();
    }

    /** @return source image height in pixels */
    UInt32 getImageHeight() const
    {
      return m_tmrTileSet->getImageHeight();
    }

    /** @return source image width in pixels */
    UInt32 getImageWidth() const
    {
      return m_tmrTileSet->getImageWidth();
    }

    /** @return spacing in pixels between tiles */
    UInt32 getSpacing() const
    {
      return m_tmrTileSet->getSpacing();
    }

    /** @return number of tiles in the tileset */
    UInt32 getTileCount() const
    {
      return m_tmrTileSet->getTileCount();
    }

    /** @return tile height in pixels */
    UInt32 getTileHeight() const
    {
      return m_tmrTileSet->getTileHeight();
    }

    /** @return tile width in pixels */
    UInt32 getTileWidth() const
    {
      return m_tmrTileSet->getTileWidth();
    }

    /** @return tileset display name */
    String getName() const
    {
      return m_name;
    }

    /**
     * @brief Gets the image key derived from the tileset's image filename.
     *
     * The image key is typically the filename stem and is suitable as a
     * lookup key in the engine's asset manager.
     *
     * @return Image key.
     */
    const String& getImageKey() const
    {
      return m_imageKey;
    }

    /**
     * @brief Gets the resolved image filepath.
     *
     * This is the path obtained by combining \p mapRootDirectory and the
     * tileset's image path (if the latter is relative), then normalizing the
     * result.
     *
     * @return Filesystem path to the tileset image.
     */
    const Path& getImageFilepath() const
    {
      return m_imageFilepath;
    }

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
    String m_name;                       ///< Tileset display name
    String m_imageKey;                   ///< Derived key for engine assets
    Path m_imageFilepath;                     ///< Resolved image file path
    const tmr::TileSet* m_tmrTileSet;         ///< Non-owning pointer to parser tileset
  };
}
