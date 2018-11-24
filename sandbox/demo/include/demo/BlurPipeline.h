#pragma once

#include <graphics/PostProcessPipeline.h>

// ------------------------------------------------------------------------------

class BlurPipeline : public mage::graphics::PostProcessPipeline
{
public:
  BlurPipeline(mage::graphics::GLShader _lightKeyShader,
               mage::graphics::GLShader _blurShader,
               mage::graphics::GLShader _mergeShader,
               std::uint8_t _blurIterations);
  virtual ~BlurPipeline();

  virtual void Execute(mage::graphics::GLFramebuffer2D& _source,
                       mage::graphics::GLFramebuffer2D& _target) override;

private:
  mage::graphics::GLShader m_lightKeyShader;
  mage::graphics::GLShader m_blurShader;
  mage::graphics::GLShader m_mergeShader;

  std::uint8_t m_blurIterations;
};

// ------------------------------------------------------------------------------
