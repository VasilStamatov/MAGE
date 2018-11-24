#include "graphics/StaticMesh.h"

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

StaticMesh::StaticMesh(std::vector<Vertex>& _vertices,
                       std::vector<std::uint32_t>& _indices)
    : m_vertexArrayObject()
    , m_vertexBuffer(BufferUsage::StaticDraw)
    , m_indexBufferObject()
{
  m_vertexBuffer.SetBufferData(sizeof(Vertex) * _vertices.size(),
                               _vertices.data());

  // setup the vao data layout (must be equal to the shader attribute layout)
  GLBufferLayout bufferLayout;
  bufferLayout.PushFloat(3, false); // first 3 floats (m_position)
  bufferLayout.PushFloat(3, false); // last 3 floats (m_normals)
  bufferLayout.PushFloat(2, false); // next 2 floats (m_texCoords)

  m_vertexArrayObject.AttachVertexBuffer(m_vertexBuffer, bufferLayout);

  m_indexBufferObject.SetData(_indices.data(), _indices.size());
}

// ------------------------------------------------------------------------------

void StaticMesh::Draw() const
{
  m_vertexArrayObject.Bind();
  m_indexBufferObject.Bind();
  m_vertexArrayObject.DrawElements(m_indexBufferObject.GetCount());
  m_indexBufferObject.Unbind();
  m_vertexArrayObject.Unbind();
}

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage