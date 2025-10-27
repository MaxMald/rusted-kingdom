#pragma once

#include <string>
#include <cstdarg>
#include <vector>

/**
 * @brief A string class that extends std::string with additional utilities.
 */
class String : public std::string
{
public:
  using std::string::string;

  /**
   * @brief Formats a string using printf-style formatting.
   *
   * Creates a formatted string using the specified format and arguments. This
   * method behaves similarly to C#'s String.Format or C's sprintf.
   *
   * @param fmt The format string (printf-style).
   * @param ... Variable arguments to format.
   * @return A formatted String object.
   *
   * @note
   *   - The format string must be compatible with printf.
   *   - Buffer resizing is handled automatically for long output.
   *   - Returns an empty String if formatting fails.
   */
  static String Format(const char* fmt, ...)
  {
    va_list args;

    va_start(args, fmt);

    std::vector<char> buffer(1024);
    int len = std::vsnprintf(buffer.data(), buffer.size(), fmt, args);

    va_end(args);

    if (len < 0) {
      return String();
    }

    if (static_cast<size_t>(len) >= buffer.size()) {
      buffer.resize(len + 1);

      va_start(args, fmt);
      std::vsnprintf(buffer.data(), buffer.size(), fmt, args);
      va_end(args);
    }

    return String(buffer.data());
  }
};
