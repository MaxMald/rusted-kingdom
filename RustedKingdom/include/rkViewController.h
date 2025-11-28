#pragma once

#include <SFML/Graphics/View.hpp>

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"

using sf::View;

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

  private:
    View m_view;
    String m_name;
  };
}