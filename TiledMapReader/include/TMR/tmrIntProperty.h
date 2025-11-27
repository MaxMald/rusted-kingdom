#pragma once

#include "TMR/tmrProperty.h"

namespace tmr
{
  class TMR_API IntProperty : public Property 
  {
  public:
    IntProperty(const char* name, int32_t value);
    virtual ~IntProperty();

    int32_t getValue() const { return m_value; }

  private:
    int32_t m_value;
  };
}