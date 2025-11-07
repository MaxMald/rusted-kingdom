#pragma once

#include "TMR/tmrPrerequisites.h"

namespace tmr
{
    class TMR_API Object
    {
    public:
      Object(
        std::uint32_t gid,
        std::uint32_t id,
        std::uint32_t height,
        std::uint32_t width,
        bool visible,
        float rotation,
        float x,
        float y,
        const char* name,
        const char* type
      );
      ~Object();

      std::uint32_t getGid() const noexcept { return m_gid; }
      std::uint32_t getId() const noexcept { return m_id; }
      std::uint32_t getHeight() const noexcept { return m_height; }
      std::uint32_t getWidth() const noexcept { return m_width; }
      bool isVisible() const noexcept { return m_visible; }
      float getRotation() const noexcept { return m_rotation; }
      float getX() const noexcept { return m_x; }
      float getY() const noexcept { return m_y; }
      const char* getName() const noexcept { return m_name; }
      const char* getType() const noexcept { return m_type; }

    private:
      std::uint32_t m_gid;
      std::uint32_t m_id;
      std::uint32_t m_height;
      std::uint32_t m_width;
      bool m_visible;
      float m_rotation;
      float m_x;
      float m_y;
      char* m_name;
      char* m_type;
    };
}