#pragma once

#include <cmath>
#include <cstdint>
#include <limits>

namespace mage
{
namespace math
{

// ------------------------------------------------------------------------------

template <typename T> constexpr inline T c_pi = 3.1415926535897932;
template <typename T> constexpr inline T c_twoPi = 6.28318530717959;
template <typename T> constexpr inline T c_halfPi = 1.57079632679;
template <typename T> constexpr inline T c_reciprocalPi = 0.31830988618;
template <typename T> constexpr inline T c_reciprocalTwoPi = 0.159154943091895;
template <typename T> constexpr inline T c_reciprocalHalfPi = 0.636619772367581;

template <typename T>
constexpr inline T c_eulersNumber = 2.71828182845904523536f;
template <typename T> constexpr inline T c_log2E = 1.44269504088896;
template <typename T>
constexpr inline T c_radToDeg = 57.2957795130823; // 180.0f/PI;
template <typename T>
constexpr inline T c_degToRad = 0.0174532925199433; // PI/180.0f;
template <typename T>
constexpr inline T c_epsilon = std::numeric_limits<T>::epsilon();

// ------------------------------------------------------------------------------

template <typename T> inline T Floor(T _val)
{
  static_assert(false, "Unsupported type");
}

template <> inline float Floor(float _val) { return std::floorf(_val); }
template <> inline double Floor(double _val) { return std::floor(_val); }
template <> inline long double Floor(long double _val)
{
  return std::floorl(_val);
}

// ------------------------------------------------------------------------------

template <typename T> inline T Ceil(T _val)
{
  static_assert(false, "Unsupported type");
}

template <> inline float Ceil(float _val) { return std::ceilf(_val); }
template <> inline double Ceil(double _val) { return std::ceil(_val); }
template <> inline long double Ceil(long double _val)
{
  return std::ceill(_val);
}

// ------------------------------------------------------------------------------

template <typename T> inline T Exp(T _val)
{
  static_assert(false, "Unsupported type");
}
template <> inline float Exp(float _val) { return std::expf(_val); }
template <> inline double Exp(double _val) { return std::exp(_val); }
template <> inline long double Exp(long double _val) { return std::expl(_val); }

// ------------------------------------------------------------------------------

template <typename T> inline T Log(T _val)
{
  static_assert(false, "Unsupported type");
}
template <> inline float Log(float _val) { return std::logf(_val); }
template <> inline double Log(double _val) { return std::log(_val); }
template <> inline long double Log(long double _val) { return std::logl(_val); }

// ------------------------------------------------------------------------------

template <typename T> inline T Logx(T _val, T _base)
{
  return Log(_val) / Log(base);
}

// ------------------------------------------------------------------------------

template <typename T> inline T Log2(T _val) { return Log(_val) * c_log2E<T>; }

// ------------------------------------------------------------------------------

template <typename T> inline T Fmod(T _num, T _den)
{
  static_assert(false, "Unsupported type");
}
template <> inline float Fmod(float _num, float _den)
{
  return std::fmodf(_num, _den);
}
template <> inline double Fmod(double _num, double _den)
{
  return std::fmod(_num, _den);
}
template <> inline long double Fmod(long double _num, long double _den)
{
  return std::fmodl(_num, _den);
}

// ------------------------------------------------------------------------------

template <typename T> inline T Sin(T _val)
{
  static_assert(false, "Unsupported type");
}
template <> inline float Sin(float _val) { return std::sinf(_val); }
template <> inline double Sin(double _val) { return std::sin(_val); }
template <> inline long double Sin(long double _val) { return std::sinl(_val); }

// ------------------------------------------------------------------------------

template <typename T> inline T ASin(T _val)
{
  static_assert(false, "Unsupported type");
}
template <> inline float ASin(float _val) { return std::asinf(_val); }
template <> inline double ASin(double _val) { return std::asin(_val); }
template <> inline long double ASin(long double _val)
{
  return std::asinl(_val);
}

// ------------------------------------------------------------------------------

template <typename T> inline T Cos(T _val)
{
  static_assert(false, "Unsupported type");
}
template <> inline float Cos(float _val) { return std::cosf(_val); }
template <> inline double Cos(double _val) { return std::cos(_val); }
template <> inline long double Cos(long double _val) { return std::cosl(_val); }

// ------------------------------------------------------------------------------

template <typename T> inline T ACos(T _val)
{
  static_assert(false, "Unsupported type");
}
template <> inline float ACos(float _val) { return std::acosf(_val); }
template <> inline double ACos(double _val) { return std::acos(_val); }
template <> inline long double ACos(long double _val)
{
  return std::acosl(_val);
}

// ------------------------------------------------------------------------------

template <typename T> inline T Tan(T _val)
{
  static_assert(false, "Unsupported type");
}
template <> inline float Tan(float _val) { return std::tanf(_val); }
template <> inline double Tan(double _val) { return std::tan(_val); }
template <> inline long double Tan(long double _val) { return std::tanl(_val); }

// ------------------------------------------------------------------------------

template <typename T> inline T ATan(T _val)
{
  static_assert(false, "Unsupported type");
}
template <> inline float ATan(float _val) { return std::atanf(_val); }
template <> inline double ATan(double _val) { return std::atan(_val); }
template <> inline long double ATan(long double _val)
{
  return std::atanl(_val);
}

// ------------------------------------------------------------------------------

template <typename T> inline T ATan2(T _y, T _x)
{
  static_assert(false, "Unsupported type");
}
template <> inline float ATan2(float _y, float _x)
{
  return std::atan2f(_y, _x);
}
template <> inline double ATan2(double _y, double _x)
{
  return std::atan2(_y, _x);
}
template <> inline long double ATan2(long double _y, long double _x)
{
  return std::atan2l(_y, _x);
}

// ------------------------------------------------------------------------------

template <typename T> inline T Pow(T _val, T _pow)
{
  static_assert(false, "Unsupported type");
}
template <> inline float Pow(float _val, float _pow)
{
  return std::powf(_val, _pow);
}
template <> inline double Pow(double _val, double _pow)
{
  return std::pow(_val, _pow);
}
template <> inline long double Pow(long double _val, long double _pow)
{
  return std::powl(_val, _pow);
}

// ------------------------------------------------------------------------------

template <typename T> inline T Sqrt(T _val)
{
  static_assert(false, "Unsupported type");
}
template <> inline float Sqrt(float _val) { return std::sqrtf(_val); }
template <> inline double Sqrt(double _val) { return std::sqrt(_val); }
template <> inline long double Sqrt(long double _val)
{
  return std::sqrtl(_val);
}

// ------------------------------------------------------------------------------

inline bool IsPowerOfTwo(std::uint32_t _val)
{
  return (_val != 0u) && ((_val & (_val - 1u)) == 0u);
}

// ------------------------------------------------------------------------------

template <typename T> constexpr inline T Abs(const T& _val)
{
  return _val >= static_cast<T>(0) ? _val : -_val;
}

// ------------------------------------------------------------------------------

template <typename T> constexpr inline T Min(const T& _val1, const T& _val2)
{
  return _val1 <= _val2 ? _val1 : _val2;
}

// ------------------------------------------------------------------------------

template <typename T>
constexpr inline T Min3(const T& _val1, const T& _val2, const T& _val3)
{
  return Min(Min(_val1, _val2), _val3);
}

// ------------------------------------------------------------------------------

template <typename T> constexpr inline T Max(const T& _val1, const T& _val2)
{
  return _val1 >= _val2 ? _val1 : _val2;
}

// ------------------------------------------------------------------------------

template <typename T>
constexpr inline T Max3(const T& _val1, const T& _val2, const T& _val3)
{
  return Max(Max(_val1, _val2), _val3);
}

// ------------------------------------------------------------------------------

template <typename T> inline T ToDegrees(const T& _val)
{
  return _val * c_RadToDeg<T>;
}

// ------------------------------------------------------------------------------

template <typename T> inline T ToRadians(const T& _val)
{
  return _val * c_DegToRad<T>;
}

// ------------------------------------------------------------------------------

template <typename T, typename U>
inline T Lerp(const T& _src, const T& _dst, const U& _alpha)
{
  return static_cast<T>((_src * (static_cast<U>(1) - _alpha)) + _dst * _alpha);
}

// ------------------------------------------------------------------------------

template <typename T>
inline T Clamp(const T& _val, const T& _min, const T& _max)
{
  if (_val > _max)
  {
    return _max;
  }
  else if (_val > _min)
  {
    return _val;
  }
  else
  {
    return _min;
  }
}

// ------------------------------------------------------------------------------

template <typename T> inline T Square(const T& _val) { return _val * _val; }

// ------------------------------------------------------------------------------

template <typename T> inline T Cube(const T& _val)
{
  return _val * _val * _val;
}

// ------------------------------------------------------------------------------

template <typename T>
inline bool Equals(const T& _val1, const T& _val2, const T& _errorMargin)
{
  return Abs(_val1 - _val2) < _errorMargin;
}

// ------------------------------------------------------------------------------

} // namespace math
} // namespace mage