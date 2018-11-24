#pragma once

#include <cstdint>
#include <string>

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

enum class TextureWrap
{
  None,
  Repeat,
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
  GLTexture2D(std::uint32_t _width, std::uint32_t _height,
              TextureParameters _parameters = TextureParameters());
  GLTexture2D(const std::string& _filepath, bool _invertY = true,
              TextureParameters _parameters = TextureParameters());
  ~GLTexture2D();

  GLTexture2D(const GLTexture2D& _copy) = delete;
  GLTexture2D(GLTexture2D&& _moved);

  GLTexture2D& operator=(const GLTexture2D& _copy) = delete;
  GLTexture2D& operator=(GLTexture2D&& _moved);

  // ------------------------------------------------------------------------------

  void Bind(std::uint32_t _slot) const;

  // ------------------------------------------------------------------------------

  void Unbind(std::uint32_t _slot) const;

  // ------------------------------------------------------------------------------

  // compares the handle id's
  bool operator==(const GLTexture2D& _other) const;

  // ------------------------------------------------------------------------------

  inline std::uint32_t GetHandle() const { return m_handle; }

private:
  void LoadTexture(const std::string& _filepath, bool _invertY,
                   TextureParameters _parameters);

  // ------------------------------------------------------------------------------

  void GenTexture(uint32_t _width, std::uint32_t _height, std::uint8_t* _data,
                  TextureParameters _parameters);

  // ------------------------------------------------------------------------------

private:
  std::uint32_t m_handle;
};

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage