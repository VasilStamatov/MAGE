#pragma once

#include "ComponentManager.h"
#include "EntityHandle.h"
#include "EntityManager.h"
#include "GameSystem.h"
#include "RenderingSystem.h"
#include "audio/SoundLibrary.h"
#include "graphics/CopyToTargetPipeline.h"
#include "graphics/OBJModelLibrary.h"
#include "graphics/Texture2DLibrary.h"

#include <array>

namespace mage
{

namespace core
{
class Application;
}

namespace messaging
{
class MessageBus;
}

namespace graphics
{
class RenderDevice;
}

namespace ecs
{

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// The world is the focal point of the application. This is where the entities,
/// components and systems can communicate. This class must be inherited by
/// end-users to describe their own world by overriding the virtual functions
/// which add their systems and entities.
/////////////////////////////////////////////////
class World
{
public:
  World(core::Application& _application);
  virtual ~World();

  // ------------------------------------------------------------------------------

  void Initialize(); ///< Initializes the world by adding the systems and
                     ///< components/entities

  // ------------------------------------------------------------------------------

  void OnEnter(); ///< called whenever the world transitions into this one
  void OnExit();  ///< called whenever the world transitions out of this one

  // ------------------------------------------------------------------------------

  EntityHandle CreateEntity();
  void DestroyEntity(Entity& _entity);

  // ------------------------------------------------------------------------------

  void RefreshEntityState(); ///< refreshes the entitiy state by refreshing the
                             ///< registered entities in all the systems with
                             ///< the modified entities.

  // ------------------------------------------------------------------------------

  void AddGameSystem(std::unique_ptr<GameSystem> _system);
  void TickGameSystems(float _deltaTime);

  // ------------------------------------------------------------------------------

  void AddRenderingSystem(std::unique_ptr<RenderingSystem> _system);
  void TickRenderingSystems(float _deltaTime);

  // ------------------------------------------------------------------------------

  void AddPostProcessPass(
      std::unique_ptr<graphics::PostProcessPipeline> _postProcess);
  void ApplyPostProcesses();

  // ------------------------------------------------------------------------------

  void AddGUISystem(std::unique_ptr<RenderingSystem> _system);
  void TickGUISystems(float _deltaTime);

  // ------------------------------------------------------------------------------

  /////////////////////////////////////////////////
  /// Adds a perspective camera to the world. This doesn't need to be explicitly
  /// called as it's done whenver a camera component is added. This is only
  /// needed if a camera component is not required.
  /////////////////////////////////////////////////
  std::uint32_t AddPerspectiveCamera(const math::Vec4i32& _viewport,
                                     float _fovDegrees, float _near, float _far,
                                     bool _listenForWindowResize);

  /////////////////////////////////////////////////
  /// Adds an orthographic camera to the world. This doesn't need to be
  /// explicitly called as it's done whenver a camera component is added. This
  /// is only needed if a camera component is not required.
  /////////////////////////////////////////////////
  std::uint32_t AddOrthographicCamera(const math::Vec4i32& _viewport,
                                      float _near, float _far,
                                      bool _listenForWindowResize);

  graphics::Camera& GetCamera(std::uint32_t _id); ///< retrieves a camera

  // ------------------------------------------------------------------------------

  template <typename ComponentType, typename... TArgs>
  ComponentType& AddComponent(Entity _entity, TArgs&&... _constructionArgs)
  {
    ComponentManager<ComponentType>* manager =
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

  template <typename ComponentType> void RemoveComponent(Entity _entity)
  {
    ComponentManager<ComponentType>* manager =
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

  template <typename ComponentType> ComponentType* GetComponent(Entity _entity)
  {
    ComponentManager<ComponentType>* manager =
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

  messaging::MessageBus& GetApplicationMessageBus();
  graphics::RenderDevice& GetRenderDevice();
  audio::SoundLibrary& GetSoundLibrary();
  graphics::Texture2DLibrary& GetTexture2DLibrary();
  graphics::OBJModelLibrary& GetOBJModelLibrary();

  // ------------------------------------------------------------------------------

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
  std::vector<Entity> m_entitiesToRemove;
  std::vector<Entity> m_modifiedEntities;
  std::vector<std::unique_ptr<GameSystem>> m_gameSystems;
  std::vector<std::unique_ptr<RenderingSystem>> m_renderingSystems;
  std::vector<std::unique_ptr<graphics::PostProcessPipeline>> m_postProcesses;
  std::vector<std::unique_ptr<RenderingSystem>> m_guiSystems;

  std::vector<graphics::Camera> m_cameras;
  graphics::Camera m_screenCamera;

  graphics::CopyToTargetPipeline m_copyToTargetPass;

  audio::SoundLibrary m_soundLibrary;
  graphics::Texture2DLibrary m_textureLibrary;
  graphics::OBJModelLibrary m_objModelLibrary;
  core::Application& m_application;
};

// ------------------------------------------------------------------------------

} // namespace ecs
} // namespace mage