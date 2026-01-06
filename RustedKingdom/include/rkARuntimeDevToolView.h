#pragma once

#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"

namespace rk
{
  class ARuntimeDevToolView : public NonCopyable
  {
  public:
    bool isOpen;

    virtual ~ARuntimeDevToolView() = default;

    void setName(const String& name);
    const String& getName() const;

    virtual void destroy();

    void update(sf::RenderWindow& window, const sf::Time& elapsed);
    void draw(sf::RenderWindow& window);

  protected:
    String m_name;
    Vector<SharedPtr<ARuntimeDevToolView>> m_childViews;

    ARuntimeDevToolView();
    ARuntimeDevToolView(String name);
    ARuntimeDevToolView(String name, bool defaultOpen);

    virtual void onUpdate(sf::RenderWindow& window, const sf::Time& elapsed) = 0;
    virtual void onDraw(sf::RenderWindow& window) = 0;
  };
}