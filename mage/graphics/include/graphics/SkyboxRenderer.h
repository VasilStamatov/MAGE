#pragma once

#include "RenderingSystem.h"

#include "renderer/GLIndexBuffer.h"
#include "renderer/GLTextureCube.h"
#include "renderer/GLVertexArray.h"

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// Skybox component which holds the cube texture of the skybox
/////////////////////////////////////////////////
struct SkyboxComponent : public ecs::Component
{
  SkyboxComponent(std::string* _sixSkyboxFiles);

  GLTextureCube m_skyboxCube;
};

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// The rendering system which renders the skybox cube
/////////////////////////////////////////////////
class SkyboxRenderer : public RenderingSystem
{
public:
  SkyboxRenderer(GLShader _shader, RenderDevice& _renderDevice);

  virtual void Render(core::World& _world, const Camera& _camera,
                      float _deltaSeconds) override;

private:
  GLVertexArray m_cubeVAO;
  GLVertexBuffer m_cubeVBO;
  std::uint32_t m_numCubeVertices;
};

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage