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
    AddGameSystem(std::make_unique<TestSystem>());

    AddRenderingSystem(std::make_unique<mage::graphics::StaticMeshRenderer>());
  }

  virtual void AddEntitiesAndComponents() override
  {
    auto handle = CreateEntity();
    auto& sc = handle.AddComponent<SandboxComponent>(1.0f, 1.0f, 1, 1, 1, 1);

    auto renderedEntity = CreateEntity();
    auto& transform =
        renderedEntity.AddComponent<mage::ecs::common::TransformComponent>();

    transform.m_transform.SetTranslation(mage::math::Vec3f(0.0f, 0.0f, -5.0f));

    auto& staticMeshComp =
        renderedEntity.AddComponent<mage::graphics::StaticMeshComponent>(
            "./res/models/cube.obj",
            m_shaderLib.Get("./res/shaders/StaticMesh.vert",
                            "./res/shaders/StaticMesh.frag"));
  }
};