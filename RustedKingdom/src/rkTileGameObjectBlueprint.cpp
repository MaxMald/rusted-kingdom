#include "rkTileGameObjectBlueprint.h"
#include "rkGameObject.h"
#include "rkSpriteComponent.h"
#include "rkSpriteComponentFactory.h"

namespace rk
{
  TileGameObjectBlueprint::TileGameObjectBlueprint() :
    m_description()
  {
  }

  TileGameObjectBlueprint::~TileGameObjectBlueprint()
  {
  }

  void TileGameObjectBlueprint::setDescription(
    const TiledObjectSpriteDescriptor& description
  )
  {
    m_description = description;
  }

  void TileGameObjectBlueprint::apply(GameObject& gameObject) const
  {
    UniquePtr<SpriteComponent> spriteComponent =
      spriteComponentFactory::createSpriteComponent(
        gameObject,
        m_description.getTextureKey(),
        m_description.getRect()
      );

    spriteComponent->setOrigin(
      sf::Vector2f(
        static_cast<float>(m_description.getRect().size.x) * m_description.getOrigin().x,
        static_cast<float>(m_description.getRect().size.y) * m_description.getOrigin().y
      )
    );

    gameObject.addComponent(std::move(spriteComponent));
  }
}