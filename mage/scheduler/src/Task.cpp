#include "scheduler/Task.h"

namespace mage
{
namespace scheduler
{

// ------------------------------------------------------------------------------

TrackedTask::TrackedTask(std::unique_ptr<Task> _internalTask)
    : m_internalTask(std::move(_internalTask))
    , m_isComplete()
{
}

// ------------------------------------------------------------------------------

void TrackedTask::Execute()
{
  m_internalTask->Execute();
  m_isComplete.set_value(true);
}

// ------------------------------------------------------------------------------

std::future<bool> TrackedTask::GetFuture() { return m_isComplete.get_future(); }

// ------------------------------------------------------------------------------

} // namespace scheduler
} // namespace mage