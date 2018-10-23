#pragma once

#include <assert.h>
#include <limits>
#include <ostream>

namespace mage
{
namespace math
{

template <typename T, std::uint32_t Size> class Vec
{
public:
  Vec() { memset(m_elements, 0, Size * sizeof(T)); }
  explicit Vec(T _val)
  {
    for (auto i = 0; i < Size; i++)
    {
      m_elements[i] = _val;
    }
  }
  Vec(T _arg1, T _arg2)
  {
    static_assert(Size == 2);
    m_elements[0] = _arg1;
    m_elements[1] = _arg2;
  }
  Vec(T _arg1, T _arg2, T _arg3)
  {
    static_assert(Size == 3);
    m_elements[0] = _arg1;
    m_elements[1] = _arg2;
    m_elements[2] = _arg3;
  }
  Vec(T _arg1, T _arg2, T _arg3, T _arg4)
  {
    static_assert(Size == 4);
    m_elements[0] = _arg1;
    m_elements[1] = _arg2;
    m_elements[2] = _arg3;
    m_elements[3] = _arg4;
  }

  Vec operator+(const Vec& _rhs) const
  {
    Vec<T, Size> rtn;

    for (auto i = 0; i < Size; i++)
    {
      rtn.m_elements[i] = m_elements[i] + _rhs.m_elements[i];
    }

    return rtn;
  }
  Vec operator-(const Vec& _rhs) const
  {
    Vec<T, Size> rtn;

    for (auto i = 0; i < Size; i++)
    {
      rtn.m_elements[i] = m_elements[i] - _rhs.m_elements[i];
    }

    return rtn;
  }
  Vec operator*(const Vec& _rhs) const
  {
    Vec<T, Size> rtn;

    for (auto i = 0; i < Size; i++)
    {
      rtn.m_elements[i] = m_elements[i] * _rhs.m_elements[i];
    }

    return rtn;
  }
  Vec operator/(const Vec& _rhs) const
  {
    Vec<T, Size> rtn;

    for (auto i = 0; i < Size; i++)
    {
      rtn.m_elements[i] = m_elements[i] / _rhs.m_elements[i];
    }

    return rtn;
  }
  Vec operator*(T _scalar) const
  {
    Vec<T, Size> rtn;

    for (auto i = 0; i < Size; i++)
    {
      rtn.m_elements[i] = m_elements[i] * _scalar;
    }

    return rtn;
  }
  Vec operator/(T _scalar) const
  {
    Vec<T, Size> rtn;

    for (auto i = 0; i < Size; i++)
    {
      rtn.m_elements[i] = m_elements[i] / _scalar;
    }

    return rtn;
  }

  Vec& operator+=(const Vec& _rhs)
  {
    for (auto i = 0; i < Size; i++)
    {
      m_elements[i] += _rhs.m_elements[i];
    }

    return *this;
  }
  Vec& operator-=(const Vec& _rhs)
  {
    for (auto i = 0; i < Size; i++)
    {
      m_elements[i] -= _rhs.m_elements[i];
    }
    return *this;
  }
  Vec& operator*=(const Vec& _rhs)
  {
    for (auto i = 0; i < Size; i++)
    {
      m_elements[i] *= _rhs.m_elements[i];
    }
    return *this;
  }
  Vec& operator/=(const Vec& _rhs)
  {
    for (auto i = 0; i < Size; i++)
    {
      m_elements[i] /= _rhs.m_elements[i];
    }
    return *this;
  }
  Vec& operator*=(T _scalar)
  {
    for (auto i = 0; i < Size; i++)
    {
      m_elements[i] *= _scalar;
    }
    return *this;
  }
  Vec& operator/=(T _scalar)
  {
    for (auto i = 0; i < Size; i++)
    {
      m_elements[i] *= _scalar;
    }
    return *this;
  }

  bool operator==(const Vec& _rhs) const
  {
    bool allElementsAreEqual = true;

    for (auto i = 0; i < Size; i++)
    {
      allElementsAreEqual &= std::abs(m_elements[i] - _rhs.m_elements[i]) <=
                             std::numeric_limits<T>::epsilon();
    }

    return allElementsAreEqual;
  }
  bool operator!=(const Vec& _rhs) const { return !operator==(_rhs); }
  bool operator>(const Vec& _rhs) const
  {
    bool allElementsAreHigher = true;

    for (auto i = 0; i < Size; i++)
    {
      allElementsAreHigher &= m_elements[i] > _rhs.m_elements[i];
    }

    return allElementsAreHigher;
  }
  bool operator>=(const Vec& _rhs) const
  {
    bool allElementsAreHigherOrEqual = true;

    for (auto i = 0; i < Size; i++)
    {
      allElementsAreHigherOrEqual &= m_elements[i] >= _rhs.m_elements[i];
    }

    return allElementsAreHigher;
  }
  bool operator<(const Vec& _rhs) const
  {
    bool allElementsAreLower = true;

    for (auto i = 0; i < Size; i++)
    {
      allElementsAreLower &= m_elements[i] < _rhs.m_elements[i];
    }

    return allElementsAreLower;
  }
  bool operator<=(const Vec& _rhs) const
  {
    bool allElementsAreLowerOrEqual = true;

    for (auto i = 0; i < Size; i++)
    {
      allElementsAreLowerOrEqual &= m_elements[i] <= _rhs.m_elements[i];
    }

    return allElementsAreLowerOrEqual;
  }

  T& operator[](std::uint32_t _index)
  {
    assert(_index < Size);
    return m_elements[_index];
  }

  T operator[](std::uint32_t _index) const
  {
    assert(_index < Size);
    return m_elements[_index];
  }

  T GetMagnitude() const { return std::sqrt(GetSquaredMagnitude()); }

  T GetSquaredMagnitude() const
  {
    T rtn = 0;

    for (auto i = 0; i < Size; i++)
    {
      rtn += m_elements[i] * m_elements[i];
    }

    return rtn;
  }

  Vec GetNormalized() const
  {
    const auto magnitude = GetMagnitude();

    Vec<T, Size> rtn;

    for (auto i = 0; i < Size; i++)
    {
      rtn.m_elements[i] = m_elements[i] / magnitude;
    }

    return rtn;
  }

  T Dot(const Vec& _other) const noexcept
  {
    T rtn = 0;

    for (auto i = 0; i < Size; i++)
    {
      rtn += m_elements[i] * _other.m_elements[i];
    }

    return rtn;
  }

  T Distance(const Vec& _other) const
  {
    return (*this - _other).GetMagnitude();
  }
  T SquaredDistance(const Vec& _other) const
  {
    return (*this - _other).GetSquaredMagnitude();
  }

  friend Vec operator*(T _lhs, const Vec& _rhs) { return _rhs * _lhs; }
  friend Vec operator/(T _lhs, const Vec& _rhs) { return _rhs / _lhs; }

  friend std::ostream& operator<<(std::ostream& _outStream, const Vec& _vec)
  {
    _outStream << "Vec: { ";

    for (auto i = 0; i < Size; i++)
    {
      _outStream << _vec.m_elements[i] << ", ";
    }

    _outStream << '}';
    return _outStream;
  }

private:
  T m_elements[Size];
};

template <typename T>
Vec<T, 3> Cross(const Vec<T, 3>& _first, const Vec<T, 3>& _second)
{
  return Vec<T, 3>(_first[1] * _second[2] - _first[2] * _second[1],
                   _first[2] * _second[0] - _first[0] * _second[2],
                   _first[0] * _second[1] - _first[1] * _second[0]);
}

using Vec2f = Vec<float, 2>;
using Vec2d = Vec<double, 2>;
using Vec2i32 = Vec<std::int32_t, 2>;
using Vec2ui32 = Vec<std::uint32_t, 2>;

using Vec3f = Vec<float, 3>;
using Vec3d = Vec<double, 3>;
using Vec3i32 = Vec<std::int32_t, 3>;
using Vec3ui32 = Vec<std::uint32_t, 3>;

using Vec4f = Vec<float, 4>;
using Vec4d = Vec<double, 4>;
using Vec4i32 = Vec<std::int32_t, 4>;
using Vec4ui32 = Vec<std::uint32_t, 4>;

} // namespace math
} // namespace mage