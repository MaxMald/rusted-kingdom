#include "TMR/tmrBoolProperty.h"

namespace tmr
{
  BoolProperty::BoolProperty(const char* name, bool value) :
    Property(name, propertyType::Type::Bool),
    m_value(value)
  {
  }

  BoolProperty::~BoolProperty()
  {
  }
}