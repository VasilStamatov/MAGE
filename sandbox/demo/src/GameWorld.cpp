#include "demo/GameWorld.h"

#include "demo/CameraControlSystem.h"

#include <ecs_common/CameraComponent.h>
#include <ecs_common/TransformComponent.h>
#include <graphics/StaticMeshRenderer.h>

GameWorld::GameWorld(mage::messaging::MessageBus& _applicationMessageBus)
    : mage::ecs::World(_applicationMessageBus)
{
}

void GameWorld::AddSystems()
{
  AddGameSystem(std::make_unique<CameraControlSystem>());

  AddRenderingSystem(std::make_unique<mage::graphics::StaticMeshRenderer>(
      mage::graphics::GLShader("./res/shaders/StaticMesh.vert",
                               "./res/shaders/StaticMesh.frag")));
}

void GameWorld::AddEntitiesAndComponents()
{
  auto camera = CreateEntity();
  auto& cameraComp = camera.AddComponent<mage::ecs::common::CameraComponent>(
      *this, mage::math::GenPerspectiveMat(mage::math::ToRadians(70.0f),
                                           16.0f / 9.0f, 0.1f, 100.0f));

  auto& cameraControlComponent = camera.AddComponent<CameraControlComponent>();

  auto renderedEntity = CreateEntity();
  auto& transform =
      renderedEntity.AddComponent<mage::ecs::common::TransformComponent>();

  transform.m_transform.SetTranslation(mage::math::Vec3f(0.0f, 0.0f, -5.0f));

  auto& staticMeshComp =
      renderedEntity.AddComponent<mage::graphics::StaticMeshComponent>(
          "./res/models/cube.obj", "./res/textures/test.png");
}