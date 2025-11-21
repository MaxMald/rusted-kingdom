#include "TMR/tmrImage.h"

#include <memory>
#include <cstring>

namespace tmr
{
  Image::Image(
    const char* source,
    const uint32_t width,
    const uint32_t height
  ) : 
    m_source(nullptr), m_width(width), m_height(height)
  {
    m_source = source ? new char[std::strlen(source) + 1] : nullptr;
    if (m_source)
      std::strcpy(m_source, source);
  }

  Image::~Image()
  {
    if (m_source)
    {
      delete[] m_source;
      m_source = nullptr;
    }
  }
}