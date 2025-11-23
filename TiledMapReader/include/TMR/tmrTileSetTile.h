#pragma once

#include "TMR/tmrPrerequisites.h"
#include "TMR/tmrNonCopyable.h"

namespace tmr
{
  class ObjectGroup;
  class Image;

  /**
   * @brief Represents a single tile in a tileset.
   *
   * TileSetTile represents a single tile in a tileset, including its unique
   * identifier and image properties.
   */
  class TMR_API TileSetTile : public NonCopyable
  {
  public:
    TileSetTile(
      uint32_t id,
      Image* image,
      ObjectGroup* objectGroup = nullptr
    );
    ~TileSetTile();

    /** @return The unique identifier for the tile. */
    uint32_t getId() const { return m_id; }

    /** @return The image associated with this tile. */
    const Image* getImage() const { return m_image; }

    /** @return The image associated with this tile. */
    Image* getImage() { return m_image; }

    /** @return The object group associated with this tile, if any. */
    ObjectGroup* getObjectGroup() const { return m_objectGroup; }

  private:
    uint32_t m_id;
    Image* m_image;
    ObjectGroup* m_objectGroup;
  };
}