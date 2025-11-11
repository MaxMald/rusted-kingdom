#pragma once

#include "rkPrerequisites.h"

#include <TMR/tmrJson.h>

#include "rkAssertions.h"

namespace rk
{
  namespace jsonUtilities {

    String getStringFromJson(const tmr::Json& json)
    { 
      if (!json.isString())
      {
        throw InvalidArgumentException(
          "jsonUtilities::getStringFromJson: JSON value is not a string."
        );
      }

      String str;
      str.resize(json.getStringLength() + 1);
      json.getString(&str[0], str.size());
      str.resize(json.getStringLength());

      return str;
    }
  }
}