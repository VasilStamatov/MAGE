#pragma once

#include "renderer/GLTexture2D.h"

#include <memory>
#include <vector>

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// Resource manager for 2D texture to avoid re-loading the same texture.
/////////////////////////////////////////////////
class Texture2DLibrary
{
public:
  Texture2DLibrary();
  ~Texture2DLibrary();

  // ------------------------------------------------------------------------------

  std::shared_ptr<GLTexture2D>
  Get(const std::string& _filepath, bool _invertY = true,
      TextureParameters _parameters = TextureParameters());

  // ------------------------------------------------------------------------------

  void Clear();
  void Refresh();

  // ------------------------------------------------------------------------------

private:
  struct Texture2DResourceInstance
  {
    Texture2DResourceInstance(std::shared_ptr<GLTexture2D>&& _texture,
                              std::uint32_t _hashedName);

    std::shared_ptr<GLTexture2D> m_texture;
    std::uint32_t m_hashedName;
  };

  // ------------------------------------------------------------------------------

  std::vector<Texture2DResourceInstance> m_loadedTextures;
};

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage