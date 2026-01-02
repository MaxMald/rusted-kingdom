#include "rkTileGameObjectBlueprint.h"
#include "rkGameObject.h"
#include "rkSpriteComponent.h"
#include "rkSpriteComponentFactory.h"

namespace rk
{
  TileGameObjectBlueprint::TileGameObjectBlueprint(
    ComponentFactoryLocator& componentFactoryLocator
  ) :
    GameObjectBlueprint(componentFactoryLocator),
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
    SharedPtr<SpriteComponentFactory> spriteComponentFactory =
      m_componentFactoryLocator.get<SpriteComponentFactory>();

    UniquePtr<SpriteComponent> spriteComponent =
      spriteComponentFactory->createSpriteComponent(
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