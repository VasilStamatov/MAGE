#pragma once

#include "renderer/GLTexture2D.h"

#include <array>
#include <string>

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

class Material
{
public:
  Material(const std::string& _imageFile);

  void Bind();
  void Unbind();

private:
  GLTexture2D m_texture;
};

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage