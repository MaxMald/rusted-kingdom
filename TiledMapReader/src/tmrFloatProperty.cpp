#include "TMR/tmrFloatProperty.h"

namespace tmr
{
  FloatProperty::FloatProperty(const char* name, float value) :
    Property(name, propertyType::Type::Float),
    m_value(value)
  {
  }

  FloatProperty::~FloatProperty()
  {
  }
}