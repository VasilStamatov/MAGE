#include "renderer/GLVertexBuffer.h"

#include "renderer/GLCommon.h"

#include <GLEW/glew.h>

namespace mage
{
namespace graphics
{

namespace
{

// ------------------------------------------------------------------------------

std::uint32_t GetOpenGLBufferUsage(BufferUsage _usage)
{
  switch (_usage)
  {
    case BufferUsage::StaticDraw:
      return GL_STATIC_DRAW;
    case BufferUsage::DynamicDraw:
      return GL_DYNAMIC_DRAW;
  }
  return 0;
}

// ------------------------------------------------------------------------------

} // namespace

// ------------------------------------------------------------------------------

GLVertexBuffer::GLVertexBuffer(BufferUsage _usage)
    : m_handle(0)
    , m_usage(_usage)
{
  GLCall(glGenBuffers(1, &m_handle));
}

// ------------------------------------------------------------------------------

GLVertexBuffer::~GLVertexBuffer()
{
  if (m_handle != 0)
  {
    GLCall(glDeleteBuffers(1, &m_handle));
    m_handle = 0;
  }
}

// ------------------------------------------------------------------------------

GLVertexBuffer::GLVertexBuffer(GLVertexBuffer&& _moved)
    : m_handle(std::move(_moved.m_handle))
    , m_usage(std::move(_moved.m_usage))
{
  _moved.m_handle = 0;
}

// ------------------------------------------------------------------------------

GLVertexBuffer& GLVertexBuffer::operator=(GLVertexBuffer&& _moved)
{
  m_handle = std::move(_moved.m_handle);
  _moved.m_handle = 0;
  return *this;
}

// ------------------------------------------------------------------------------

void GLVertexBuffer::SetBufferData(std::uint32_t _sizeInBytes, const void* data)
{
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_handle));
  GLCall(glBufferData(GL_ARRAY_BUFFER, _sizeInBytes, data,
                      GetOpenGLBufferUsage(m_usage)));
}

// ------------------------------------------------------------------------------

void GLVertexBuffer::Bind() const
{
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_handle));
}

// ------------------------------------------------------------------------------

void GLVertexBuffer::Unbind() const
{
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

// ------------------------------------------------------------------------------

void* GLVertexBuffer::GetPointerToBufferData() const
{
  GLCall(void* result = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
  return result;
}

// ------------------------------------------------------------------------------

void GLVertexBuffer::ReleasePointerToBufferData() const
{
  GLCall(glUnmapBuffer(GL_ARRAY_BUFFER));
}

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage