#include "graphics/StaticMeshRenderer.h"

#include "ecs/World.h"
#include "ecs_common/TransformComponent.h"

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

StaticMeshComponent::StaticMeshComponent(const std::string& _meshFile)
    : m_mesh(_meshFile)
{
}

// ------------------------------------------------------------------------------

StaticMeshRenderer::StaticMeshRenderer(GLShader _shader)
    : ecs::RenderingSystem(std::move(_shader))
{
  m_systemSignature.AddComponent<ecs::common::TransformComponent>();
  m_systemSignature.AddComponent<StaticMeshComponent>();
}

// ------------------------------------------------------------------------------

void StaticMeshRenderer::Render(mage::ecs::World& _world, const Camera& _camera,
                                float _deltaTime)
{
  m_shader.Bind();
  m_shader.SetUniformMat4("in_Projection", _camera.GetProjection());
  m_shader.SetUniformMat4("in_View", _camera.GetView());

  for (auto&& entity : m_registeredEntities)
  {
    auto& staticMesh = _world.GetComponent<StaticMeshComponent>(entity);
    auto& transform =
        _world.GetComponent<ecs::common::TransformComponent>(entity);

    m_shader.SetUniformMat4("in_Model", transform.m_transform.ToMatrix());

    staticMesh.m_mesh.Draw();
  }
}

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage