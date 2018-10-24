#pragma once

#include "Vec.h"

namespace mage
{
namespace math
{

// ------------------------------------------------------------------------------

template <typename T, std::uint32_t Size> class Mat
{
public:
  Mat() { memset(m_elements, 0, Size * Size * sizeof(T)); }

  // ------------------------------------------------------------------------------

  explicit Mat(T _diagonal)
  {
    memset(m_elements, 0, Size * Size * sizeof(T));

    for (auto i = 0; i < Size * Size; i += Size + 1)
    {
      m_elements[i] = _diagonal;
    }
  }

  // ------------------------------------------------------------------------------

  explicit Mat(T* _elements)
  {
    memcpy(m_elements, _elements, Size * Size * sizeof(T));
  }

  // ------------------------------------------------------------------------------

  Mat operator+(const Mat& _rhs) const
  {
    Mat rtn;

    for (auto i = 0; i < Size * Size; i++)
    {
      rtn[i] = m_elements[i] + _rhs.m_elements[i];
    }

    return rtn;
  }

  // ------------------------------------------------------------------------------

  Mat operator-(const Mat& _rhs) const
  {
    Mat rtn;

    for (auto i = 0; i < Size * Size; i++)
    {
      rtn[i] = m_elements[i] - _rhs.m_elements[i];
    }

    return rtn;
  }

  // ------------------------------------------------------------------------------

  Mat operator*(const Mat& _rhs) const
  {
    Mat rtn;

    for (auto row = 0; row < Size; row++)
    {
      for (auto col = 0; col < Size; col++)
      {
        T sum = 0.0f;

        for (int32_t e = 0; e < Size; e++)
        {
          sum += m_elements[e + row * Size] * _rhs.m_elements[col + e * Size];
        }

        rtn.m_elements[col + row * Size] = sum;
      }
    }

    return rtn;
  }

  // ------------------------------------------------------------------------------

  Mat operator*(T _scalar) const
  {
    Mat rtn;

    for (auto i = 0; i < Size * Size; i++)
    {
      rtn[i] = m_elements[i] * _scalar;
    }

    return rtn;
  }

  // ------------------------------------------------------------------------------

  Mat operator/(T _scalar) const
  {
    Mat rtn;

    for (auto i = 0; i < Size * Size; i++)
    {
      rtn[i] = m_elements[i] / _scalar;
    }

    return rtn;
  }

  // ------------------------------------------------------------------------------

  Vec<T, Size> operator*(const Vec<T, Size>& _vec) const
  {
    Vec<T, Size> rtn;

    for (auto row = 0; row < Size; row++)
    {
      for (auto col = 0; col < Size; col++)
      {
        rtn[row] += m_elements[col + row * Size] * _vec[col];
      }
    }

    return rtn;
  }

  // ------------------------------------------------------------------------------

  Mat& operator+=(const Mat& _rhs)
  {
    *this = *this + _rhs;
    return *this;
  }

  // ------------------------------------------------------------------------------

  Mat& operator-=(const Mat& _rhs)
  {
    *this = *this - _rhs;
    return *this;
  }

  // ------------------------------------------------------------------------------

  Mat& operator*=(const Mat& _rhs)
  {
    *this = *this * _rhs;
    return *this;
  }

  // ------------------------------------------------------------------------------

  Mat& operator*=(T _scalar)
  {
    *this = *this * _rhs;
    return *this;
  }

  // ------------------------------------------------------------------------------

  Mat& operator/=(T _scalar)
  {
    *this = *this / _rhs;
    return *this;
  }

  // ------------------------------------------------------------------------------

  T& operator[](std::uint32_t _index)
  {
    assert(_index < Size * Size);
    return m_elements[_index];
  }

  // ------------------------------------------------------------------------------

  T operator[](std::uint32_t _index) const
  {
    assert(_index < Size * Size);
    return m_elements[_index];
  }

  // ------------------------------------------------------------------------------

  bool operator==(const Mat& _rhs) const
  {
    bool allElementsAreEqual = true;

    for (auto i = 0; i < Size * Size; i++)
    {
      allElementsAreEqual &=
          Equals(m_elements[i], _rhs.m_elements[i], c_epsilon<T>);
    }

    return allElementsAreEqual;
  }

  // ------------------------------------------------------------------------------

  bool operator!=(const Mat& _rhs) const { return !operator==(_rhs); }

  // ------------------------------------------------------------------------------

  friend std::ostream& operator<<(std::ostream& _outStream, const Mat& _mat)
  {
    _outStream << "Mat:\n";

    for (auto row = 0; row < Size; row++)
    {
      _outStream << "Row " << row << '\t';
      _outStream << "{ ";

      for (auto col = 0; col < Size; col++)
      {
        _outStream << _mat[col + row * Size] << ", ";
      }

      _outStream << '}' << '\n';
    }

    return _outStream;
  }

  // ------------------------------------------------------------------------------

private:
  // [row][col] access = col + row * Size
  T m_elements[Size * Size];
};

// ------------------------------------------------------------------------------

template <typename T> Mat<T, 3> GetTransposedMat(const Mat<T, 3>& _mat)
{
  using std::swap;

  Mat rtn(_mat);

  swap(rtn.m_elements[1], rtn.m_elements[3]);
  swap(rtn.m_elements[2], rtn.m_elements[6]);
  swap(rtn.m_elements[5], rtn.m_elements[7]);

  return rtn;
}

// ------------------------------------------------------------------------------

template <typename T> Mat<T, 4> GetTransposedMat(const Mat<T, 4>& _mat)
{
  using std::swap;

  Mat rtn(_mat);

  swap(rtn[1], rtn[4]);
  swap(rtn[2], rtn[8]);
  swap(rtn[6], rtn[9]);
  swap(rtn[3], rtn[12]);
  swap(rtn[7], rtn[13]);
  swap(rtn[11], rtn[14]);

  return rtn;
}

// ------------------------------------------------------------------------------

template <typename T> Mat<T, 4> GenTranslationMat(const Vec<T, 3>& _translation)
{
  float matrixData[16] = {
      static_cast<T>(1.0), static_cast<T>(0.0), static_cast<T>(0.0),
      _translation[0],     static_cast<T>(0.0), static_cast<T>(1.0),
      static_cast<T>(0.0), _translation[1],     static_cast<T>(0.0),
      static_cast<T>(0.0), static_cast<T>(1.0), _translation[2],
      static_cast<T>(0.0), static_cast<T>(0.0), static_cast<T>(0.0),
      static_cast<T>(1.0)};

  return Mat<T, 4>(matrixData);
}

// ------------------------------------------------------------------------------

template <typename T>
Mat<T, 4> GenRotationMat(T _radians, const Vec<T, 3>& _axis)
{
  const T c = std::cos(_radians);
  const T s = std::sin(_radians);

  const Vec<T, 3> normalizedAxis = _axis.GetNormalized();

  const T omc = static_cast<T>(1.0) - c;

  Mat<T, 4> rtn;

  rtn[0 + 0 * 4] = normalizedAxis[0] * normalizedAxis[0] * omc + c;

  rtn[0 + 1 * 4] =
      normalizedAxis[1] * normalizedAxis[0] * omc + normalizedAxis[2] * s;

  rtn[0 + 2 * 4] =
      normalizedAxis[0] * normalizedAxis[2] * omc - normalizedAxis[1] * s;

  rtn[1 + 0 * 4] =
      normalizedAxis[0] * normalizedAxis[1] * omc - normalizedAxis[2] * s;

  rtn[1 + 1 * 4] = normalizedAxis[1] * normalizedAxis[1] * omc + c;

  rtn[1 + 2 * 4] =
      normalizedAxis[1] * normalizedAxis[2] * omc + normalizedAxis[0] * s;

  rtn[2 + 0 * 4] =
      normalizedAxis[0] * normalizedAxis[2] * omc + normalizedAxis[1] * s;

  rtn[2 + 1 * 4] =
      normalizedAxis[1] * normalizedAxis[2] * omc - normalizedAxis[0] * s;

  rtn[2 + 2 * 4] = normalizedAxis[2] * normalizedAxis[2] * omc + c;

  rtn[3 + 3 * 4] = static_cast<T>(1.0);

  return rtn;
}

// ------------------------------------------------------------------------------

template <typename T> Mat<T, 4> GenScalingMat(const Vec<T, 3>& _scale)
{
  float matrixData[16] = {
      _scale[0],           static_cast<T>(0.0), static_cast<T>(0.0),
      static_cast<T>(0.0), static_cast<T>(0.0), _scale[1],
      static_cast<T>(0.0), static_cast<T>(0.0), static_cast<T>(0.0),
      static_cast<T>(0.0), _scale[2],           static_cast<T>(0.0),
      static_cast<T>(0.0), static_cast<T>(0.0), static_cast<T>(0.0),
      static_cast<T>(1.0)};

  return Mat<T, 4>(matrixData);
}

// ------------------------------------------------------------------------------

template <typename T>
Mat<T, 4> GenOrthoMat(T _left, T _right, T _bottom, T _top, T _near, T _far)
{
  Mat<T, 4> rtn;

  rtn[0 + 0 * 4] = static_cast<T>(2.0) / (_right - _left);
  rtn[1 + 1 * 4] = static_cast<T>(2.0) / (_top - _bottom);

  rtn[3 + 0 * 4] = -(_right + _left) / (_right - _left);
  rtn[3 + 1 * 4] = -(_top + _bottom) / (_top - _bottom);

  rtn[2 + 2 * 4] = -static_cast<T>(2.0) / (_far - _near);
  rtn[3 + 2 * 4] = -(_far + _near) / (_far - _near);

  return rtn;
}

// ------------------------------------------------------------------------------

template <typename T>
Mat<T, 4> GenPerspectiveMat(T _FovRadians, T _aspectRatio, T _near, T _far)
{
  assert(std::abs(_aspectRatio - std::numeric_limits<T>::epsilon()) >
         static_cast<T>(0.0));

  Mat<T, 4> rtn;

  const T tanHalfFoV = std::tan(_FovRadians * static_cast<T>(0.5));

  rtn[0] = static_cast<T>(1.0) / (_aspectRatio * tanHalfFoV);
  rtn[1 + 1 * 4] = static_cast<T>(1.0) / (tanHalfFoV);
  rtn[2 + 3 * 4] = static_cast<T>(-1.0);

  rtn[2 + 2 * 4] = -(_far + _near) / (_far - _near);
  rtn[3 + 2 * 4] = -(static_cast<T>(2.0) * _far * _near) / (_far - _near);

  return rtn;
}

// ------------------------------------------------------------------------------

template <typename T>
Mat<T, 4> GenLookAtMat(const Vec<T, 3>& _camera, const Vec<T, 3>& _object,
                       const Vec<T, 3>& _up)
{
  Mat<T, 4> rtn(static_cast<T>(1.0));

  const Vec<T, 3> forward = (_object - _camera).GetNormalized();
  const Vec<T, 3> right = Cross(forward, _up.GetNormalized()).GetNormalized();
  const Vec<T, 3> up = Cross(right, forward);

  rtn[0 + 0 * 4] = right[0];
  rtn[1 + 0 * 4] = right[1];
  rtn[2 + 0 * 4] = right[2];
  rtn[0 + 1 * 4] = up[0];
  rtn[1 + 1 * 4] = up[1];
  rtn[2 + 1 * 4] = up[2];
  rtn[0 + 2 * 4] = -forward[0];
  rtn[1 + 2 * 4] = -forward[1];
  rtn[2 + 2 * 4] = -forward[2];
  rtn[3 + 0 * 4] = -right.Dot(_camera);
  rtn[3 + 1 * 4] = -up.Dot(_camera);
  rtn[3 + 2 * 4] = forward.Dot(_camera);

  return rtn;
}

// ------------------------------------------------------------------------------

using Mat3f = Mat<float, 3>;
using Mat3d = Mat<double, 3>;
using Mat4f = Mat<float, 4>;
using Mat4d = Mat<double, 4>;

// ------------------------------------------------------------------------------

} // namespace math
} // namespace mage