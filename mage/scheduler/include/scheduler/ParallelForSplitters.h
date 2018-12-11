#pragma once

#include <cstdint>

namespace mage
{
namespace scheduler
{

// ------------------------------------------------------------------------------

class CountSplitter
{
public:
  explicit CountSplitter(std::uint32_t _count)
      : m_count(_count)
  {
  }

  template <typename T> inline bool Split(std::uint32_t _count) const
  {
    return (_count > m_count);
  }

private:
  std::uint32_t m_count;
};

// ------------------------------------------------------------------------------

class DataSizeSplitter
{
public:
  explicit DataSizeSplitter(std::uint32_t _size)
      : m_size(_size)
  {
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