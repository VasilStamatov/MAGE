#include "core/Timer.h"

namespace mage
{
namespace core
{

Timer::Timer()
    : m_start(HRTimePoint::clock::now())
{
}

void Timer::Renew() { m_start = HRTimePoint::clock::now(); }

float Timer::GetElapsedMilli() const
{
  using Milli = std::chrono::duration<float, std::milli>;

  return std::chrono::duration_cast<Milli>(
             (HRTimePoint::clock::now() - m_start))
      .count();
}

float Timer::GetElapsedSeconds() const { return GetElapsedMilli() / 1000.0f; }

} // namespace core
} // namespace mage