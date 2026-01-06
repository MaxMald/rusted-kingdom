#include "rkARuntimeDevToolView.h"

#include "imgui.h"
#include "imgui-SFML.h"

namespace rk
{
  void ARuntimeDevToolView::setName(const String& name)
  {
    m_name = name;
  }

  const String& ARuntimeDevToolView::getName() const
  {
    return m_name;
  }

  void ARuntimeDevToolView::destroy()
  {
    // Base implementation does nothing
  }

  void ARuntimeDevToolView::update(
    sf::RenderWindow& window,
    const sf::Time& elapsed
  )
  {
    if (!isOpen)
      return;

    onUpdate(window, elapsed);

    SizeT numChild = m_childViews.size();
    for (SizeT i = 0; i < numChild; ++i)
      m_childViews[i]->update(window, elapsed);
  }

  void ARuntimeDevToolView::draw(sf::RenderWindow& window)
  {
    if (!isOpen)
      return;

    ImGui::Begin(m_name.c_str());

    onDraw(window);

    SizeT numChild = m_childViews.size();
    for (SizeT i = 0; i < numChild; ++i)
      m_childViews[i]->draw(window);

    ImGui::End();
  }

  ARuntimeDevToolView::ARuntimeDevToolView() :
    isOpen(false), m_name(""), m_childViews()
  {
  }

  ARuntimeDevToolView::ARuntimeDevToolView(String name) :
    isOpen(false), m_name(name), m_childViews()
  {
  }

  ARuntimeDevToolView::ARuntimeDevToolView(String name, bool defaultOpen) :
    isOpen(defaultOpen), m_name(name), m_childViews()
  {
  }
}