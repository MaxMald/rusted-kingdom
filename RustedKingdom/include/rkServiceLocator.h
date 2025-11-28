#pragma once

#include "rkIService.h"

namespace rk
{
  /**
   * @brief ServiceLocator provides registry for managing IService-derived
   * services.
   *
   * This class allows registration, retrieval, and removal of services by type.
   * All services must inherit from rk::IService. Services are stored using
   * type-safe keys.
   */
  class ServiceLocator : public NonCopyable
  {
  public:
    static ServiceLocator& Instance()
    {
      if (_Instance == nullptr)
      {
        throw RuntimeErrorException(
          "ServiceLocator is not prepared. Call Prepare() before using."
        );
      }

      return *_Instance;
    }

    /**
     * @brief Registers a service instance of type T.
     *
     * @tparam T Service type, must derive from IService.
     * @param service Shared pointer to the service instance.
     */
    template<typename T>
    void registerService(SharedPtr<T> service)
    {
      static_assert(
        IsBaseOf<IService, T>::value,
        "Service must derive from IService"
        );

      m_services[typeid(T)] = service;
    }

    /**
     * @brief Retrieves a registered service instance of type T.
     *
     * @tparam T Service type, must derive from IService.
     *
     * @return Shared pointer to the requested service.
     * @throws RuntimeErrorException if the service is not found.
     */
    template<typename T>
    SharedPtr<T> getService()
    {
      static_assert(
        IsBaseOf<IService, T>::value,
        "Service must derive from rkIService"
        );

      auto it = m_services.find(typeid(T));
      if (it != m_services.end()) {
        return std::static_pointer_cast<T>(it->second);
      }

      throw RuntimeErrorException(
        String::Format("Service of type {} not found", typeid(T).name())
      );
    }

    /**
     * @brief Unregisters a service instance of type T.
     *
     * @tparam T Service type, must derive from IService.
     */
    template<typename T>
    void unregisterService() {
      static_assert(
        IsBaseOf<IService, T>::value,
        "Service must derive from rkIService"
        );
      m_services.erase(typeid(T));
    }

  private:
    static ServiceLocator* _Instance;

    UnorderedMap<TypeIndex, SharedPtr<IService>> m_services;

    ServiceLocator() = default;
    ~ServiceLocator() = default;

    static void Prepare()
    {
      if (!_Instance)
        _Instance = new ServiceLocator();
    }

    static void Shutdown()
    {
      if (_Instance)
      {
        _Instance->destroy();

        delete _Instance;
        _Instance = nullptr;
      }
    }

    /**
     * @brief Initializes all registered services.
     */
    void initializeServices()
    {
      for (auto& [type, service] : m_services)
        service->init(*this);
    }

    /**
     * @brief Destroys all registered services and clears the registry.
     */
    void destroy()
    {
      for (auto& [type, service] : m_services)
        service->destroy();
      m_services.clear();
    }

    friend class Application;
  };
}