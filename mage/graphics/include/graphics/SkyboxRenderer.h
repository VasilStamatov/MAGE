#pragma once

#include "ecs/RenderingSystem.h"
#include "renderer/GLIndexBuffer.h"
#include "renderer/GLTextureCube.h"
#include "renderer/GLVertexArray.h"

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

struct SkyboxComponent : public ecs::Component
{
  SkyboxComponent(std::string* _sixSkyboxFiles);

  GLTextureCube m_skyboxCube;
};

// ------------------------------------------------------------------------------

class SkyboxRenderer : public ecs::RenderingSystem
{
public:
  SkyboxRenderer(GLShader _shader);

  virtual void Render(mage::ecs::World& _world, const Camera& _camera,
                      float _deltaTime) override;

private:
  GLVertexArray m_cubeVAO;
  GLVertexBuffer m_cubeVBO;
  std::uint32_t m_numCubeVertices;
};

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage