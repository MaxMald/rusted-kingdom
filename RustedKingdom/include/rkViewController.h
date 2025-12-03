#pragma once

#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"

using sf::View;
using sf::Vector2f;

namespace rk
{
  class ViewController : public NonCopyable
  {
  public:
    ViewController(const String& name);
    ViewController(const String& name, const View&);
    ~ViewController();

    const String& getName() const;
    void setView(const View& view);
    const View& getView() const;
    void setViewCenter(const Vector2f& center);

  private:
    View m_view;
    String m_name;
  };
}