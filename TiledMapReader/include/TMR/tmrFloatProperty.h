#pragma once

#include "TMR/tmrProperty.h"

namespace tmr
{
  class TMR_API FloatProperty : public Property 
  {
  public:
    FloatProperty(const char* name, float value);
    virtual ~FloatProperty();

    float getValue() const { return m_value; }

  private:
    float m_value;
  };
}