#include "graphics/Material.h"

#include <assert.h>

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

Material::Material(const std::string& _imageFile)
    : m_texture(_imageFile)
{
}

// ------------------------------------------------------------------------------

void Material::Bind() { m_texture.Bind(0); }

// ------------------------------------------------------------------------------

void Material::Unbind() { m_texture.Unbind(0); }

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage