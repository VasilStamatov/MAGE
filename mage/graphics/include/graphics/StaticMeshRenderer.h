#pragma once

#include "Material.h"
#include "StaticMesh.h"

#include "ecs/RenderingSystem.h"

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// Static mesh component which holds the static mesh and material used for
/// rendering.
/////////////////////////////////////////////////
struct StaticMeshComponent : public ecs::Component
{
  StaticMeshComponent(OBJModel& _objMesh,
                      std::shared_ptr<GLTexture2D> _texture);

  StaticMesh m_mesh;
  Material m_material;
};

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// This renders all static meshes in the world.
/////////////////////////////////////////////////
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