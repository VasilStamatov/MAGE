#include "gui/ButtonRenderer.h"

#include "core/World.h"
#include "gui/Button.h"
#include "scheduler/Scheduler.h"

namespace mage
{
namespace gui
{

struct ButtonRendererData
{
  ButtonRendererData(
      std::vector<Button>& _buttonComponents,
      std::vector<GUITexture>& _guiTextureComponents,
      std::unordered_map<graphics::GLTexture2D*, ButtonBatch>& _batches)
      : m_buttonComponents(_buttonComponents)
      , m_guiTextureComponents(_guiTextureComponents)
      , m_batches(_batches)
  {
  }

  std::vector<Button>& m_buttonComponents;
  std::vector<GUITexture>& m_guiTextureComponents;
  std::unordered_map<graphics::GLTexture2D*, ButtonBatch>& m_batches;
};

static void ButtonRenderTask(scheduler::Task* _task, const void* _taskData)
{
  const ButtonRendererData* data =
      static_cast<const ButtonRendererData*>(_taskData);

  for (size_t i = 0; i < data->m_buttonComponents.size(); i++)
  {
    Button& button = data->m_buttonComponents[i];
    GUITexture& texture = data->m_guiTextureComponents[i];
    ButtonBatch& batch = data->m_batches[&(*texture.m_texture)];

    float x = button.m_screenPos[0];
    float y = button.m_screenPos[1];
    float width = button.m_size[0];
    float height = button.m_size[1];

    ButtonVertex topLeft(math::Vec2f(x, y + height), math::Vec2f(0.0f, 1.0f));
    ButtonVertex botLeft(math::Vec2f(x, y), math::Vec2f(0.0f, 0.0f));
    ButtonVertex botRight(math::Vec2f(x + width, y), math::Vec2f(1.0f, 0.0f));
    ButtonVertex topRight(math::Vec2f(x + width, y + height),
                          math::Vec2f(1.0f, 1.0f));

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
}

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
  ButtonRendererData data(_world.GetAllComponentsOfType<Button>(),
                          _world.GetAllComponentsOfType<GUITexture>(),
                          m_batches);

  auto* task = scheduler::CreateTask(ButtonRenderTask, &data, sizeof(data));

  scheduler::Run(task);

  // Only this is safe to execute in parallel
  m_shader.Bind();
  m_shader.SetUniformMat4("in_Projection", _camera.GetProjection());

  scheduler::Wait(task);

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