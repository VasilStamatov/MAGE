#pragma once

#include "GLBufferLayout.h"

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// Supported buffer usage types
/// http://docs.gl/gl4/glBufferData
/////////////////////////////////////////////////
enum class BufferUsage : std::uint32_t
{
  StaticDraw,
  DynamicDraw
};

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// An opengl vertex buffer
/////////////////////////////////////////////////
class GLVertexBuffer
{
public:
  GLVertexBuffer(BufferUsage _usage);
  ~GLVertexBuffer();

  GLVertexBuffer(const GLVertexBuffer& _copy) = delete;
  GLVertexBuffer(GLVertexBuffer&& _moved);

  GLVertexBuffer& operator=(const GLVertexBuffer& _copy) = delete;
  GLVertexBuffer& operator=(GLVertexBuffer&& _moved);

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
  BufferUsage m_usage;
};

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage
