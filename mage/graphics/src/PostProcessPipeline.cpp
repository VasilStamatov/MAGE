#include "graphics/PostProcessPipeline.h"

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

struct PostProcessShaderAttrib
{
  PostProcessShaderAttrib(math::Vec2f _position, math::Vec2f _texCoord)
      : m_position(std::move(_position))
      , m_texCoord(std::move(_texCoord))
  {
  }

  math::Vec2f m_position;
  math::Vec2f m_texCoord;
};

// ------------------------------------------------------------------------------

PostProcessPipeline::PostProcessPipeline()
    : m_screenVAO()
    , m_screenVBO(BufferUsage::StaticDraw)
    , m_screenIBO()
{
  std::vector<PostProcessShaderAttrib> screenVerts;
  // reserve space for the 4 screen points
  screenVerts.reserve(4);

  // top left
  screenVerts.emplace_back(math::Vec2f(-1.0f, 1.0f), math::Vec2f(0.0f, 1.0f));
  // bottom left
  screenVerts.emplace_back(math::Vec2f(-1.0f, -1.0f), math::Vec2f(0.0f, 0.0f));
  // bottom right
  screenVerts.emplace_back(math::Vec2f(1.0f, -1.0f), math::Vec2f(1.0f, 0.0f));
  // top right
  screenVerts.emplace_back(math::Vec2f(1.0f, 1.0f), math::Vec2f(1.0f, 1.0f));

  // quad indices for indexed drawing
  std::vector<std::uint32_t> indices = {0, 1, 2, 2, 3, 0};

  m_screenVBO.SetBufferData(
      sizeof(PostProcessShaderAttrib) * screenVerts.size(), screenVerts.data());

  // setup the vao data layout (must be equal to the shader attribute layout)
  GLBufferLayout bufferLayout;
  bufferLayout.PushFloat(2, false); // first 2 floats (m_position x,y)
  bufferLayout.PushFloat(2, false); // next 2 floats (m_texCoords x,y)

  m_screenVAO.AttachVertexBuffer(m_screenVBO, bufferLayout);

  m_screenIBO.SetData(indices.data(), indices.size());
}

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage