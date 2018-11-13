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

class Timer
{
public:
  Timer();

  void Renew();

  float GetElapsedMilli() const;
  float GetElapsedSeconds() const;

private:
  HRTimePoint m_start;
};

// ------------------------------------------------------------------------------

} // namespace core
} // namespace mage