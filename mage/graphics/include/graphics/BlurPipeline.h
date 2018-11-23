#pragma once

#include "PostProcessPipeline.h"

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

class BlurPipeline : public PostProcessPipeline
{
public:
  BlurPipeline(GLShader _lightKeyShader, GLShader _blurShader,
               GLShader _mergeShader, std::uint8_t _blurIterations);
  virtual ~BlurPipeline();

  virtual void Execute(GLFramebuffer2D& _source,
                       GLFramebuffer2D& _target) override;

private:
  GLShader m_lightKeyShader;
  GLShader m_blurShader;
  GLShader m_mergeShader;

  std::uint8_t m_blurIterations;
};

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage