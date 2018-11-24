#include "graphics/Material.h"

#include <assert.h>

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

Material::Material(std::shared_ptr<GLTexture2D> _texture)
    : m_texture(_texture)
{
}

// ------------------------------------------------------------------------------

void Material::Bind() { m_texture->Bind(0); }

// ------------------------------------------------------------------------------

void Material::Unbind() { m_texture->Unbind(0); }

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage