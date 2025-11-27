#pragma once

#include "TMR/tmrPrerequisites.h"
#include "TMR/tmrNonCopyable.h"
#include "TMR/tmrPropertyType.h"

namespace tmr
{
  class TMR_API Property : public NonCopyable
  {
  public:
    Property(const char* name, propertyType::Type type);
    virtual ~Property();

    const char* getName() const { return m_name; }
    propertyType::Type getType() const { return m_type; }

  private:
    char* m_name;
    propertyType::Type m_type;
  };
}