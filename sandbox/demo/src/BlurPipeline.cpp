#include "demo/BlurPipeline.h"

// ------------------------------------------------------------------------------

BlurPipeline::BlurPipeline(mage::graphics::GLShader _lightKeyShader,
                           mage::graphics::GLShader _blurShader,
                           mage::graphics::GLShader _mergeShader,
                           std::uint8_t _blurIterations)
    : m_lightKeyShader(std::move(_lightKeyShader))
    , m_blurShader(std::move(_blurShader))
    , m_mergeShader(std::move(_mergeShader))
    , m_blurIterations(_blurIterations)

{
}

// ------------------------------------------------------------------------------

BlurPipeline::~BlurPipeline() {}

// ------------------------------------------------------------------------------

void BlurPipeline::Execute(mage::graphics::GLFramebuffer2D& _source,
                           mage::graphics::GLFramebuffer2D& _target)
{
  // Make temporary framebuffers to hold texture data
  mage::graphics::GLFramebuffer2D lightSource(_source.GetWidth(),
                                              _source.GetHeight());

  mage::graphics::GLFramebuffer2D blurredLight(_source.GetWidth(),
                                               _source.GetHeight());

  // The screen vertex data is used for all post processing so it stay bound
  m_screenVAO.Bind();
  m_screenIBO.Bind();

  // Output a texture with only brightly coloured pixels
  m_lightKeyShader.Bind();
  lightSource.Bind();
  _source.GetTexture().Bind(0);

  m_screenVAO.DrawElements(m_screenIBO.GetCount());

  // Output a texture with the bright pixels blurred
  m_blurShader.Bind();
  for (size_t i = 0; i < m_blurIterations; i++)
  {
    blurredLight.Bind();
    lightSource.GetTexture().Bind(0);
    m_screenVAO.DrawElements(m_screenIBO.GetCount());

    // Render back into ligthsource for further iterations
    lightSource.Bind();
    blurredLight.GetTexture().Bind(0);
    m_screenVAO.DrawElements(m_screenIBO.GetCount());
  }

  // Merge the blurred texture with the original source
  m_mergeShader.Bind();
  _target.Bind();
  _source.GetTexture().Bind(0);
  blurredLight.GetTexture().Bind(1);
  m_screenVAO.DrawElements(m_screenIBO.GetCount());

  // Reset State
  blurredLight.GetTexture().Unbind(1);
  _source.GetTexture().Unbind(0);
  _target.Unbind();

  m_screenIBO.Unbind();
  m_screenVAO.Unbind();
}

// ------------------------------------------------------------------------------
