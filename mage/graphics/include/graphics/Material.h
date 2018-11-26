#pragma once

#include "renderer/GLTexture2D.h"

#include <memory>

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// Material is just an interface to a single texture.
/////////////////////////////////////////////////
class Material
{
public:
  Material(std::shared_ptr<GLTexture2D> _texture);

  void Bind();
  void Unbind();

private:
  std::shared_ptr<GLTexture2D> m_texture;
};

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage