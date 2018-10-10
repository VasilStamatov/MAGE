#include "../include/ecs/Component.h"

namespace mage
{
namespace ecs
{

std::uint32_t internal::GenerateUniqueComponentId()
{
    static std::uint32_t s_UniqueComponentIdCounter = 0;
    return s_UniqueComponentIdCounter++;
}

} // namespace ecs
} // namespace mage