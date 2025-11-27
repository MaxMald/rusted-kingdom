#pragma once

#include "TMR/tmrPrerequisites.h"
#include "TMR/tmrNonCopyable.h"

namespace tmr
{
  class Property;

  class TMR_API Properties : public NonCopyable
  {
  public:
    Properties(Property** properties, size_t propertyCount);
    ~Properties();

    size_t getPropertyCount() const { return m_propertyCount; }
    Property* getPropertyAt(size_t index) const;

  private:
    Property** m_properties;
    size_t m_propertyCount;
  };
}