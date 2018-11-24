#pragma once

#include "ecs/RenderingSystem.h"
#include "renderer/GLIndexBuffer.h"
#include "renderer/GLVertexArray.h"

#include <unordered_map>
#include <vector>

namespace mage
{
namespace gui
{

// ------------------------------------------------------------------------------

struct ButtonVertex
{
  ButtonVertex(math::Vec2f _position, math::Vec2f _texCoords);

  math::Vec2f m_position;
  math::Vec2f m_texCoords;
};

// ------------------------------------------------------------------------------

struct ButtonBatch
{
  std::vector<ButtonVertex> m_vertices;
  std::vector<std::uint32_t> m_indices;

  std::uint32_t m_indexOffset;
};

// ------------------------------------------------------------------------------

class ButtonRenderer : public ecs::RenderingSystem
{
public:
  ButtonRenderer(graphics::GLShader _shader);

  virtual void Initialize(mage::ecs::World& _world) override;

  virtual void Render(mage::ecs::World& _world, const graphics::Camera& _camera,
                      float _deltaTime) override;

private:
  std::unordered_map<graphics::GLTexture2D*, ButtonBatch> m_batches;
  graphics::GLVertexArray m_VAO;
  graphics::GLVertexBuffer m_VBO;
  graphics::GLIndexBuffer m_IBO;
};

// ------------------------------------------------------------------------------

} // namespace gui
} // namespace mage