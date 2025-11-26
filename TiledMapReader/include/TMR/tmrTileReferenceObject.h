#pragma once

#include "TMR/tmrObject.h"

namespace tmr
{
  class TMR_API TileReferenceObject : public Object
  {
  public:
    TileReferenceObject(
      uint32_t gid,
      uint32_t id,
      uint32_t width,
      uint32_t height,
      bool visible,
      float rotation,
      float x,
      float y,
      const char* name,
      const char* type
    );
    virtual ~TileReferenceObject();

    uint32_t getGid() const noexcept { return m_gid; }
    uint32_t getHeight() const noexcept { return m_height; }
    uint32_t getWidth() const noexcept { return m_width; }
    float getRotation() const noexcept { return m_rotation; }

  private:
    std::uint32_t m_gid;
    std::uint32_t m_height;
    std::uint32_t m_width;
    float m_rotation;
  };
}