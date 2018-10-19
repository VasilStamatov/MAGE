#include "ecs/Component.h"

#include <assert.h>

namespace mage
{
namespace ecs
{

std::int32_t internal::GenerateUniqueComponentId() noexcept
{
  static std::int32_t s_uniqueComponentIdCounter = 0;
  assert(s_uniqueComponentIdCounter < c_maxNumberOfComponentTypes - 1);
  return s_uniqueComponentIdCounter++;
}

} // namespace ecs
} // namespace mage