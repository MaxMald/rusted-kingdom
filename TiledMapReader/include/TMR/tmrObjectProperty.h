#pragma once

#include "TMR/tmrProperty.h"

namespace tmr
{
  class TMR_API ObjectProperty : public Property 
  {
  public:
    ObjectProperty(const char* name, int32_t value);
    virtual ~ObjectProperty();

    int32_t getValue() const { return m_value; }

  private:
    int32_t m_value;
  };
}