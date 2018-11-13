#pragma once

#include "renderer/GLIndexBuffer.h"
#include "renderer/GLVertexArray.h"

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

class StaticMesh
{
public:
  StaticMesh(const std::string& _filepath);

  void Draw() const;

private:
  void Load(const std::string& _filepath);

private:
  GLVertexArray m_vertexArrayObject;
  GLVertexBuffer m_vertexBuffer;
  GLIndexBuffer m_indexBufferObject;
};

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage