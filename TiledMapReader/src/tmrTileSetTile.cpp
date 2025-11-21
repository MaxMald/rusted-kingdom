#include "TMR/tmrTileSetTile.h"

#include <cstring>

#include "TMR/tmrObjectGroup.h"
#include "TMR/tmrImage.h"

namespace tmr
{
  TileSetTile::TileSetTile(
    std::uint32_t id,
    Image* image,
    ObjectGroup* objectGroup
  ) :
    m_id(id),
    m_image(image),
    m_objectGroup(objectGroup)
  {
  }

  TileSetTile::~TileSetTile()
  {
    if (m_image)
    {
      delete m_image;
      m_image = nullptr;
    }

    if (m_objectGroup)
    {
      delete m_objectGroup;
      m_objectGroup = nullptr;
    }
  }
}