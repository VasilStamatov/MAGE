#include "renderer/GLVertexBuffer.h"

#include "renderer/GLCommon.h"

#include <glew.h>

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
    , m_sizeOfBufferDataInBytes(0)
    , m_usage(_usage)
    , m_layout()
{
  GLCall(glGenBuffers(1, &m_handle));
}

// ------------------------------------------------------------------------------

GLVertexBuffer::~GLVertexBuffer() { GLCall(glDeleteBuffers(1, &m_handle)); }

// ------------------------------------------------------------------------------

void GLVertexBuffer::SetBufferLayout(GLBufferLayout _layout)
{
  m_layout = std::move(_layout);
}

// ------------------------------------------------------------------------------

void GLVertexBuffer::SetBufferData(std::uint32_t _sizeInBytes, const void* data)
{
  m_sizeOfBufferDataInBytes = _sizeInBytes;

  GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_handle));
  GLCall(glBufferData(GL_ARRAY_BUFFER, m_sizeOfBufferDataInBytes, data,
                      GetOpenGLBufferUsage(m_usage)));
}

// ------------------------------------------------------------------------------

void GLVertexBuffer::Bind() const
{
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_handle));
  m_layout.Apply();
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