#pragma once

#include "ShaderLibrary.h"
#include "StaticMesh.h"

#include "ecs/System.h"
#include "ecs/World.h"
#include "ecs_common/TransformComponent.h"
#include "math/Mat.h"

#include <iostream>

namespace mage
{
namespace graphics
{

static math::Mat4f c_projection =
    math::GenPerspectiveMat(math::ToRadians(70.0f), 16.0f / 9.0f, 0.1f, 100.0f);

static math::Mat4f c_view(1.0f);

struct StaticMeshComponent : public ecs::Component
{
  StaticMeshComponent(const std::string& _meshFile,
                      std::shared_ptr<GLShader> _shader)
      : m_mesh(_meshFile)
      , m_shader(_shader)
  {
  }
  StaticMesh m_mesh;
  std::shared_ptr<GLShader> m_shader;
};

class StaticMeshRenderer : public ecs::System
{
public:
  StaticMeshRenderer()
  {
    m_systemSignature.AddComponent<ecs::common::TransformComponent>();
    m_systemSignature.AddComponent<StaticMeshComponent>();
  }

  void Initialize(mage::ecs::World& _world) {}

  void Tick(mage::ecs::World& _world, float _deltaTime) override
  {
    for (auto&& entity : m_registeredEntities)
    {
      auto& staticMesh = _world.GetComponent<StaticMeshComponent>(entity);
      auto& transform =
          _world.GetComponent<ecs::common::TransformComponent>(entity);

      staticMesh.m_shader->Bind();
      staticMesh.m_shader->SetUniformMat4("in_Projection", c_projection);
      staticMesh.m_shader->SetUniformMat4("in_View", c_view);
      staticMesh.m_shader->SetUniformMat4("in_Model",
                                          transform.m_transform.ToMatrix());

      staticMesh.m_mesh.Draw();
    }
  }
};

} // namespace graphics
} // namespace mage