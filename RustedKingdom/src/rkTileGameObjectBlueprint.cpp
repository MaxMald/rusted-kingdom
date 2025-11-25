#include "rkTileGameObjectBlueprint.h"
#include "rkGameObject.h"
#include "rkSpriteComponent.h"
#include "rkSpriteComponentFactory.h"
#include "rkGameObjectBuilder.h"

namespace rk
{
  TileGameObjectBlueprint::TileGameObjectBlueprint(
    SpriteComponentFactory& spriteComponentFactory
  ) :
    m_spriteComponentFactory(spriteComponentFactory),
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

  GameObject* TileGameObjectBlueprint::instantiate(
    const String& name,
    GameObject& parent
  ) const
  {
    GameObjectBuilder gameObjectBuilder;
    GameObject* tileGameObject = gameObjectBuilder
      .createGameObject(name)
      .buildWithParent(parent);

    UniquePtr<SpriteComponent> spriteComponent =
      m_spriteComponentFactory.createSpriteComponent(
        *tileGameObject,
        m_description.getTextureKey(),
        m_description.getRect()
      );

    spriteComponent->setOrigin(
      sf::Vector2f(
        static_cast<float>(m_description.getRect().size.x) * m_description.getOrigin().x,
        static_cast<float>(m_description.getRect().size.y) * m_description.getOrigin().y
      )
    );

    tileGameObject->addComponent(std::move(spriteComponent));

    return tileGameObject;
  }
}