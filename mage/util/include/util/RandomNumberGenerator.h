#pragma once

#include <chrono>
#include <random>

namespace mage
{
namespace util
{

/////////////////////////////////////////////////
/// class for random number generation
/////////////////////////////////////////////////
class RandomNumberGenerator
{
public:
  RandomNumberGenerator();

  /////////////////////////////////////////////////
  /// Generate a random number of type T (integer) between [min, max]
  /////////////////////////////////////////////////
  template <typename T> T GenRandInt(T _min, T _max)
  {
    std::uniform_int_distribution<T> intDis(_min, _max);
    return intDis(m_generator);
  }

  /////////////////////////////////////////////////
  /// Generate a random number of type T (real) between [min, max]
  /////////////////////////////////////////////////
  template <typename T> T GenRandReal(T _min, T _max)
  {
    std::uniform_real_distribution<T> realDis(_min, _max);
    return realDis(m_generator);
  }

private:
  std::mt19937 m_generator; ///< the mersene twister engine for generation
};

} // namespace util
} // namespace mage