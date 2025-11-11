#include "rkGameObjectBuilder.h"
#include "rkAssetManager.h"
#include "rkSpriteComponent.h"
#include "rkAnimationComponent.h"
#include "rkEightDirectionsSpriteSheetAnimationDescription.h"

namespace rk
{
  GameObjectBuilder::GameObjectBuilder(const AssetManager& assetsManager)
    : m_assetsManager(&assetsManager), m_current(nullptr)
  {
  }

  GameObjectBuilder::~GameObjectBuilder()
  {
    if (m_current)
    {
      delete m_current;
      m_current = nullptr;
    }
    m_assetsManager = nullptr;
  }

  GameObjectBuilder& GameObjectBuilder::createGameObject()
  {
    assertCurrentIsNull();
    m_current = new GameObject();
    return *this;
  }

  GameObjectBuilder& GameObjectBuilder::createGameObject(const String& name)
  {
    assertCurrentIsNull();
    m_current = new GameObject(name.c_str());
    return *this;
  }

  GameObjectBuilder& GameObjectBuilder::position(const sf::Vector2f& position)
  {
    assertCurrentIsNotNull();
    m_current->setPosition(position);
    return *this;
  }

  GameObjectBuilder& GameObjectBuilder::withSpriteComponent(
    const String& textureKey
  )
  {
    assertCurrentIsNotNull();
    assertAssetManagerHasTexture(textureKey);

    const sf::Texture* texture = m_assetsManager->getTexture(textureKey);
    SpriteComponent* spriteComponent = new SpriteComponent(*m_current, *texture);
    m_current->addComponent(UniquePtr<Component>(spriteComponent));

    return *this;
  }

  GameObjectBuilder& GameObjectBuilder::withSpriteComponent(
    const String& textureKey, 
    const sf::IntRect& textureRect
  )
  {
    assertCurrentIsNotNull();
    assertAssetManagerHasTexture(textureKey);

    const sf::Texture* texture = m_assetsManager->getTexture(textureKey);
    SpriteComponent* spriteComponent = new SpriteComponent(
      *m_current,
      *texture
    );
    spriteComponent->setTextureRect(textureRect);
    m_current->addComponent(UniquePtr<Component>(spriteComponent));
    return *this;
  }

  GameObjectBuilder& GameObjectBuilder::withAnimationComponent()
  {
    assertCurrentIsNotNull();
    AnimationComponent* animationComponent = new AnimationComponent(*m_current);
    m_current->addComponent(UniquePtr<Component>(animationComponent));
    return *this;
  }

  GameObjectBuilder& GameObjectBuilder::withAnimationComponent(
    const String& animationKey
  )
  {
    assertCurrentIsNotNull();
    if (!m_assetsManager->hasEightDirectionAnimation(animationKey))
    {
      throw RuntimeErrorException(
        String::Format(
          "GameObjectBuilder error: Eight Direction Animation with key '%s' not found "
          "in AssetManager.",
          animationKey.c_str()
        )
      );
    }

    const EightDirectionsSpriteSheetAnimationDescription* animationDescription =
      m_assetsManager->getEightDirectionAnimation(animationKey);

    assertAssetManagerHasTexture(animationDescription->getTextureKey());
    const sf::Texture* texture = m_assetsManager->getTexture(
      animationDescription->getTextureKey()
    );

    AnimationComponent* animationComponent = new AnimationComponent(*m_current);
    m_current->addComponent(UniquePtr<Component>(animationComponent));

    animationComponent->setAnimation(*animationDescription, *texture);
    return *this;
  }

  void GameObjectBuilder::buildWithParent(GameObject& parent)
  {
    assertCurrentIsNotNull();
    parent.addChild(UniquePtr<GameObject>(m_current));
    m_current = nullptr;
  }

  UniquePtr<GameObject> GameObjectBuilder::build()
  {
    assertCurrentIsNotNull();
    UniquePtr<GameObject> result(m_current);
    m_current = nullptr;
    return result;
  }

  void GameObjectBuilder::assertCurrentIsNull() const
  {
    if (m_current)
      throw RuntimeErrorException(
        "GameObjectBuilder error: Current GameObject is not null."
      );
  }

  void GameObjectBuilder::assertCurrentIsNotNull() const
  {
    if (!m_current)
      throw RuntimeErrorException(
        "GameObjectBuilder error: Current GameObject is null."
      );
  }

  void GameObjectBuilder::assertAssetManagerHasTexture(
    const String& textureKey
  ) const
  {
    if (!m_assetsManager->hasTexture(textureKey))
    {
      throw RuntimeErrorException(
        String::Format(
          "GameObjectBuilder error: Texture with key '%s' not found in "
          "AssetManager.",
          textureKey.c_str()
        )
      );
    }
  }
}