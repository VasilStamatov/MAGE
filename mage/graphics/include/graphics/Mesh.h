#pragma once

#include "renderer/GLIndexBuffer.h"
#include "renderer/GLVertexArray.h"

namespace mage
{
namespace graphics
{

class Mesh
{
public:
  Mesh(const std::string& _filepath);

private:
  void Load(const std::string& _filepath);

private:
  GLVertexArray m_vertexArrayObject;
  GLIndexBuffer m_indexBufferObject;
};

} // namespace graphics
} // namespace mage