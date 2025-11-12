#include "rkAnimation.h"

namespace rk
{
  Animation::Animation(
    const AnimationStateMachine& animationStateMachine,
    const String& animationKey,
    animationType::Type type
  ) :
    m_type(type),
    m_animationKey(animationKey),
    m_isPlaying(false),
    m_animationStateMachine(&animationStateMachine)
  {
  }

  Animation::~Animation()
  {
  }
}