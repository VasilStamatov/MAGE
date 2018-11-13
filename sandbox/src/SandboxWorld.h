#pragma once

#include "SandboxSystems.h"

#include <graphics/StaticMeshRenderer.h>
#include <messaging/MessageBus.h>

class SandboxWorld : public mage::ecs::World
{
public:
  SandboxWorld(mage::messaging::MessageBus& _applicationMessageBus)
      : mage::ecs::World(_applicationMessageBus)
  {
  }

private:
  virtual void AddSystems() override
  {
    AddGameSystem(std::make_unique<CameraController>());

    AddRenderingSystem(std::make_unique<mage::graphics::StaticMeshRenderer>(
        mage::graphics::GLShader("./res/shaders/StaticMesh.vert",
                                 "./res/shaders/StaticMesh.frag")));
  }

  virtual void AddEntitiesAndComponents() override
  {
    auto camera = CreateEntity();
    auto& cameraComp = camera.AddComponent<mage::ecs::common::CameraComponent>(
        *this, mage::math::GenPerspectiveMat(mage::math::ToRadians(70.0f),
                                             16.0f / 9.0f, 0.1f, 100.0f));

    auto& cameraControlComponent =
        camera.AddComponent<CameraControlComponent>();

    auto renderedEntity = CreateEntity();
    auto& transform =
        renderedEntity.AddComponent<mage::ecs::common::TransformComponent>();

    transform.m_transform.SetTranslation(mage::math::Vec3f(0.0f, 0.0f, -5.0f));

    auto& staticMeshComp =
        renderedEntity.AddComponent<mage::graphics::StaticMeshComponent>(
            "./res/models/cube.obj");
  }
};