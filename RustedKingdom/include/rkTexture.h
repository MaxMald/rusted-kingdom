#pragma once

#include <SFML/Graphics/Texture.hpp>

#include "rkIAsset.h"

using sf::Texture;

namespace rk
{
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