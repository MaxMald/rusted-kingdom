#include "rkAnimationFactory.h"

#include <SFML/Graphics/Texture.hpp>

#include "rkServiceLocator.h"
#include "rkAssetManager.h"
#include "rkEightDirAnimationDesc.h"
#include "rkEightDirectionsSpriteSheetAnimation.h"
#include "rkTexture.h"

namespace rk
{
  namespace animationFactory
  {
    UniquePtr<Animation> createEightDirectionsAnimation(
      const String& descriptionKey,
      const Blackboard& blackboard
    )
    {
      SharedPtr<AssetManager> assetManager = ServiceLocator::Instance()
        .getService<AssetManager>();

      const SharedPtr<EightDirAnimationDesc> description =
        assetManager->getAssetGroup<EightDirAnimationDesc>().get(descriptionKey);

      const SharedPtr<rk::Texture> texture =
        assetManager->getAssetGroup<rk::Texture>().get(description->getTextureKey());

      return MakeUnique<EightDirectionsSpriteSheetAnimation>(
        *description,
        blackboard,
        texture->getSFMLTexture()
      );
    }
  }
}