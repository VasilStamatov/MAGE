#pragma once

#include "Material.h"
#include "RenderingSystem.h"
#include "StaticMesh.h"

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
class StaticMeshRenderer : public RenderingSystem
{
public:
  StaticMeshRenderer(GLShader _shader, RenderDevice& _renderDevice);

  virtual void Render(core::World& _world, const Camera& _camera,
                      float _deltaSeconds) override;
};

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage