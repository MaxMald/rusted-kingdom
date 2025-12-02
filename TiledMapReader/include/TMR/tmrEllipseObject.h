#pragma once

#include "TMR/tmrObject.h"

namespace tmr
{
  class TMR_API EllipseObject : public Object
  {
  public:
    EllipseObject(
      uint32_t id,
      uint32_t width,
      uint32_t height,
      bool visible,
      float x,
      float y,
      const char* name,
      const char* type,
      Properties* properties
    );
    ~EllipseObject() override;

    uint32_t getWidth() const noexcept { return m_width; }
    uint32_t getHeight() const noexcept { return m_height; }

  private:
    uint32_t m_width;
    uint32_t m_height;
  };
}