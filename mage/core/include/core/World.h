#pragma once

#include "EntityHandle.h"

#include "audio/AudioWorld.h"
#include "ecs/ComponentManager.h"
#include "ecs/EntityManager.h"
#include "ecs/GameWorld.h"
#include "graphics/RenderWorld.h"
#include "physics/PhysicsWorld.h"

#include <array>

namespace mage
{
namespace core
{

// ------------------------------------------------------------------------------

class Application;

// ------------------------------------------------------------------------------

class World
{
public:
  World(Application& _ownerApplication);
  virtual ~World();

  // ------------------------------------------------------------------------------

  void Initialize(); ///< Initializes the world by adding the systems and
                     ///< components/entities

  // ------------------------------------------------------------------------------

  void OnEnter(); ///< called whenever the world transitions into this one
  void OnExit();  ///< called whenever the world transitions out of this one

  // ------------------------------------------------------------------------------

  EntityHandle CreateEntity();
  void DestroyEntity(ecs::Entity& _entity);

  // ------------------------------------------------------------------------------

  void RefreshEntityState(); ///< refreshes the entitiy state by refreshing the
                             ///< registered entities in all the systems with
                             ///< the modified entities.

  // ------------------------------------------------------------------------------

  void AddGameSystem(std::unique_ptr<ecs::GameSystem> _system);
  void AddAudioSystem(std::unique_ptr<audio::AudioSystem> _system);
  void AddRenderingSystem(std::unique_ptr<graphics::RenderingSystem> _system);
  void AddPostProcessPass(
      std::unique_ptr<graphics::PostProcessPipeline> _postProcess);
  void AddGUISystem(std::unique_ptr<graphics::RenderingSystem> _system);
  void AddPhysicsSystem(std::unique_ptr<physics::PhysicsSystem> _system);

  // ------------------------------------------------------------------------------

  void Update(float _deltaSeconds);
  void Render(float _interpolation);

  // ------------------------------------------------------------------------------

  template <typename ComponentType, typename... TArgs>
  ComponentType& AddComponent(ecs::Entity _entity, TArgs&&... _constructionArgs)
  {
    ecs::ComponentManager<ComponentType>* manager =
        GetPtrToDerivedComponentManager<ComponentType>();

    ComponentType& componentRef = manager->AddComponent(
        _entity, std::forward<TArgs>(_constructionArgs)...);

    m_entityManager.AddComponent<ComponentType>(_entity);

    if (std::find(m_modifiedEntities.begin(), m_modifiedEntities.end(),
                  _entity) == m_modifiedEntities.end())
    {
      m_modifiedEntities.push_back(_entity);
    }

    return componentRef;
  }

  // ------------------------------------------------------------------------------

  template <typename ComponentType> void RemoveComponent(ecs::Entity _entity)
  {
    ecs::ComponentManager<ComponentType>* manager =
        GetPtrToDerivedComponentManager<ComponentType>();

    manager->RemoveComponent(_entity);

    m_entityManager.RemoveComponent<ComponentType>(_entity);

    if (std::find(m_modifiedEntities.begin(), m_modifiedEntities.end(),
                  _entity) == m_modifiedEntities.end())
    {
      m_modifiedEntities.push_back(_entity);
    }
  }

  // ------------------------------------------------------------------------------

  template <typename ComponentType>
  ComponentType* GetComponent(ecs::Entity _entity)
  {
    ecs::ComponentManager<ComponentType>* manager =
        GetPtrToDerivedComponentManager<ComponentType>();
    return manager->GetComponent(_entity);
  }

  // ------------------------------------------------------------------------------

  template <typename ComponentType>
  std::vector<ComponentType>& GetAllComponentsOfType()
  {
    ComponentManager<ComponentType>* manager =
        GetPtrToDerivedComponentManager<ComponentType>();
    return manager->GetAllComponents();
  }

  // ------------------------------------------------------------------------------

  inline Application& GetApplication() { return m_ownerApplication; }
  inline ecs::GameWorld& GetGameWorld() { return m_gameWorld; }
  inline audio::AudioWorld& GetAudioWorld() { return m_audioWorld; }
  inline graphics::RenderWorld& GetRenderWorld() { return m_renderWorld; }
  inline physics::PhysicsWorld& GetPhysicsWorld() { return m_physicsWorld; }

private:
  /////////////////////////////////////////////////
  /// AddSystem is a function to be overriden which must add all the game and
  /// rendering systems.
  /////////////////////////////////////////////////
  virtual void AddSystems() = 0;

  /////////////////////////////////////////////////
  /// AddEntitiesAndComponents is a function to be overriden which must add all
  /// the entities and components.
  /////////////////////////////////////////////////
  virtual void AddEntitiesAndComponents() = 0;

  // ------------------------------------------------------------------------------

  template <typename ComponentType>
  ecs::ComponentManager<ComponentType>* GetPtrToDerivedComponentManager()
  {
    const std::int32_t componentTypeId =
        ecs::GetComponentTypeId<ComponentType>();
    auto& baseComponentManager = m_componentManagers[componentTypeId];
    if (baseComponentManager == nullptr)
    {
      baseComponentManager =
          std::make_unique<ecs::ComponentManager<ComponentType>>();
    }
    return static_cast<ecs::ComponentManager<ComponentType>*>(
        baseComponentManager.get());
  }

  // ------------------------------------------------------------------------------

private:
  Application& m_ownerApplication;

  ecs::GameWorld m_gameWorld;
  audio::AudioWorld m_audioWorld;
  graphics::RenderWorld m_renderWorld;
  physics::PhysicsWorld m_physicsWorld;

  std::array<std::unique_ptr<ecs::BaseComponentManager>,
             ecs::c_maxNumberOfComponentTypes>
      m_componentManagers;
  ecs::EntityManager m_entityManager;
  std::vector<ecs::Entity> m_entitiesToRemove;
  std::vector<ecs::Entity> m_modifiedEntities;
};

} // namespace core
} // namespace mage