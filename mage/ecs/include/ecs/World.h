#pragma once

#include "ComponentManager.h"
#include "EntityHandle.h"
#include "EntityManager.h"
#include "SystemManager.h"

#include "graphics/ShaderLibrary.h"

#include <array>

namespace mage
{

namespace messaging
{
class MessageBus;
}

namespace ecs
{

// ------------------------------------------------------------------------------

class World
{
public:
  World(messaging::MessageBus& _applicationMessageBus);
  virtual ~World();

  // ------------------------------------------------------------------------------

  void Initialize();

  // ------------------------------------------------------------------------------

  void OnEnter();
  void OnExit();

  // ------------------------------------------------------------------------------

  EntityHandle CreateEntity();
  void DestroyEntity(Entity& _entity);

  // ------------------------------------------------------------------------------

  void AddGameSystem(std::unique_ptr<System> _system);
  void TickGameSystems(float _deltaTime);

  // ------------------------------------------------------------------------------

  void AddRenderingSystem(std::unique_ptr<System> _system);
  void TickRenderingSystems(float _deltaTime);

  // ------------------------------------------------------------------------------
  template <typename ComponentType, typename... TArgs>
  ComponentType& AddComponent(Entity _entity, TArgs&&... _constructionArgs)
  {
    ComponentManager<ComponentType>* manager =
        GetPtrToDerivedComponentManager<ComponentType>();

    ComponentType& componentRef = manager->AddComponent(
        _entity, std::forward<TArgs>(_constructionArgs)...);

    m_entityManager.AddComponent<ComponentType>(_entity);

    m_gameSystems.OnEntityComponentMaskChange(
        _entity, m_entityManager.GetComponentMaskForEntity(_entity));

    m_renderingSystems.OnEntityComponentMaskChange(
        _entity, m_entityManager.GetComponentMaskForEntity(_entity));

    return componentRef;
  }

  // ------------------------------------------------------------------------------

  template <typename ComponentType> void RemoveComponent(Entity _entity)
  {
    ComponentManager<ComponentType>* manager =
        GetPtrToDerivedComponentManager<ComponentType>();

    manager->RemoveComponent(_entity);

    m_entityManager.RemoveComponent<ComponentType>(_entity);

    m_gameSystems.OnEntityComponentMaskChange(
        _entity, m_entityManager.GetComponentMaskForEntity(_entity));

    m_renderingSystems.OnEntityComponentMaskChange(
        _entity, m_entityManager.GetComponentMaskForEntity(_entity));
  }

  // ------------------------------------------------------------------------------

  template <typename ComponentType> ComponentType& GetComponent(Entity _entity)
  {
    ComponentManager<ComponentType>* manager =
        GetPtrToDerivedComponentManager<ComponentType>();
    return manager->GetComponent(_entity);
  }

  // ------------------------------------------------------------------------------

  messaging::MessageBus& GetApplicationMessageBus();

  // ------------------------------------------------------------------------------

private:
  virtual void AddSystems() = 0;
  virtual void AddEntitiesAndComponents() = 0;

  // ------------------------------------------------------------------------------

  template <typename ComponentType>
  ComponentManager<ComponentType>* GetPtrToDerivedComponentManager()
  {
    const std::int32_t componentTypeId = GetComponentTypeId<ComponentType>();
    auto& baseComponentManager = m_componentManagers[componentTypeId];
    if (baseComponentManager == nullptr)
    {
      baseComponentManager =
          std::make_unique<ComponentManager<ComponentType>>();
    }
    return static_cast<ComponentManager<ComponentType>*>(
        baseComponentManager.get());
  }

  // ------------------------------------------------------------------------------

protected:
  std::array<std::unique_ptr<BaseComponentManager>, c_maxNumberOfComponentTypes>
      m_componentManagers;
  EntityManager m_entityManager;
  SystemManager m_gameSystems;
  SystemManager m_renderingSystems;

  graphics::ShaderLibrary m_shaderLib;
  messaging::MessageBus& m_applicationMessageBus;
};

// ------------------------------------------------------------------------------

} // namespace ecs
} // namespace mage