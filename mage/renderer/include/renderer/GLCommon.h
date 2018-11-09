#pragma once

#include <assert.h>
#include <cstdint>

namespace mage
{
namespace renderer
{

// ------------------------------------------------------------------------------

extern void GLClearError();
extern bool GLLogCall(const char* _function, const char* _file, int _line);

// ------------------------------------------------------------------------------

#ifdef NDEBUG
#define GLCall(expr) expr
#else
#define GLCall(expr)                                                           \
  GLClearError();                                                              \
  expr;                                                                        \
  assert(GLLogCall(#expr, __FILE__, __LINE__))
#endif

// ------------------------------------------------------------------------------

} // namespace renderer
} // namespace mage