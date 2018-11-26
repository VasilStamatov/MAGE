#pragma once

#include <chrono>

// ------------------------------------------------------------------------------

using HRTimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

// ------------------------------------------------------------------------------

namespace mage
{
namespace core
{

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// The timer begins running once constructer and can be queried for elapsed
/// time or restarted.
/////////////////////////////////////////////////
class Timer
{
public:
  Timer();

  void Renew();

  float GetElapsedMilli() const;
  float GetElapsedSeconds() const;

private:
  HRTimePoint
      m_start; ///< The point at which the class instance was constructer
};

// ------------------------------------------------------------------------------

} // namespace core
} // namespace mage