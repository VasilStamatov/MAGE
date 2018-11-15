#pragma once

#include "Material.h"
#include "StaticMesh.h"

#include "ecs/RenderingSystem.h"

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

struct StaticMeshComponent : public ecs::Component
{
  StaticMeshComponent(const std::string& _meshFile,
                      const std::string& _materialFile);

  StaticMesh m_mesh;
  Material m_material;
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