#include "rkAnimationFactory.h"

#include <SFML/Graphics/Texture.hpp>

#include "rkAssetManager.h"
#include "rkEightDirectionsSpriteSheetAnimationDescription.h"
#include "rkEightDirectionsSpriteSheetAnimation.h"

namespace rk
{
  AnimationFactory::AnimationFactory(const AssetManager& assetManager) :
    m_assetManager(assetManager)
  {
  }

  AnimationFactory::~AnimationFactory()
  {
  }

  UniquePtr<Animation> AnimationFactory::createEightDirectionsAnimation(
    const String& descriptionKey,
    const Blackboard& blackboard
  )
  {
    EightDirectionsSpriteSheetAnimationDescription* description = m_assetManager
      .getEightDirectionAnimation(descriptionKey);

    sf::Texture* texture = m_assetManager
      .getTexture(description->getTextureKey());

    return MakeUnique<EightDirectionsSpriteSheetAnimation>(
      *description,
      blackboard,
      *texture
    );
  }
}