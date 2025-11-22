#include "TMR/tmrPathUtilities.h"

#include <memory>
#include <cstring>
#include <filesystem>

using std::filesystem::path;

namespace tmr
{
  namespace pathUtilities
  {
    char* combinePaths(const char* path1, const char* path2)
    {
      path p1(path1);
      path p2(path2);
      path combined = p1 / p2;

      std::string combinedStr = combined.string();
      char* result = new char[combinedStr.size() + 1];
      std::strcpy(result, combinedStr.c_str());

      return result;
    }

    char* getDirectoryFromPath(const char* filePath)
    {
      path p(filePath);
      path directory = p.parent_path();

      std::string directoryStr = directory.string();
      char* result = new char[directoryStr.size() + 1];
      std::strcpy(result, directoryStr.c_str());

      return result;
    }
  }
}
