#pragma once

#include "rkPrerequisites.h"

namespace sf
{
  class Sprite;
}

using sf::Sprite;

namespace rk
{
  class AnimationState;

  class AnimationStateMachine
  {
  public:
    AnimationStateMachine();
    ~AnimationStateMachine();

    AnimationState* getCurrentState() const { return m_currentState; }

    bool hasFloat(const String& key) const;
    void addFloat(const String& key, float initialValue);
    void setFloat(const String& key, float value);
    float getFloat(const String& key) const;
    bool hasBool(const String& key) const;
    void addBool(const String& key, bool initialValue);
    void setBool(const String& key, bool value);
    bool getBool(const String& key) const;

    /**
     * @brief Adds an animation state to the state machine. Ownership of the
     * state is transferred to the state machine.
     * 
     * @param state The state to add.
     */
    void addState(AnimationState* state);
    void update(float deltaTime, Sprite& sprite);

  private:
    AnimationState* m_currentState;
    Vector<AnimationState*> m_states;
    UnorderedMap<String, float> m_floatParameters;
    UnorderedMap<String, bool> m_boolParameters;
  };
}