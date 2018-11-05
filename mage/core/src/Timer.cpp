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

std::chrono::nanoseconds Timer::GetElapsedTime() const
{
  return HRTimePoint::clock::now() - m_start;
}

} // namespace core
} // namespace mage