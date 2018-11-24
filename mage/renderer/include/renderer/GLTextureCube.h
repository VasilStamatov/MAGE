#pragma once

#include "GLTexture2D.h"

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

class GLTextureCube
{
public:
  // Pass an array of 6 strings in the following order:
  // X positive, X Negative, Ypos, Yneg, Zpos, Zneg
  GLTextureCube(std::string* _sixSkyboxFiles);
  ~GLTextureCube();

  GLTextureCube(const GLTextureCube& _copy) = delete;
  GLTextureCube(GLTextureCube&& _moved);

  GLTextureCube& operator=(const GLTextureCube& _copy) = delete;
  GLTextureCube& operator=(GLTextureCube&& _moved);

  // ------------------------------------------------------------------------------

  void Bind(std::uint32_t _slot) const;

  // ------------------------------------------------------------------------------

  void Unbind(std::uint32_t _slot) const;

  // ------------------------------------------------------------------------------

  // compares the handle id's
  bool operator==(const GLTextureCube& _other) const;

  // ------------------------------------------------------------------------------

  inline std::uint32_t GetHandle() const { return m_handle; }

private:
  void LoadTexture(std::string* _sixSkyboxFiles);

  // ------------------------------------------------------------------------------

private:
  std::uint32_t m_handle;
};

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage