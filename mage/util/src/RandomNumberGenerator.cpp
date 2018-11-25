#include "util/RandomNumberGenerator.h"

using HighResClock = std::chrono::high_resolution_clock;

namespace mage
{
namespace util
{

RandomNumberGenerator::RandomNumberGenerator()
{
  m_generator.seed(static_cast<unsigned int>(
      HighResClock::now().time_since_epoch().count()));
}

} // namespace util
} // namespace mage