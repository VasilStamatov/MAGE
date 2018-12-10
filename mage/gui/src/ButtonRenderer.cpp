#include "gui/ButtonRenderer.h"

#include "core/World.h"
#include "gui/Button.h"

namespace mage
{
namespace gui
{

// ------------------------------------------------------------------------------

ButtonVertex::ButtonVertex(math::Vec2f _position, math::Vec2f _texCoords)
    : m_position(_position)
    , m_texCoords(_texCoords)
{
}

// ------------------------------------------------------------------------------

ButtonRenderer::ButtonRenderer(graphics::GLShader _shader,
                               graphics::RenderDevice& _renderDevice)
    : graphics::RenderingSystem(std::move(_shader), _renderDevice)
    , m_batches()
    , m_VAO()
    , m_VBO(graphics::BufferUsage::DynamicDraw)
    , m_IBO()
{
  m_systemSignature.AddComponent<Button>();
  m_systemSignature.AddComponent<GUITexture>();

  graphics::GLBufferLayout bufferLayout;
  bufferLayout.PushFloat(2, false); // first 2 floats (m_position x,y)
  bufferLayout.PushFloat(2, false); // next 2 floats (m_texCoords x,y)

  m_VAO.AttachVertexBuffer(m_VBO, bufferLayout);
}

// ------------------------------------------------------------------------------

void ButtonRenderer::Render(core::World& _world,
                            const graphics::Camera& _camera,
                            float _deltaSeconds)
{
  m_shader.Bind();
  m_shader.SetUniformMat4("in_Projection", _camera.GetProjection());

  for (auto&& entity : m_registeredEntities)
  {
    auto* button = _world.GetComponent<Button>(entity);
    auto* texture = _world.GetComponent<GUITexture>(entity);

    float x = button->m_screenPos[0];
    float y = button->m_screenPos[1];
    float width = button->m_size[0];
    float height = button->m_size[1];

    ButtonVertex topLeft(math::Vec2f(x, y + height), math::Vec2f(0.0f, 1.0f));
    ButtonVertex botLeft(math::Vec2f(x, y), math::Vec2f(0.0f, 0.0f));
    ButtonVertex botRight(math::Vec2f(x + width, y), math::Vec2f(1.0f, 0.0f));
    ButtonVertex topRight(math::Vec2f(x + width, y + height),
                          math::Vec2f(1.0f, 1.0f));

    // temporarily store the raw pointer in the map (cleared once rendering is
    // finished)
    ButtonBatch& batch = m_batches[&(*texture->m_texture)];

    batch.m_vertices.push_back(topLeft);
    batch.m_vertices.push_back(botLeft);
    batch.m_vertices.push_back(botRight);
    batch.m_vertices.push_back(topRight);

    batch.m_indices.push_back(batch.m_indexOffset + 0);
    batch.m_indices.push_back(batch.m_indexOffset + 1);
    batch.m_indices.push_back(batch.m_indexOffset + 2);
    batch.m_indices.push_back(batch.m_indexOffset + 2);
    batch.m_indices.push_back(batch.m_indexOffset + 3);
    batch.m_indices.push_back(batch.m_indexOffset + 0);

    batch.m_indexOffset += 4;
  }

  for (auto&& batch : m_batches)
  {
    m_VBO.SetBufferData(sizeof(ButtonVertex) * batch.second.m_vertices.size(),
                        batch.second.m_vertices.data());

    m_IBO.SetData(batch.second.m_indices.data(), batch.second.m_indices.size());

    batch.first->Bind(0);

    m_VAO.Bind();
    m_IBO.Bind();
    m_VAO.DrawElements(m_IBO.GetCount());
    m_IBO.Unbind();
    m_VAO.Unbind();

    batch.first->Unbind(0);
  }

  m_batches.clear();
}

// ------------------------------------------------------------------------------

} // namespace gui
} // namespace mage