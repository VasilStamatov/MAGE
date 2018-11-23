#pragma once

#include "PostProcessPass.h"

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

class NullPostProcessPass : public PostProcessPass
{
public:
  NullPostProcessPass();
  virtual ~NullPostProcessPass();

  virtual void Apply(GLFramebuffer2D& _source,
                     GLFramebuffer2D* _target) override;
};

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage