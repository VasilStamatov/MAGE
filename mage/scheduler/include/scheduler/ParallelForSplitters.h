#pragma once

#include <cassert>
#include <cstdint>

namespace mage
{
namespace scheduler
{

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// Splits the data based on the passed count.
/////////////////////////////////////////////////
class CountSplitter
{
public:
  explicit CountSplitter(std::uint32_t _count)
      : m_count(_count)
  {
    assert(m_count > 1);
  }

  template <typename T> inline bool Split(std::uint32_t _count) const
  {
    return (_count > m_count);
  }

private:
  std::uint32_t m_count;
};

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// Splits the data based on the data size in bytes (this is useful for
/// splitting arrays into sizes that fit cache lines or the whole L1 cache)
/////////////////////////////////////////////////
class DataSizeSplitter
{
public:
  explicit DataSizeSplitter(std::uint32_t _size)
      : m_size(_size)
  {
    assert(m_size > 1);
  }

  template <typename T> inline bool Split(std::uint32_t _count) const
  {
    return (_count * sizeof(T) > m_size);
  }

private:
  std::uint32_t m_size;
};

// ------------------------------------------------------------------------------

} // namespace scheduler
} // namespace mage