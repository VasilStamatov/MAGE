#pragma once

#include <cstdint>

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// Index buffer for indexed drawing
/////////////////////////////////////////////////
class GLIndexBuffer
{
public:
  GLIndexBuffer();
  ~GLIndexBuffer();

  GLIndexBuffer(const GLIndexBuffer& _copy) = delete;
  GLIndexBuffer(GLIndexBuffer&& _moved);

  GLIndexBuffer& operator=(const GLIndexBuffer& _copy) = delete;
  GLIndexBuffer& operator=(GLIndexBuffer&& _moved);

  // ------------------------------------------------------------------------------

  void SetData(std::uint32_t* _data, std::uint32_t _count);

  // ------------------------------------------------------------------------------

  void SetData(std::uint16_t* _data, std::uint32_t _count);

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

} // namespace graphics
} // namespace mage
