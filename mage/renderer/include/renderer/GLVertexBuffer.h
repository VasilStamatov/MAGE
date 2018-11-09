#pragma once

#include "GLBufferLayout.h"

namespace mage
{
namespace renderer
{

// http://docs.gl/gl4/glBufferData
enum class BufferUsage : std::uint32_t
{
  StaticDraw,
  DynamicDraw
};

// ------------------------------------------------------------------------------

class GLVertexBuffer
{
public:
  GLVertexBuffer(BufferUsage _usage);
  ~GLVertexBuffer();

  // ------------------------------------------------------------------------------

  void SetBufferLayout(GLBufferLayout _layout);

  // ------------------------------------------------------------------------------

  void SetBufferData(std::uint32_t _sizeInBytes, const void* data);

  // ------------------------------------------------------------------------------

  void Bind() const;

  // ------------------------------------------------------------------------------

  void Unbind() const;

  // ------------------------------------------------------------------------------

  void* GetPointerToBufferData() const;

  // ------------------------------------------------------------------------------

  void ReleasePointerToBufferData() const;

  // ------------------------------------------------------------------------------

private:
  std::uint32_t m_handle;
  std::uint32_t m_sizeOfBufferDataInBytes;
  BufferUsage m_usage;
  GLBufferLayout m_layout;
};

// ------------------------------------------------------------------------------

} // namespace renderer
} // namespace mage
