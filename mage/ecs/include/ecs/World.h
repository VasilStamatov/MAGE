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
public:
  World();
  virtual ~World();

  void Initialize();

  void OnEnter();
  void OnExit();

  EntityHandle CreateEntity();
  void DestroyEntity(Entity& _entity);

  void AddSystem(std::unique_ptr<System> _system);
  void TickSystems(float _deltaTime);

  template <typename ComponentType, typename... TArgs>
  void AddComponent(Entity _entity, TArgs&&... _constructionArgs)
  {
    ComponentManager<ComponentType>* manager =
        GetPtrToDerivedComponentManager<ComponentType>();

    manager->AddComponent(_entity, std::forward<TArgs>(_constructionArgs)...);

    m_entityManager.AddComponent<ComponentType>(_entity);
    m_systemManager.OnEntityComponentMaskChange(
        _entity, m_entityManager.GetComponentMaskForEntity(_entity));
  }

  template <typename ComponentType> void RemoveComponent(Entity _entity)
  {
    ComponentManager<ComponentType>* manager =
        GetPtrToDerivedComponentManager<ComponentType>();

    manager->RemoveComponent(_entity);

    m_entityManager.RemoveComponent<ComponentType>(_entity);
    m_systemManager.OnEntityComponentMaskChange(
        _entity, m_entityManager.GetComponentMaskForEntity(_entity));
  }

  template <typename ComponentType> ComponentType& GetComponent(Entity _entity)
  {
    ComponentManager<ComponentType>* manager =
        GetPtrToDerivedComponentManager<ComponentType>();
    return manager->GetComponent(_entity);
  }

private:
  virtual void AddSystems() = 0;
  virtual void AddEntitiesAndComponents() = 0;

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

private:
  std::array<std::unique_ptr<BaseComponentManager>, c_maxNumberOfComponentTypes>
      m_componentManagers;
  EntityManager m_entityManager;
  SystemManager m_systemManager;
};

} // namespace ecs
} // namespace mage