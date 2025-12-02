#include "TMR/tmrTileSetTile.h"

#include <cstring>

#include "TMR/tmrObjectGroup.h"
#include "TMR/tmrImage.h"
#include "TMR/tmrProperties.h"

namespace tmr
{
  TileSetTile::TileSetTile(
    std::uint32_t id,
    Image* image,
    Properties* properties,
    ObjectGroup* objectGroup
  ) :
    m_id(id),
    m_image(image),
    m_properties(properties),
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

    if (m_properties)
    {
      delete m_properties;
      m_properties = nullptr;
    }
  }
}