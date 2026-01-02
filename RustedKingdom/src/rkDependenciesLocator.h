#pragma once

#include "rkPrerequisites.h"

namespace rk
{
  template<typename _BaseType>
  class DependenciesLocator
  {
  public:
    template<typename T>
    void registerDependency(SharedPtr<T> service)
    {
      static_assert(
        IsBaseOf<_BaseType, T>::value,
        "Dependency must derive from base type."
      );

      m_dependencies[typeid(T)] = service;
    }

    
    template<typename T>
    SharedPtr<T> get()
    {
      static_assert(
        IsBaseOf<_BaseType, T>::value,
        "Dependency must derive from base type."
      );

      auto it = m_dependencies.find(typeid(T));
      if (it != m_dependencies.end()) {
        return std::static_pointer_cast<T>(it->second);
      }

      throw RuntimeErrorException(
        String::Format("Dependency of type {} not found", typeid(T).name())
      );
    }

    void clear()
    {
      m_dependencies.clear();
    }

  private:
    UnorderedMap<std::type_index, SharedPtr<_BaseType>> m_dependencies;
  };

  class IComponentFactory;

  using ComponentFactoryLocator = DependenciesLocator<IComponentFactory>;
}