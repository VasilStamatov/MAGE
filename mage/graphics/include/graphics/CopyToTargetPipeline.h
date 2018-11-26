#pragma once

#include "PostProcessPipeline.h"

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// This post process pipeline simply renders the _source's texture into _target
/// buffer Mainly used to render the post-processed image to the screen.
/////////////////////////////////////////////////
class CopyToTargetPipeline : public PostProcessPipeline
{
public:
  CopyToTargetPipeline();
  virtual ~CopyToTargetPipeline();

  /////////////////////////////////////////////////
  /// If _source and _target are the same instance,, it renders the texture to
  /// the screen buffer.
  /////////////////////////////////////////////////
  virtual void Execute(GLFramebuffer2D& _source,
                       GLFramebuffer2D& _target) override;

private:
  GLShader m_nullPassShader;
};

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage