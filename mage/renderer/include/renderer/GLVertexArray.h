#pragma once

#include "GLVertexBuffer.h"

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

class GLVertexArray
{
public:
  GLVertexArray();
  ~GLVertexArray();

  GLVertexArray(const GLVertexArray& _copy) = delete;
  GLVertexArray(GLVertexArray&& _moved);

  GLVertexArray& operator=(const GLVertexArray& _copy) = delete;
  GLVertexArray& operator=(GLVertexArray&& _moved);

  // ------------------------------------------------------------------------------

  void AttachVertexBuffer(const GLVertexBuffer& _buffer,
                          const GLBufferLayout& _layout) const;

  // ------------------------------------------------------------------------------

  void Bind() const;

  // ------------------------------------------------------------------------------

  void Unbind() const;

  // ------------------------------------------------------------------------------

  void DrawElements(std::uint32_t _indexCount) const;

  // ------------------------------------------------------------------------------

  void DrawArrays(std::uint32_t _vertexCount, std::uint32_t _offset = 0) const;

private:
  std::uint32_t m_handle;
};

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage
