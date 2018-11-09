#pragma once

#include <cstdint>
#include <vector>

namespace mage
{
namespace renderer
{

// ------------------------------------------------------------------------------

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

} // namespace renderer
} // namespace mage
