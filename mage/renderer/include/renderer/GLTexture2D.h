#pragma once

#include <cstdint>
#include <string>

namespace mage
{
namespace renderer
{

// ------------------------------------------------------------------------------

enum class TextureWrap
{
  None,
  Repeat,
  Clamp,
  MirroredRepeat,
  ClampToEdge,
  ClampToBorder
};

// ------------------------------------------------------------------------------

enum class TextureFilter
{
  None,
  Linear,
  Nearest
};

// ------------------------------------------------------------------------------

enum class TextureFormat
{
  None,
  RGB,
  RGBA,
  Luminance,
  LuminanceAlpha
};

// ------------------------------------------------------------------------------

struct TextureParameters
{
  TextureParameters();
  TextureParameters(TextureFormat _format, TextureFilter _filter,
                    TextureWrap _wrap);

  TextureFormat m_format;
  TextureFilter m_filter;
  TextureWrap m_wrap;
};

// ------------------------------------------------------------------------------

class GLTexture2D
{
public:
  GLTexture2D(const std::string& _filepath,
              TextureParameters _parameters = TextureParameters());
  ~GLTexture2D();

  // ------------------------------------------------------------------------------

  void Bind(std::uint32_t _slot) const;

  // ------------------------------------------------------------------------------

  void Unbind(std::uint32_t _slot) const;

  // ------------------------------------------------------------------------------

  bool operator==(const GLTexture2D& _other) const;

  // ------------------------------------------------------------------------------

private:
  void LoadTexture(const std::string& _filepath, TextureParameters _parameters);

  // ------------------------------------------------------------------------------

private:
  std::uint32_t m_handle;
};

// ------------------------------------------------------------------------------

} // namespace renderer
} // namespace mage