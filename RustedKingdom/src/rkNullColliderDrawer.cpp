#include "rkNullColliderDrawer.h"

namespace rk
{
  NullColliderDrawer::NullColliderDrawer()
  {
  }

  NullColliderDrawer::~NullColliderDrawer()
  {
  }

  void NullColliderDrawer::draw(
    sf::RenderWindow&,
    const Collider&,
    const sf::Color&
  )
  {
    // Intentionally does nothing
  }
}