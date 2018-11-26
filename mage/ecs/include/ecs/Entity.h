#pragma once

#include <cstdint>

namespace mage
{
namespace ecs
{

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// An Entity is just an Id which maps to different components it owns.
/////////////////////////////////////////////////
struct Entity
{
  explicit Entity(std::int32_t _id);

  bool operator==(const Entity& _other) const noexcept;
  bool operator!=(const Entity& _other) const noexcept;

  std::int32_t m_id;
};

// ------------------------------------------------------------------------------

} // namespace ecs
} // namespace mage