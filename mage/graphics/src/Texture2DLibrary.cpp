#include "graphics/Texture2DLibrary.h"

#include <algorithm>

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

Texture2DLibrary::Texture2DLibrary()
    : m_loadedTextures()
{
}

// ------------------------------------------------------------------------------

Texture2DLibrary::~Texture2DLibrary() {}

// ------------------------------------------------------------------------------

std::shared_ptr<GLTexture2D>
Texture2DLibrary::Get(const std::string& _filepath,
                      TextureParameters _parameters)
{
  std::hash<std::string> hashFunction;
  std::uint32_t hashedName = hashFunction(_filepath);

  auto foundIt =
      std::find_if(m_loadedTextures.begin(), m_loadedTextures.end(),
                   [hashedName](const Texture2DResourceInstance& _resource) {
                     return _resource.m_hashedName == hashedName;
                   });
  ;

  if (foundIt != m_loadedTextures.end())
  {
    return foundIt->m_texture;
  }

  m_loadedTextures.emplace_back(
      std::make_shared<GLTexture2D>(_filepath, _parameters), hashedName);

  return m_loadedTextures.back().m_texture;
}

// ------------------------------------------------------------------------------

void Texture2DLibrary::Clear() { m_loadedTextures.clear(); }

// ------------------------------------------------------------------------------

void Texture2DLibrary::Refresh()
{
  m_loadedTextures.erase(
      std::remove_if(m_loadedTextures.begin(), m_loadedTextures.end(),
                     [](const Texture2DResourceInstance& _resource) -> bool {
                       return _resource.m_texture.use_count() == 0;
                     }),
      m_loadedTextures.end());
}

// ------------------------------------------------------------------------------

Texture2DLibrary::Texture2DResourceInstance::Texture2DResourceInstance(
    std::shared_ptr<GLTexture2D>&& _texture, std::uint32_t _hashedName)
    : m_texture(std::move(_texture))
    , m_hashedName(_hashedName)
{
}

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage