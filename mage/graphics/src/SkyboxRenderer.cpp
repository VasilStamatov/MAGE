#include "graphics/SkyboxRenderer.h"

#include "core/World.h"
#include "renderer/RenderDevice.h"

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

struct SkyboxVertex
{
  SkyboxVertex(math::Vec3f _position)
      : m_position(std::move(_position))
  {
  }
  math::Vec3f m_position;
};

// ------------------------------------------------------------------------------

SkyboxComponent::SkyboxComponent(std::string* _sixSkyboxFiles)
    : m_skyboxCube(_sixSkyboxFiles)
{
}

// ------------------------------------------------------------------------------

SkyboxRenderer::SkyboxRenderer(GLShader _shader, RenderDevice& _renderDevice)
    : RenderingSystem(std::move(_shader), _renderDevice)
    , m_cubeVAO()
    , m_cubeVBO(BufferUsage::StaticDraw)
    , m_numCubeVertices(36)
{
  m_systemSignature.AddComponent<SkyboxComponent>();

  float skyboxVertices[108] = {
      // positions
      -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f,
      1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f,

      -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f,
      -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,

      1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,
      1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f,

      -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,
      1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,

      -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,
      1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f,

      -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f,
      1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f};

  m_cubeVBO.SetBufferData(sizeof(skyboxVertices), skyboxVertices);

  // setup the vao data layout (must be equal to the shader attribute layout)
  GLBufferLayout bufferLayout;
  bufferLayout.PushFloat(3, false); // (m_position x,y,z)

  m_cubeVAO.AttachVertexBuffer(m_cubeVBO, bufferLayout);
}

// ------------------------------------------------------------------------------

void SkyboxRenderer::Render(core::World& _world, const Camera& _camera,
                            float _deltaSeconds)
{
  math::Mat4f view = _camera.GetView();
  // remove translation
  view[3] = 0.0f;
  view[7] = 0.0f;
  view[11] = 0.0f;

  m_renderDevice.SetDepthFunc(graphics::DepthFunc::LessOrEqual);

  m_shader.Bind();
  m_shader.SetUniformMat4("in_Projection", _camera.GetProjection());
  m_shader.SetUniformMat4("in_View", view);

  for (auto&& entity : m_registeredEntities)
  {
    auto* skybox = _world.GetComponent<SkyboxComponent>(entity);

    skybox->m_skyboxCube.Bind(0);

    m_cubeVAO.Bind();
    m_cubeVAO.DrawArrays(m_numCubeVertices);
    m_cubeVAO.Unbind();

    skybox->m_skyboxCube.Unbind(0);
  }

  m_renderDevice.SetDepthFunc(graphics::DepthFunc::Less);
}

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage