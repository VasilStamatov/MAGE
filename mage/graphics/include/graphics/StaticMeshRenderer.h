#pragma once

#include "StaticMesh.h"

#include "ecs/RenderingSystem.h"

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

struct StaticMeshComponent : public ecs::Component
{
  StaticMeshComponent(const std::string& _meshFile);

  StaticMesh m_mesh;
};

// ------------------------------------------------------------------------------

class StaticMeshRenderer : public ecs::RenderingSystem
{
public:
  StaticMeshRenderer(GLShader _shader);

  virtual void Render(mage::ecs::World& _world, const Camera& _camera,
                      float _deltaTime) override;
};

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage