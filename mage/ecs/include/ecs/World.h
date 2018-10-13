#pragma once

#include "ComponentManager.h"
#include "EntityHandle.h"
#include "EntityManager.h"
#include "SystemManager.h"

#include <array>

namespace mage
{
namespace ecs
{

class World
{
private:
  std::array<std::unique_ptr<BaseComponentManager>, 32> m_componentManagers;
  EntityManager m_entityManager;
  SystemManager m_systemManager;

  template <typename ComponentType>
  ComponentManager<ComponentType> *GetPtrToDerivedComponentManager()
  {
    const std::uint32_t componentTypeId = GetComponentTypeId<ComponentType>();
    auto &baseComponentManager = m_componentManagers[componentTypeId];
    if (baseComponentManager == nullptr)
    {
      baseComponentManager = std::make_unique<ComponentManager<ComponentType>>();
    }
    return static_cast<ComponentManager<ComponentType> *>(baseComponentManager.get());
  }

public:
  void OnEnter();
  void OnExit();

  EntityHandle CreateEntity();
  void DestroyEntity(Entity _entity);

  void AddSystem(std::unique_ptr<System> _system);
  void TickSystems(float _deltaTime);

  template <typename ComponentType>
  void AddComponent(Entity _entity, const ComponentType &_component)
  {
    ComponentManager<ComponentType> *manager = GetPtrToDerivedComponentManager<ComponentType>();
    manager->AddComponent<ComponentType>(_entity, _component);

    const std::uint32_t componentTypeId = GetComponentTypeId<ComponentType>();
    m_entityManager.SetComponentBit(_entity, componentTypeId);
    m_systemManager.OnEntityComponentMaskChange(_entity, m_entityManager.GetComponentMaskForEntity(_entity));
  }

  template <typename ComponentType>
  void RemoveComponent(Entity _entity)
  {
    ComponentManager<ComponentType> *manager = GetPtrToDerivedComponentManager<ComponentType>();
    manager->RemoveComponent<ComponentType>(_entity);

    const std::uint32_t componentTypeId = GetComponentTypeId<ComponentType>();
    m_entityManager.UnsetComponentBit(_entity, componentTypeId);
    m_systemManager.OnEntityComponentMaskChange(_entity, m_entityManager.GetComponentMaskForEntity(_entity));
  }
};

} // namespace ecs
} // namespace mage