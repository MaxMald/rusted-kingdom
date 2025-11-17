#include "TMR/tmrDrawOrderParser.h"
#include <string>
#include <stdexcept>

namespace tmr
{
  namespace drawOrderParser
  {
    drawOrder::Type parseFromString(const char* str)
    {
      if(!str)
        throw std::runtime_error("str is null");

      std::string drawOrderStr(str);

      if(drawOrderStr == "topdown")
        return drawOrder::Type::TopDown;
      else if(drawOrderStr == "index")
        return drawOrder::Type::Index;
      else
        throw std::runtime_error("Unknown draw order string: " + drawOrderStr);
    }
  }
}