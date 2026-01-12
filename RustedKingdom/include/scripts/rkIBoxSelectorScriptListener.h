#pragma once

#include <SFML/System/Vector2.hpp>

#include "rkPrerequisites.h"

using sf::Vector2f;

namespace rk
{
  class IBoxSelectorScriptListener
  {
  public:
    virtual ~IBoxSelectorScriptListener() = default;

    virtual void onBoxSelectionStarted(
      const Vector2f& boxP1,
      const Vector2f& boxP2
    ) = 0;

    virtual void onBoxSelectionUpdated(
      const Vector2f& boxP1,
      const Vector2f& boxP2
    ) = 0;

    virtual void onBoxSelectionEnded(
      const Vector2f& boxP1,
      const Vector2f& boxP2
    ) = 0;

  protected:
    IBoxSelectorScriptListener() = default;
  };
}