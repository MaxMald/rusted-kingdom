#pragma once

#include "TMR/tmrPrerequisites.h"
#include "TMR/tmrNonCopyable.h"
#include "TMR/tmrObjectType.h"

namespace tmr
{
  class TMR_API Object : public NonCopyable
  {
  public:
    Object(
      objectType::Type objectType,
      uint32_t id,
      float x,
      float y,
      bool visible,
      const char* name,
      const char* type
    );
    virtual ~Object();

    objectType::Type getObjectType() const noexcept { return m_objectType; }
    uint32_t getId() const noexcept { return m_id; }
    bool isVisible() const noexcept { return m_visible; }
    float getX() const noexcept { return m_x; }
    float getY() const noexcept { return m_y; }
    const char* getName() const noexcept { return m_name; }
    const char* getType() const noexcept { return m_type; }

  private:
    objectType::Type m_objectType;
    uint32_t m_id;
    float m_x;
    float m_y;
    bool m_visible;
    char* m_name;
    char* m_type;
  };
}