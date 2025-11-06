#include "rkLayerGameObject.h"

#include <SFML/Graphics/RenderStates.hpp>

namespace rk
{
  LayerGameObject::LayerGameObject(const char* name) :
    GameObject(name)
  {
  }

  LayerGameObject::~LayerGameObject()
  {
  }

  void LayerGameObject::onUpdate(float deltaTime)
  {
    sortChildrenByYPosition();
  }

  void LayerGameObject::sortChildrenByYPosition()
  {
    std::stable_sort(
      m_children.begin(), m_children.end(),
      [](const UniquePtr<GameObject>& aPtr, const UniquePtr<GameObject>& bPtr) -> bool
      {
        const GameObject* a = aPtr.get();
        const GameObject* b = bPtr.get();
        
        if (!a || !b) 
          return a < b;

        const sf::Vector2f aWorld = a->getWorldTransform().transformPoint(sf::Vector2f(0.f, 0.f));
        const sf::Vector2f bWorld = b->getWorldTransform().transformPoint(sf::Vector2f(0.f, 0.f));

        if (aWorld.y != bWorld.y) 
          return aWorld.y < bWorld.y;

        if (aWorld.x != bWorld.x) 
          return aWorld.x < bWorld.x;

        return a < b;
      });
  }
}