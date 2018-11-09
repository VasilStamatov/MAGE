#pragma once

#include "GLVertexBuffer.h"

namespace mage
{
namespace renderer
{

// ------------------------------------------------------------------------------

class GLVertexArray
{
public:
  GLVertexArray();
  ~GLVertexArray();

  // ------------------------------------------------------------------------------

  void AttachVertexBuffer(const GLVertexBuffer& _buffer) const;

  // ------------------------------------------------------------------------------

  void Bind() const;

  // ------------------------------------------------------------------------------

  void Unbind() const;

  // ------------------------------------------------------------------------------

  void Draw(std::uint32_t _count) const;

  // ------------------------------------------------------------------------------

private:
  std::uint32_t m_handle;
};

// ------------------------------------------------------------------------------

} // namespace renderer
} // namespace mage