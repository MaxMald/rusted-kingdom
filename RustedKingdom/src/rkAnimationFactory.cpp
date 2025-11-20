#include "rkAnimationFactory.h"

#include <SFML/Graphics/Texture.hpp>

#include "rkAssetManager.h"
#include "rkEightDirAnimationDesc.h"
#include "rkEightDirectionsSpriteSheetAnimation.h"
#include "rkTexture.h"

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
    const SharedPtr<EightDirAnimationDesc> description = m_assetManager
      .getEightDirAnimationDescGroup().get(descriptionKey);

    const SharedPtr<rk::Texture> texture = m_assetManager
      .getTextureGroup().get(description->getTextureKey());

    return MakeUnique<EightDirectionsSpriteSheetAnimation>(
      *description,
      blackboard,
      texture->getSFMLTexture()
    );
  }
}