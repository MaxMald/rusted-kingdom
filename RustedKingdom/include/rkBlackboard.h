#pragma once

#include <SFML/System/Angle.hpp>
#include <SFML/System/Vector2.hpp>

#include "rkPrerequisites.h"
#include "rkBlackboardValueGroup.h"

using sf::Angle;
using sf::Vector2f;

namespace rk
{
  class Blackboard
  {
  public:
    Blackboard() = default;
    ~Blackboard() = default;

    Blackboard(const Blackboard&) = delete;
    Blackboard& operator=(const Blackboard&) = delete;
    Blackboard(Blackboard&&) noexcept = delete;
    Blackboard& operator=(Blackboard&&) noexcept = delete;

    BlackboardValueGroup<float>& getFloatValues() { return m_floatValues; }
    const BlackboardValueGroup<float>& getFloatValues() const { return m_floatValues; }

    BlackboardValueGroup<bool>& getBoolValues() { return m_boolValues; }
    const BlackboardValueGroup<bool>& getBoolValues() const { return m_boolValues; }

    BlackboardValueGroup<Angle>& getAngleValues() { return m_angleValues; }
    const BlackboardValueGroup<Angle>& getAngleValues() const { return m_angleValues; }

    BlackboardValueGroup<Vector2f>& getVector2fValues() { return m_vector2fValues; }
    const BlackboardValueGroup<Vector2f>& getVector2fValues() const { return m_vector2fValues; }

  private:
    BlackboardValueGroup<float> m_floatValues;
    BlackboardValueGroup<bool> m_boolValues;
    BlackboardValueGroup<Angle> m_angleValues;
    BlackboardValueGroup<Vector2f> m_vector2fValues;
  };
}