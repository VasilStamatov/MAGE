#pragma once

#include <memory>

namespace mage
{
namespace audio
{

// ------------------------------------------------------------------------------

class AudioDevice
{
public:
  AudioDevice();
  ~AudioDevice();

  void Initialize();
  void Shutdown();

private:
  class Impl;

  std::unique_ptr<Impl> m_impl;
};

// ------------------------------------------------------------------------------

} // namespace audio
} // namespace mage