#pragma once

#include "graphics/RenderingSystem.h"
#include "renderer/GLIndexBuffer.h"
#include "renderer/GLVertexArray.h"

#include <unordered_map>
#include <vector>

namespace mage
{
namespace gui
{

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// Vertex for buttons
/////////////////////////////////////////////////
struct ButtonVertex
{
  ButtonVertex(math::Vec2f _position, math::Vec2f _texCoords);

  math::Vec2f m_position;
  math::Vec2f m_texCoords;
};

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// A batch of buttons to render in one draw call
/////////////////////////////////////////////////
struct ButtonBatch
{
  std::vector<ButtonVertex> m_vertices;
  std::vector<std::uint32_t> m_indices;

  std::uint32_t m_indexOffset;
};

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// Renders all buttons in the world.
/////////////////////////////////////////////////
class ButtonRenderer : public graphics::RenderingSystem
{
public:
  ButtonRenderer(graphics::GLShader _shader,
                 graphics::RenderDevice& _renderDevice);

  virtual void Render(core::World& _world, const graphics::Camera& _camera,
                      float _deltaSeconds) override;

private:
  std::unordered_map<graphics::GLTexture2D*, ButtonBatch> m_batches;
  graphics::GLVertexArray m_VAO;
  graphics::GLVertexBuffer m_VBO;
  graphics::GLIndexBuffer m_IBO;
};

// ------------------------------------------------------------------------------

} // namespace gui
} // namespace mage