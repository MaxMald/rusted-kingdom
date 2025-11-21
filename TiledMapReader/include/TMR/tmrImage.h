#pragma once

#include "TMR/tmrNonCopyable.h"

namespace tmr
{
  /**
   * @brief Represents an image resource in a tileset.
   *
   * Stores the source path and dimensions of an image, typically used for tileset images.
   * Inherits from NonCopyable to prevent copying.
   */
  class TMR_API Image : public NonCopyable
  {
  public:
    /**
     * @brief Constructs an Image with the given source path and dimensions.
     * 
     * @param source Path to the image file. Source is copied internally.
     * @param width Width of the image in pixels.
     * @param height Height of the image in pixels.
     */
    Image(
      const char* source,
      const uint32_t width,
      const uint32_t height
    );

    /**
     * @brief Destroys the Image.
     */
    ~Image();

    /**
     * @brief Gets the source path of the image.
     * 
     * @return C-string representing the image file path.
     */
    const char* getSource() const { return m_source; }

    /**
     * @brief Gets the width of the image in pixels.
     * 
     * @return Width of the image.
     */
    uint32_t getWidth() const { return m_width; }

    /**
     * @brief Gets the height of the image in pixels.
     * 
     * @return Height of the image.
     */
    uint32_t getHeight() const { return m_height; }

  private:
    char* m_source;
    uint32_t m_width;
    uint32_t m_height;
  };
} 