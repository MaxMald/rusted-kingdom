#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include "rkPrerequisites.h"
#include "rkNonCopyable.h"

using sf::FloatRect;
using sf::Vector2f;

namespace rk
{
  template<typename T>
  class QuadTree : public NonCopyable
  {
  public:
    using PositionGetter = std::function<Vector2f(const T&)>;

    QuadTree(const FloatRect& bounds, UInt32 capacity, PositionGetter getPosition);
    ~QuadTree();

    Bool isDivided() const;
    UInt32 getCapacity() const;
    const FloatRect& getBound() const;

    void insert(const T& item);
    void query(const Vector2f& point, Vector<T>& foundItems) const;

  protected:

  private:
    PositionGetter m_getPosition;
    Vector<T> m_items;
    FloatRect m_bound;
    UInt32 m_capacity;
    Bool m_divided;

    SharedPtr<QuadTree<T>> m_topRight;
    SharedPtr<QuadTree<T>> m_topLeft;
    SharedPtr<QuadTree<T>> m_bottomRight;
    SharedPtr<QuadTree<T>> m_bottomLeft;

    void subdivide();
  };

  template<typename T>
  inline QuadTree<T>::QuadTree(
    const FloatRect& bounds,
    UInt32 capacity,
    PositionGetter getPosition
  ) :
    m_getPosition(getPosition),
    m_bound(bounds),
    m_capacity(capacity),
    m_divided(false)
  {
  }

  template<typename T>
  inline QuadTree<T>::~QuadTree()
  {
  }

  template<typename T>
  inline Bool QuadTree<T>::isDivided() const
  {
    return m_divided;
  }

  template<typename T>
  inline UInt32 QuadTree<T>::getCapacity() const
  {
    return m_capacity;
  }

  template<typename T>
  inline const FloatRect& QuadTree<T>::getBound() const
  {
    return m_bound;
  }

  template<typename T>
  inline void QuadTree<T>::insert(const T& item)
  {
    Vector2f itemPosition = m_getPosition(item);

    if (!m_bound.contains(itemPosition))
      return;

    if (m_items.size() < m_capacity && !m_divided)
    {
      m_items.push_back(item);
      return;
    }

    if (!m_divided)
      subdivide();

    if (m_topLeft && m_topLeft->m_bound.contains(itemPosition))
      m_topLeft->insert(item);
    else if (m_topRight && m_topRight->m_bound.contains(itemPosition))
      m_topRight->insert(item);
    else if (m_bottomLeft && m_bottomLeft->m_bound.contains(itemPosition))
      m_bottomLeft->insert(item);
    else if (m_bottomRight && m_bottomRight->m_bound.contains(itemPosition))
      m_bottomRight->insert(item);
    else
      m_items.push_back(item);
  }

  template<typename T>
  inline void QuadTree<T>::query(
    const Vector2f& point,
    Vector<T>& foundItems
  ) const
  {
    if (!m_bound.contains(point))
      return;

    for (const T& item : m_items)
      foundItems.push_back(item);

    if (m_divided)
    {
      if (m_topLeft)
        m_topLeft->query(point, foundItems);
      if (m_topRight)
        m_topRight->query(point, foundItems);
      if (m_bottomLeft)
        m_bottomLeft->query(point, foundItems);
      if (m_bottomRight)
        m_bottomRight->query(point, foundItems);
    }
  }

  template<typename T>
  inline void QuadTree<T>::subdivide()
  {
    float halfWidth = m_bound.size.x * 0.5f;
    float halfHeight = m_bound.size.y * 0.5f;

    FloatRect topLeftRect(
      Vector2f(m_bound.position.x, m_bound.position.y),
      Vector2f(halfWidth, halfHeight)
    );
    m_topLeft = MakeShared<QuadTree<T>>(topLeftRect, m_capacity, m_getPosition);

    FloatRect topRightRect(
      Vector2f(m_bound.position.x + halfWidth, m_bound.position.y),
      Vector2f(halfWidth, halfHeight)
    );
    m_topRight = MakeShared<QuadTree<T>>(topRightRect, m_capacity, m_getPosition);

    FloatRect bottomLeftRect(
      Vector2f(m_bound.position.x, m_bound.position.y + halfHeight),
      Vector2f(halfWidth, halfHeight)
    );
    m_bottomLeft = MakeShared<QuadTree<T>>(bottomLeftRect, m_capacity, m_getPosition);

    FloatRect bottomRightRect(
      Vector2f(m_bound.position.x + halfWidth, m_bound.position.y + halfHeight),
      Vector2f(halfWidth, halfHeight)
    );
    m_bottomRight = MakeShared<QuadTree<T>>(bottomRightRect, m_capacity, m_getPosition);

    m_divided = true;
  }
}