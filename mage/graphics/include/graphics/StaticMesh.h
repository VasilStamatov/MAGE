#pragma once

#include "OBJModel.h"

#include "renderer/GLIndexBuffer.h"
#include "renderer/GLVertexArray.h"

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// Static mesh used for static mesh rendering.
/////////////////////////////////////////////////
class StaticMesh
{
public:
  StaticMesh(std::vector<Vertex>& _vertices,
             std::vector<std::uint32_t>& _indices);

  void Draw() const;

private:
  GLVertexArray m_vertexArrayObject;
  GLVertexBuffer m_vertexBuffer;
  GLIndexBuffer m_indexBufferObject;
};

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage