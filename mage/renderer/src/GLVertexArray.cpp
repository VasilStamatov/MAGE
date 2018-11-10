#include "renderer/GLVertexArray.h"

#include "renderer/GLCommon.h"

#include <glew.h>

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

GLVertexArray::GLVertexArray() { GLCall(glGenVertexArrays(1, &m_handle)); }

// ------------------------------------------------------------------------------

GLVertexArray::~GLVertexArray() { GLCall(glDeleteVertexArrays(1, &m_handle)); }

// ------------------------------------------------------------------------------

void GLVertexArray::AttachVertexBuffer(const GLVertexBuffer& _buffer) const
{
  Bind();
  _buffer.Bind();
  Unbind();
  _buffer.Unbind();
}

// ------------------------------------------------------------------------------

void GLVertexArray::Bind() const { GLCall(glBindVertexArray(m_handle)); }

// ------------------------------------------------------------------------------

void GLVertexArray::Unbind() const { GLCall(glBindVertexArray(0)); }

// ------------------------------------------------------------------------------

void GLVertexArray::Draw(std::uint32_t _count) const
{
  GLCall(glDrawElements(GL_TRIANGLES, _count, GL_UNSIGNED_INT, nullptr));
}

// ------------------------------------------------------------------------------

} // namespace renderer
} // namespace mage
