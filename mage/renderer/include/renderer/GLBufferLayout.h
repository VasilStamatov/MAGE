#pragma once

#include <cstdint>
#include <vector>

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// Buffer element used to describe the element in a vbo buffer layout
/////////////////////////////////////////////////
struct BufferElement
{
  BufferElement(std::uint32_t _type, std::uint32_t _size, std::uint32_t _count,
                std::uint32_t _offset, bool _normalized);

  std::uint32_t m_type;
  std::uint32_t m_size;
  std::uint32_t m_count;
  std::uint32_t m_offset;
  bool m_normalized;
};

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// Buffer layout describes the buffer layout for the attributes of a vbo
/////////////////////////////////////////////////
class GLBufferLayout
{
public:
  GLBufferLayout();

  // ------------------------------------------------------------------------------

  void PushFloat(std::uint32_t _count, bool _normalized);
  void PushUint32(std::uint32_t _count, bool _normalized);
  void PushUint8(std::uint32_t _count, bool _normalized);

  // ------------------------------------------------------------------------------

  void Apply() const;

  // ------------------------------------------------------------------------------

private:
  std::vector<BufferElement> m_elements;
  std::uint32_t m_currentSizeInBytes;
};

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage
