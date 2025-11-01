#pragma once

#include "rkPrerequisites.h"
#include <filesystem>

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
     * engine. If \p tmrTileSet is null, the instance will be empty.
     *
     * @param mapRootDirectory Filesystem path that is used as the base when
     * resolving relative image paths from the tileset.
     * @param tmrTileSet Pointer to the parsed tileset from the TMR reader. Not
     * owned;
     */
    TileSet(
      const std::filesystem::path& mapRootDirectory,
      const tmr::TileSet* tmrTileSet
    );

    /**
     * @brief Destructor.
     *
     * Does not delete the wrapped \p tmr::TileSet pointer (ownership is not
     * transferred to rk::TileSet).
     */
    ~TileSet();

    /**
     * @brief Gets the tileset name.
     * @return Tileset name as a std::string (empty if not available).
     */
    const std::string& getName() const
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
    const std::string& getImageKey() const
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
    const std::filesystem::path& getImageFilepath() const
    {
      return m_imageFilepath;
    }

    /**
     * @brief Gets the underlying TMR tileset pointer.
     *
     * @return Pointer to the original tmr::TileSet (may be nullptr).
     */
    const tmr::TileSet* getTmrTileSet() const
    {
      return m_tmrTileSet;
    }

  private:
    std::string m_name;                       ///< Tileset display name
    std::string m_imageKey;                   ///< Derived key for engine assets
    std::filesystem::path m_imageFilepath;    ///< Resolved image file path
    const tmr::TileSet* m_tmrTileSet;         ///< Non-owning pointer to parser tileset
  };
}
