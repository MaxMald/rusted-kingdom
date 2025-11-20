#include "rkTexture.h"

namespace rk
{
  Texture::Texture() :
    m_texture()
  {
  }

  Texture::~Texture()
  {
  }

  bool Texture::loadFromFile(const Path& filename)
  {
    return m_texture.loadFromFile(filename);
  }

  void Texture::unload()
  {
    // SFML Texture does not require explicit unloading.
    // The destructor will handle resource cleanup.
  }
}