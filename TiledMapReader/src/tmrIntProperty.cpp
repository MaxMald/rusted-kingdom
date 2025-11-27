#include "TMR/tmrIntProperty.h"

namespace tmr
{
  IntProperty::IntProperty(const char* name, int value) :
    Property(name, propertyType::Type::Int),
    m_value(value)
  {
  }

  IntProperty::~IntProperty()
  {
  }
}