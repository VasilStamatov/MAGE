#include "renderer/GLBufferLayout.h"

#include "renderer/GLCommon.h"

#include <GLEW/glew.h>

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

BufferElement::BufferElement(std::uint32_t _type, std::uint32_t _size,
                             std::uint32_t _count, std::uint32_t _offset,
                             bool _normalized)
    : m_type(_type)
    , m_size(_size)
    , m_count(_count)
    , m_offset(_offset)
    , m_normalized(_normalized)
{
}

// ------------------------------------------------------------------------------

GLBufferLayout::GLBufferLayout()
    : m_elements()
    , m_currentSizeInBytes(0u)
{
}

// ------------------------------------------------------------------------------

void GLBufferLayout::PushFloat(std::uint32_t _count, bool _normalized)
{
  m_elements.emplace_back(GL_FLOAT, sizeof(float), _count, m_currentSizeInBytes,
                          _normalized);

  m_currentSizeInBytes += sizeof(float) * _count;
}

// ------------------------------------------------------------------------------

void GLBufferLayout::PushUint32(std::uint32_t _count, bool _normalized)
{
  m_elements.emplace_back(GL_UNSIGNED_INT, sizeof(std::uint32_t), _count,
                          m_currentSizeInBytes, _normalized);

  m_currentSizeInBytes += sizeof(std::uint32_t) * _count;
}

// ------------------------------------------------------------------------------

void GLBufferLayout::PushUint8(std::uint32_t _count, bool _normalized)
{
  m_elements.emplace_back(GL_UNSIGNED_BYTE, sizeof(std::uint8_t), _count,
                          m_currentSizeInBytes, _normalized);

  m_currentSizeInBytes += sizeof(std::uint8_t) * _count;
}

// ------------------------------------------------------------------------------

void GLBufferLayout::Apply() const
{
  assert(!m_elements.empty());

  for (auto i = 0; i < m_elements.size(); i++)
  {
    const BufferElement& element = m_elements[i];
    GLCall(glEnableVertexAttribArray(i));
    GLCall(glVertexAttribPointer(
        i, element.m_count, element.m_type, element.m_normalized,
        m_currentSizeInBytes, reinterpret_cast<const void*>(element.m_offset)));
  }
}

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage
