#pragma once

#include "PostProcessPipeline.h"

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

class CopyToTargetPipeline : public PostProcessPipeline
{
public:
  CopyToTargetPipeline();
  virtual ~CopyToTargetPipeline();

  virtual void Execute(GLFramebuffer2D& _source,
                       GLFramebuffer2D& _target) override;

private:
  GLShader m_nullPassShader;
};

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage