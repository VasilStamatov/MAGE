#pragma once

#include <assert.h>
#include <cstdint>

namespace mage
{
namespace graphics
{

// ------------------------------------------------------------------------------

std::uint32_t GLCheckError();
bool GLLogCall(const char* _function, const char* _file, int _line);

// ------------------------------------------------------------------------------

#ifdef NDEBUG
#define GLCall(expr) expr
#else
#define GLCall(expr)                                                           \
  GLCheckError();                                                              \
  expr;                                                                        \
  assert(GLLogCall(#expr, __FILE__, __LINE__))
#endif

// ------------------------------------------------------------------------------

} // namespace graphics
} // namespace mage