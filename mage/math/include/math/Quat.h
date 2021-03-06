#pragma once

#include "Mat.h"

namespace mage
{
namespace math
{

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// Quaternion class which is templated to support a float and double quats.
/////////////////////////////////////////////////
template <typename T> class Quat
{
public:
  Quat()
  {
    memset(m_elements, 0, 4 * sizeof(T));
    m_elements[3] = static_cast<T>(1.0);
  }

  // ------------------------------------------------------------------------------

  Quat(T _x, T _y, T _z, T _w)
  {
    m_elements[0] = _x;
    m_elements[1] = _y;
    m_elements[2] = _z;
    m_elements[3] = _w;
  }

  // ------------------------------------------------------------------------------

  explicit Quat(const Vec<T, 3>& _eulerAnglesInRadians)
  {
    const Vec<T, 3> c(Cos(_eulerAnglesInRadians[0] * static_cast<T>(0.5)),
                      Cos(_eulerAnglesInRadians[1] * static_cast<T>(0.5)),
                      Cos(_eulerAnglesInRadians[2] * static_cast<T>(0.5)));

    const Vec<T, 3> s(Sin(_eulerAnglesInRadians[0] * static_cast<T>(0.5)),
                      Sin(_eulerAnglesInRadians[1] * static_cast<T>(0.5)),
                      Sin(_eulerAnglesInRadians[2] * static_cast<T>(0.5)));

    m_elements[0] = s[0] * c[1] * c[2] - c[0] * s[1] * s[2];
    m_elements[1] = c[0] * s[1] * c[2] + s[0] * c[1] * s[2];
    m_elements[2] = c[0] * c[1] * s[2] - s[0] * s[1] * c[2];
    m_elements[3] = c[0] * c[1] * c[2] + s[0] * s[1] * s[2];
  }

  // ------------------------------------------------------------------------------

  explicit Quat(const Mat<T, 4>& _mat4)
  {
    T fourXSquaredMinus1 =
        _mat4[0 + 4 * 0] - _mat4[1 + 4 * 1] - _mat4[2 + 4 * 2];

    T fourYSquaredMinus1 =
        _mat4[1 + 4 * 1] - _mat4[0 + 4 * 0] - _mat4[2 + 4 * 2];

    T fourZSquaredMinus1 =
        _mat4[2 + 4 * 2] - _mat4[0 + 4 * 0] - _mat4[1 + 4 * 1];

    T fourWSquaredMinus1 =
        _mat4[0 + 4 * 0] + _mat4[1 + 4 * 1] + _mat4[2 + 4 * 2];

    std::int32_t biggestIndex = 0;

    T fourBiggestSquaredMinus1 = fourWSquaredMinus1;

    if (fourXSquaredMinus1 > fourBiggestSquaredMinus1)
    {
      fourBiggestSquaredMinus1 = fourXSquaredMinus1;
      biggestIndex = 1;
    }

    if (fourYSquaredMinus1 > fourBiggestSquaredMinus1)
    {
      fourBiggestSquaredMinus1 = fourYSquaredMinus1;
      biggestIndex = 2;
    }

    if (fourZSquaredMinus1 > fourBiggestSquaredMinus1)
    {
      fourBiggestSquaredMinus1 = fourZSquaredMinus1;
      biggestIndex = 3;
    }

    T biggestVal = Sqrt(fourBiggestSquaredMinus1 + static_cast<T>(1.0)) *
                   static_cast<T>(0.5);
    T mult = static_cast<T>(0.25) / biggestVal;

    switch (biggestIndex)
    {
      case 0:
        m_elements[3] = biggestVal;
        m_elements[0] = (_mat4[1 + 4 * 2] - _mat4[2 + 4 * 1]) * mult;
        m_elements[1] = (_mat4[2 + 4 * 0] - _mat4[0 + 4 * 2]) * mult;
        m_elements[2] = (_mat4[0 + 4 * 1] - _mat4[1 + 4 * 0]) * mult;
        break;
      case 1:
        m_elements[3] = (_mat4[1 + 4 * 2] - _mat4[2 + 4 * 1]) * mult;
        m_elements[0] = biggestVal;
        m_elements[1] = (_mat4[0 + 4 * 1] + _mat4[1 + 4 * 0]) * mult;
        m_elements[2] = (_mat4[2 + 4 * 0] + _mat4[0 + 4 * 2]) * mult;
        break;
      case 2:
        m_elements[3] = (_mat4[2 + 4 * 0] - _mat4[0 + 4 * 2]) * mult;
        m_elements[0] = (_mat4[0 + 4 * 1] + _mat4[1 + 4 * 0]) * mult;
        m_elements[1] = biggestVal;
        m_elements[2] = (_mat4[1 + 4 * 2] + _mat4[2 + 4 * 1]) * mult;
        break;
      case 3:
        m_elements[3] = (_mat4[0 + 4 * 1] - _mat4[1 + 4 * 0]) * mult;
        m_elements[0] = (_mat4[2 + 4 * 0] + _mat4[0 + 4 * 2]) * mult;
        m_elements[1] = (_mat4[1 + 4 * 2] + _mat4[2 + 4 * 1]) * mult;
        m_elements[2] = biggestVal;
        break;
    }
  }

  // ------------------------------------------------------------------------------

  static Quat GenRotation(const Vec<T, 3>& _origin, const Vec<T, 3>& _dest)
  {
    const T cosHalfAngleX2 = Sqrt(
        (static_cast<T>(2.0) * (static_cast<T>(1.0) + _origin.Dot(_dest))));

    const T recipCosHalfAngleX2 = (static_cast<T>(1.0) / cosHalfAngleX2);

    const Vec<T, 3> axisOfRotation =
        Cross(_origin, _dest) * recipCosHalfAngleX2;

    const T cosAmountOfRotation = cosHalfAngleX2 * static_cast<T>(0.5);

    return Quat(axisOfRotation[0], axisOfRotation[1], axisOfRotation[2],
                cosAmountOfRotation);
  }

  // ------------------------------------------------------------------------------

  static Quat GenRotation(T _radians, const Vec<T, 3>& _unitVec)
  {
    const T angle = _radians * static_cast<T>(0.5);
    const Vec<T, 3> axisOfRotation = _unitVec * Sin(angle);
    const T cosAmountOfRotation = Cos(angle);

    return Quat(axisOfRotation[0], axisOfRotation[1], axisOfRotation[2],
                cosAmountOfRotation);
  }

  // ------------------------------------------------------------------------------

  static Quat GenRotationX(T _radians)
  {
    const T angle = _radians * static_cast<T>(0.5);
    return Quat(Sin(angle), static_cast<T>(0.0), static_cast<T>(0.0),
                Cos(angle));
  }

  // ------------------------------------------------------------------------------

  static Quat GenRotationY(T _radians)
  {
    const T angle = _radians * static_cast<T>(0.5);
    return Quat(static_cast<T>(0.0), Sin(angle), static_cast<T>(0.0),
                Cos(angle));
  }

  // ------------------------------------------------------------------------------

  static Quat GenRotationZ(T _radians)
  {
    const T angle = _radians * static_cast<T>(0.5);
    return Quat(static_cast<T>(0.0), static_cast<T>(0.0), Sin(angle),
                Cos(angle));
  }

  // ------------------------------------------------------------------------------

  static Vec<T, 3> RotateVec(const Quat& _quat, const Vec<T, 3>& _vec)
  {
    // const Vec<T, 3> axesOfRotation(_quat.m_elements[0], _quat.m_elements[1],
    //                                _quat.m_elements[2]);
    // const Vec<T, 3> uv(Cross(axesOfRotation, _vec));
    // const Vec<T, 3> uuv(Cross(axesOfRotation, uv));

    // return _vec + ((uv * _quat.m_elements[3]) + uuv) * static_cast<T>(2.0);

    const float tmpX =
        (((_quat[3] * _vec[0]) + (_quat[1] * _vec[2])) - (_quat[2] * _vec[1]));
    const float tmpY =
        (((_quat[3] * _vec[1]) + (_quat[2] * _vec[0])) - (_quat[0] * _vec[2]));
    const float tmpZ =
        (((_quat[3] * _vec[2]) + (_quat[0] * _vec[1])) - (_quat[1] * _vec[0]));
    const float tmpW =
        (((_quat[0] * _vec[0]) + (_quat[1] * _vec[1])) + (_quat[2] * _vec[2]));

    return Vec<T, 3>(
        ((((tmpW * _quat[0]) + (tmpX * _quat[3])) - (tmpY * _quat[2])) +
         (tmpZ * _quat[1])),
        ((((tmpW * _quat[1]) + (tmpY * _quat[3])) - (tmpZ * _quat[0])) +
         (tmpX * _quat[2])),
        ((((tmpW * _quat[2]) + (tmpZ * _quat[3])) - (tmpX * _quat[1])) +
         (tmpY * _quat[0])));
  }

  // ------------------------------------------------------------------------------

  Quat operator+(const Quat& _rhs) const
  {
    return Quat(
        m_elements[0] + _rhs.m_elements[0], m_elements[1] + _rhs.m_elements[1],
        m_elements[2] + _rhs.m_elements[2], m_elements[3] + _rhs.m_elements[3]);
  }

  // ------------------------------------------------------------------------------

  Quat operator-(const Quat& _rhs) const
  {
    return Quat(
        m_elements[0] - _rhs.m_elements[0], m_elements[1] - _rhs.m_elements[1],
        m_elements[2] - _rhs.m_elements[2], m_elements[3] - _rhs.m_elements[3]);
  }

  // ------------------------------------------------------------------------------

  Quat operator*(const Quat& _rhs) const
  {
    return Quat((((m_elements[3] * _rhs.m_elements[0]) +
                  (m_elements[0] * _rhs.m_elements[3])) +
                 (m_elements[1] * _rhs.m_elements[2])) -
                    (m_elements[2] * _rhs.m_elements[1]),

                (((m_elements[3] * _rhs.m_elements[1]) +
                  (m_elements[1] * _rhs.m_elements[3])) +
                 (m_elements[2] * _rhs.m_elements[0])) -
                    (m_elements[0] * _rhs.m_elements[2]),

                (((m_elements[3] * _rhs.m_elements[2]) +
                  (m_elements[2] * _rhs.m_elements[3])) +
                 (m_elements[0] * _rhs.m_elements[1])) -
                    (m_elements[1] * _rhs.m_elements[0]),

                (((m_elements[3] * _rhs.m_elements[3]) -
                  (m_elements[0] * _rhs.m_elements[0])) -
                 (m_elements[1] * _rhs.m_elements[1])) -
                    (m_elements[2] * _rhs.m_elements[2]))
        .GetNormalized();
  }

  // ------------------------------------------------------------------------------

  Quat operator*(T _rhs) const
  {
    return Quat(m_elements[0] * _rhs, m_elements[1] * _rhs,
                m_elements[2] * _rhs, m_elements[3] * _rhs);
  }

  // ------------------------------------------------------------------------------

  Quat operator/(T _rhs) const
  {
    return Quat(m_elements[0] / _rhs, m_elements[1] / _rhs,
                m_elements[2] / _rhs, m_elements[3] / _rhs);
  }

  // ------------------------------------------------------------------------------

  Quat operator-() const
  {
    return Quat(-m_elements[0], -m_elements[1], -m_elements[2], -m_elements[3]);
  }

  // ------------------------------------------------------------------------------

  Quat& operator+=(const Quat& _rhs)
  {
    *this = *this + _rhs;
    return *this;
  }

  // ------------------------------------------------------------------------------

  Quat& operator-=(const Quat& _rhs)
  {
    *this = *this - _rhs;
    return *this;
  }

  // ------------------------------------------------------------------------------

  Quat& operator*=(const Quat& _rhs)
  {
    *this = *this * _rhs;
    return *this;
  }

  // ------------------------------------------------------------------------------

  Quat& operator*=(T _rhs)
  {
    *this = *this * _rhs;
    return *this;
  }

  // ------------------------------------------------------------------------------

  Quat& operator/=(T _rhs)
  {
    *this = *this / _rhs;
    return *this;
  }

  // ------------------------------------------------------------------------------

  bool operator==(const Quat& _rhs) const
  {
    bool allElementsAreEqual = true;

    for (auto i = 0; i < 4; i++)
    {
      allElementsAreEqual &=
          Equals(m_elements[i], _rhs.m_elements[i], c_epsilon<T>);
    }

    return allElementsAreEqual;
  }

  // ------------------------------------------------------------------------------

  bool operator!=(const Quat& _rhs) const { return !operator==(_rhs); }

  // ------------------------------------------------------------------------------

  T& operator[](std::uint32_t _index)
  {
    assert(_index < 4);
    return m_elements[_index];
  }

  // ------------------------------------------------------------------------------

  T operator[](std::uint32_t _index) const
  {
    assert(_index < 4);
    return m_elements[_index];
  }

  // ------------------------------------------------------------------------------

  Vec<T, 3> GetAxis() const
  {
    const T temp1 = static_cast<T>(1.0) - m_elements[3] * m_elements[3];

    if (Abs(m_elements[0]) < c_epsilon<T>) // Divide by zero safety check
    {
      // default axis = z
      return Vec<T, 3>(static_cast<T>(0.0), static_cast<T>(0.0),
                       static_cast<T>(1.0));
    }

    const T temp2 = Sqrt(static_cast<T>(1.0) / temp1);
    return Vec<T, 3>(m_elements[0] * temp2, m_elements[1] * temp2,
                     m_elements[2] * temp2);
  }

  // ------------------------------------------------------------------------------

  T GetPitchRad() const
  {
    return ATan2(static_cast<T>(2.0) * (m_elements[1] * m_elements[2] +
                                        m_elements[3] * m_elements[0]),
                 m_elements[3] * m_elements[3] - m_elements[0] * m_elements[0] -
                     m_elements[1] * m_elements[1] +
                     m_elements[2] * m_elements[2]);
  }

  // ------------------------------------------------------------------------------

  T GetYawRad() const
  {
    return ASin(Clamp(static_cast<T>(-2.0) * (m_elements[0] * m_elements[2] -
                                              m_elements[3] * m_elements[1]),
                      static_cast<T>(-1.0), static_cast<T>(1.0)));
  }

  // ------------------------------------------------------------------------------

  T GetRollRad() const
  {
    return ATan2(static_cast<T>(2.0) * (m_elements[0] * m_elements[1] +
                                        m_elements[3] * m_elements[2]),
                 m_elements[3] * m_elements[3] + m_elements[0] * m_elements[0] -
                     m_elements[1] * m_elements[1] -
                     m_elements[2] * m_elements[2]);
  }

  // ------------------------------------------------------------------------------

  Vec<T, 3> ToEulerAngles() const
  {
    return Vec<T, 3>(GetPitchRad(), GetYawRad(), GetRollRad());
  }

  // ------------------------------------------------------------------------------

  Mat<T, 4> ToMat4() const
  {
    Mat<T, 4> rtn;

    Quat normalized = GetNormalized();

    T xx = normalized.m_elements[0] * normalized.m_elements[0];
    T yy = normalized.m_elements[1] * normalized.m_elements[1];
    T zz = normalized.m_elements[2] * normalized.m_elements[2];
    T ww = normalized.m_elements[3] * normalized.m_elements[3];

    rtn[0] = (xx - yy - zz + ww);
    rtn[5] = (-xx + yy - zz + ww);
    rtn[10] = (-xx - yy + zz + ww);

    T tmp1 = normalized.m_elements[0] * normalized.m_elements[1];
    T tmp2 = normalized.m_elements[2] * normalized.m_elements[3];
    rtn[4] = static_cast<T>(2.0) * (tmp1 + tmp2);
    rtn[1] = static_cast<T>(2.0) * (tmp1 - tmp2);

    tmp1 = normalized.m_elements[0] * normalized.m_elements[2];
    tmp2 = normalized.m_elements[1] * normalized.m_elements[3];
    rtn[8] = static_cast<T>(2.0) * (tmp1 - tmp2);
    rtn[2] = static_cast<T>(2.0) * (tmp1 + tmp2);

    tmp1 = normalized.m_elements[1] * normalized.m_elements[2];
    tmp2 = normalized.m_elements[0] * normalized.m_elements[3];
    rtn[1 + 2 * 4] = static_cast<T>(2.0) * (tmp1 + tmp2);
    rtn[2 + 1 * 4] = static_cast<T>(2.0) * (tmp1 - tmp2);
    rtn[3 + 3 * 4] = static_cast<T>(1.0);

    return rtn;
  }

  // ------------------------------------------------------------------------------

  T Dot(const Quat& _other) const
  {
    return m_elements[0] * _other.m_elements[0] +
           m_elements[1] * _other.m_elements[1] +
           m_elements[2] * _other.m_elements[2] +
           m_elements[3] * _other.m_elements[3];
  }

  // ------------------------------------------------------------------------------

  T GetMagnitude() const { return Sqrt(GetSquaredMagnitude()); }

  // ------------------------------------------------------------------------------

  T GetSquaredMagnitude() const
  {
    return m_elements[0] * m_elements[0] + m_elements[1] * m_elements[1] +
           m_elements[2] * m_elements[2] + m_elements[3] * m_elements[3];
  }

  // ------------------------------------------------------------------------------

  Quat GetNormalized() const
  {
    const T inverseMagnitude =
        Sqrt(static_cast<T>(1.0) / GetSquaredMagnitude());
    return (*this * inverseMagnitude);
  }

  // ------------------------------------------------------------------------------

  Quat GetConjugated() const
  {
    return Quat(-m_elements[0], -m_elements[1], -m_elements[2], m_elements[3]);
  }

  // ------------------------------------------------------------------------------

  Quat GetInversed() const
  {
    const Quat conjugated = GetConjugated();
    const T sqrLen = GetSquaredMagnitude();
    return Quat(conjugated / sqrLen);
  }

  // ------------------------------------------------------------------------------

  friend std::ostream& operator<<(std::ostream& _outStream, const Quat& _quat)
  {
    _outStream << "Quat: { ";

    for (auto i = 0; i < 4; i++)
    {
      _outStream << _quat.m_elements[i] << ", ";
    }

    _outStream << '}';
    return _outStream;
  }

  // ------------------------------------------------------------------------------

private:
  // [x, y, z, w]
  // [xyz = axes of rotation, w = cosine of amount of rotation]
  T m_elements[4];
};

// ------------------------------------------------------------------------------

using Quatf = Quat<float>;
using Quatd = Quat<double>;

} // namespace math
} // namespace mage