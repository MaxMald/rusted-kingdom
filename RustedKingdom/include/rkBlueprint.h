#pragma once

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"

namespace rk
{
  class GameObject;

  class Blueprint : public NonCopyable
  {
  public:
    Blueprint() : NonCopyable() {}
    virtual ~Blueprint() {}

    /**
     * @brief Instantiates a new GameObject based on this blueprint and adds it
     * as a child to the specified parent GameObject.
     * @param parent The parent GameObject to which the newly instantiated
     * GameObject will be added as a child.
     * @return A pointer to the newly instantiated GameObject, owned by the
     * parent.
     */
    virtual GameObject* instantiate(GameObject& parent) = 0;
  };
}