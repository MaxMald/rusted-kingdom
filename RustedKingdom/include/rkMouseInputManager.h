#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"
#include "rkIMouseButtonHandlerListener.h"

using sf::Vector2i;

namespace rk
{
  class IMouseInputManagerListener;
  class MouseButtonHandler;
  class WindowManager;

  class MouseInputManager : public NonCopyable, public IMouseButtonHandlerListener
  {
  public:
    MouseInputManager();
    ~MouseInputManager();

    /**
     * @brief Get the current position of the mouse in desktop coordinates.
     * 
     * This function returns the current position of the mouse cursor
     * on the desktop.
     * 
     * @returns Current position of the mouse cursor in desktop coordinates.
     */
    Vector2i getMousePosition() const;

    /**
     * @brief Get the current position of the mouse in window coordinates.
     *
     * This function returns the current position of the mouse cursor, relative
     * to the given application window.
     *
     * @returns Current position of the mouse cursor in window coordinates.
     */
    Vector2i getMousePositionRelativeToWindow() const;

    bool isButtonPressed(sf::Mouse::Button button) const;

    virtual void onMouseButtonPressed(sf::Mouse::Button button);
    virtual void onMouseButtonReleased(sf::Mouse::Button button);

    void prepare(SharedPtr<WindowManager> windowManager);
    void update();

    void subscribe(IMouseInputManagerListener* listener);
    void unsubscribe(IMouseInputManagerListener* listener);

  private:
    Vector<IMouseInputManagerListener*> m_listeners;
    UnorderedMap<sf::Mouse::Button, SharedPtr<MouseButtonHandler>> m_buttonHandlers;
    SharedPtr<WindowManager> m_windowManager;

    void registerButtonHandlers();
  };
}