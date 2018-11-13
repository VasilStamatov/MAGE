#pragma once

#include <cstdint>

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

enum class RendererBufferType
{
  None,
  Color,
  Depth,
  Stencil,

  Color_Depth,
  Color_Depth_Stencil,
  Depth_Stencil
};

// ------------------------------------------------------------------------------

enum class RendererBlendFunction
{
  Zero,
  One,
  SourceAlpha,
  DestinationAlpha,
  OneMinusSourceAlpha
};

// ------------------------------------------------------------------------------

enum class RendererBlendEquation
{
  Add,
  Subtract
};

// ------------------------------------------------------------------------------

class RenderDevice
{
public:
  RenderDevice();

  // ------------------------------------------------------------------------------

  void Initialize();

  // ------------------------------------------------------------------------------

  void Shutdown();

  // ------------------------------------------------------------------------------

  void ClearBuffer(RendererBufferType _buffer);

  // ------------------------------------------------------------------------------

  void SetDepthTesting(bool _enabled);

  // ------------------------------------------------------------------------------

  void SetBlend(bool _enabled);

  // ------------------------------------------------------------------------------

  void SetViewport(std::uint32_t _x, std::uint32_t _y, std::uint32_t _width,
                   std::uint32_t _height);

  // ------------------------------------------------------------------------------

  void SetBlendFunction(RendererBlendFunction _source,
                        RendererBlendFunction _destination);

  // ------------------------------------------------------------------------------

  void SetBlendEquation(RendererBlendEquation _blendEquation);

  // ------------------------------------------------------------------------------
};

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage