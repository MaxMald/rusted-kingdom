#pragma once

#include "TMR/tmrPrerequisites.h"
#include "TMR/tmrJson.h"
#include "TMR/tmrObjectParser.h"

namespace tmr
{
  class ObjectGroup;

  class ObjectGroupParser
  {
  public:
    ObjectGroupParser();
    ~ObjectGroupParser();

    ObjectGroup* parseFromJson(const Json& json);

  private:
    ObjectParser m_objectParser;
  };
}