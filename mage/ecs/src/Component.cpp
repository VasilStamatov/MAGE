#include "ecs/Component.h"

namespace mage
{
namespace ecs
{

std::uint32_t internal::GenerateUniqueComponentId()
{
    static std::uint32_t s_uniqueComponentIdCounter = 0;
    return s_uniqueComponentIdCounter++;
}

} // namespace ecs
} // namespace mage