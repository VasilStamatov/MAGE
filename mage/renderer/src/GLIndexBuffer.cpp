#include "renderer/GLIndexBuffer.h"

#include "renderer/GLCommon.h"

#include <type_traits>

#include <GLEW/glew.h>

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

GLIndexBuffer::GLIndexBuffer()
    : m_count(0)
{
  GLCall(glGenBuffers(1, &m_handle));
}

// ------------------------------------------------------------------------------

GLIndexBuffer::~GLIndexBuffer()
{
  if (m_handle != 0)
  {
    GLCall(glDeleteBuffers(1, &m_handle));
    m_handle = 0;
  }
}

// ------------------------------------------------------------------------------

GLIndexBuffer::GLIndexBuffer(GLIndexBuffer&& _moved)
    : m_handle(std::move(_moved.m_handle))
    , m_count(std::move(_moved.m_count))
{
  _moved.m_handle = 0;
  _moved.m_count = 0;
}

// ------------------------------------------------------------------------------

GLIndexBuffer& GLIndexBuffer::operator=(GLIndexBuffer&& _moved)
{
  m_handle = std::move(_moved.m_handle);
  m_count = std::move(_moved.m_count);
  _moved.m_handle = 0;
  _moved.m_count = 0;
  return *this;
}

// ------------------------------------------------------------------------------

void GLIndexBuffer::SetData(std::uint32_t* _data, std::uint32_t _count)
{
  m_count = _count;
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle));
  GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(uint32_t),
                      _data, GL_STATIC_DRAW));
}

// ------------------------------------------------------------------------------

void GLIndexBuffer::SetData(std::uint16_t* _data, std::uint32_t _count)
{
  m_count = _count;
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle));
  GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(uint16_t),
                      _data, GL_STATIC_DRAW));
}

// ------------------------------------------------------------------------------

void GLIndexBuffer::Bind() const
{
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle));
}

// ------------------------------------------------------------------------------

void GLIndexBuffer::Unbind() const
{
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

// ------------------------------------------------------------------------------

std::uint32_t GLIndexBuffer::GetCount() const noexcept { return m_count; }

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage