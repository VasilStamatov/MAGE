#include "scheduler/Task.h"

namespace mage
{
namespace scheduler
{

// ------------------------------------------------------------------------------

constexpr int sizeOfTask = sizeof(Task);

static_assert(sizeOfTask == 64, "Task must be 64 bytes to avoid false sharing");

// ------------------------------------------------------------------------------

} // namespace scheduler
} // namespace mage