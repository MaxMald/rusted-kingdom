#pragma once

#include "TMR/tmrPrerequisites.h"
#include "TMR/tmrNonCopyable.h"

namespace tmr
{
  class TMR_API Data : public NonCopyable
  {
  public:
    Data(int32_t* data, const size_t& size);
    virtual ~Data();

    /**
     * @brief Gets the size of the data array.
     * @return The size of the data array.
     */
    const size_t& getSize() const { return m_size; }

    /**
     * @brief Gets a pointer to the data array.
     * @return Pointer to the data array.
     */
    int32_t getDataAt(const size_t& index) const;

  private:
    size_t m_size;
    int32_t* m_data;
  };
}