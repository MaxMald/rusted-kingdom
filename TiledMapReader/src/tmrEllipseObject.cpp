#include "TMR/tmrEllipseObject.h"

namespace tmr
{
  EllipseObject::EllipseObject(
    uint32_t id,
    uint32_t width,
    uint32_t height,
    bool visible,
    float x,
    float y,
    const char* name,
    const char* type,
    Properties* properties
  ) :
    Object(
      objectType::Ellipse,
      id, x, y,
      visible,
      name,
      type,
      properties
    ),
    m_width(width),
    m_height(height)
  {
  } 
   
  EllipseObject::~EllipseObject()
  {
  }
}