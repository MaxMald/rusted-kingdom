#include "TMR/tmrData.h"

#include <stdexcept>

namespace tmr
{
  Data::Data(int32_t* data, const size_t& size) :
    m_size(size),
    m_data(data)
  {
  }

  Data::~Data()
  {
    if (m_data)
    {
      delete[] m_data;
      m_data = nullptr;
      m_size = 0;
    }
  }

  int32_t Data::getDataAt(const size_t& index) const
  {
    if (index >= m_size)
      throw std::out_of_range("Index out of range in Data::getDataAt");
    return m_data[index];
  }
}