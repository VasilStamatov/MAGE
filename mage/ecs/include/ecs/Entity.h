#pragma once

#include <cstdint>

namespace mage
{
namespace ecs
{

// ------------------------------------------------------------------------------

struct Entity
{
  explicit Entity(std::int32_t _id);

  // ------------------------------------------------------------------------------

  bool operator==(const Entity& _other) const noexcept;

  // ------------------------------------------------------------------------------

  bool operator!=(const Entity& _other) const noexcept;

  // ------------------------------------------------------------------------------

  std::int32_t m_id;
};

// ------------------------------------------------------------------------------

} // namespace ecs
} // namespace mage