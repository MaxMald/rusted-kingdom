#pragma once

#include <SFML/Graphics/Texture.hpp>

#include "rkIAsset.h"

using sf::Texture;

namespace rk
{
  /**
   * @brief Represents a texture asset managed by the engine.
   *
   * Wraps an SFML texture and provides asset loading/unloading functionality.
   * Inherits from IAsset to support asset management operations.
   */
  class Texture : public IAsset
  {
  public:
    Texture();
    virtual ~Texture();

    const sf::Texture& getSFMLTexture() const { return m_texture; }

  protected:
    virtual bool loadFromFile(const Path& filename) override;
    virtual void unload() override;

  private:
    sf::Texture m_texture;
  };
}