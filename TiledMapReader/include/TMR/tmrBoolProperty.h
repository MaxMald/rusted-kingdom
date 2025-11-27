#pragma once

#include "TMR/tmrProperty.h"

namespace tmr
{
  class TMR_API BoolProperty : public Property 
  {
  public:
    BoolProperty(const char* name, bool value);
    virtual ~BoolProperty();

    bool getValue() const { return m_value; }

  private:
    bool m_value;
  };
}