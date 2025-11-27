#include "TMR/tmrObjectProperty.h"

namespace tmr
{
  ObjectProperty::ObjectProperty(const char* name, int32_t value) :
    Property(name, propertyType::Type::Object),
    m_value(value)
  {
  }

  ObjectProperty::~ObjectProperty()
  {
  }
}