#pragma once

#include <cstdint>

namespace mage
{
namespace renderer
{

// ------------------------------------------------------------------------------

class GLIndexBuffer
{
public:
  GLIndexBuffer(std::uint32_t* _data, std::uint32_t _count);
  GLIndexBuffer(std::uint16_t* _data, std::uint32_t _count);
  ~GLIndexBuffer();

  // ------------------------------------------------------------------------------

  void Bind() const;

  // ------------------------------------------------------------------------------

  void Unbind() const;

  // ------------------------------------------------------------------------------

  std::uint32_t GetCount() const noexcept;

  // ------------------------------------------------------------------------------

private:
  std::uint32_t m_handle;
  std::uint32_t m_count;
};

// ------------------------------------------------------------------------------

} // namespace renderer
} // namespace mage
