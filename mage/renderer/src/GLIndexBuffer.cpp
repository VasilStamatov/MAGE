#include "renderer/GLIndexBuffer.h"

#include "renderer/GLCommon.h"

#include <glew.h>

namespace mage
{
namespace graphics
{

GLIndexBuffer::GLIndexBuffer()
    : m_count(0)
{
  GLCall(glGenBuffers(1, &m_handle));
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

GLIndexBuffer::~GLIndexBuffer() { GLCall(glDeleteBuffers(1, &m_handle)); }

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