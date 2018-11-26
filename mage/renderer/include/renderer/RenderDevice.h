#pragma once

#include <cstdint>

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// Buffer types used for clearing the screen.
/////////////////////////////////////////////////
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

/////////////////////////////////////////////////
/// Blend functions
/////////////////////////////////////////////////
enum class RendererBlendFunction
{
  Zero,
  One,
  SourceAlpha,
  DestinationAlpha,
  OneMinusSourceAlpha
};

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// Blend equations
/////////////////////////////////////////////////
enum class RendererBlendEquation
{
  Add,
  Subtract
};

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// Depth functions
/////////////////////////////////////////////////
enum class DepthFunc
{
  Never,
  Less,
  Equal,
  LessOrEqual,
  Greater,
  NotEqual,
  GreaterOrEqual,
  Always,
};

// ------------------------------------------------------------------------------

// TODO: This can be changed to fully control the render API like the audio
// device.

/////////////////////////////////////////////////
/// The main render device which handles intialization of the render API and
/// some control of state.
/////////////////////////////////////////////////
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

  void SetDepthFunc(DepthFunc _func);

  // ------------------------------------------------------------------------------

  void SetBlend(bool _enabled);

  // ------------------------------------------------------------------------------

  void SetCulling(bool _enabled);

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