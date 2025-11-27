#pragma once

#include "TMR/tmrProperty.h"

namespace tmr
{
  class TMR_API ColorProperty : public Property 
  {
  public:
    ColorProperty(const char* name, const char* value);
    virtual ~ColorProperty();

    const char* getValue() const { return m_value; }

  private:
    char* m_value;
  };
}