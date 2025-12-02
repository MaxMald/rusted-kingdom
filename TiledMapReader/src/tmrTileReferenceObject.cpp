#include "TMR/tmrTileReferenceObject.h"

namespace tmr
{
  TileReferenceObject::TileReferenceObject(
    uint32_t gid,
    uint32_t id,
    uint32_t width,
    uint32_t height,
    bool visible,
    float rotation,
    float x,
    float y,
    const char* name,
    const char* type,
    Properties* properties
  ) :
    Object(
      objectType::TileReference,
      id, x, y,
      visible,
      name,
      type,
      properties
    ),
    m_gid(gid),
    m_height(height),
    m_width(width),
    m_rotation(rotation)
  {
  }

  TileReferenceObject::~TileReferenceObject()
  {
  }
}