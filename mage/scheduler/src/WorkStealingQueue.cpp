#include "scheduler/WorkStealingQueue.h"

namespace mage
{
namespace scheduler
{

// ------------------------------------------------------------------------------

WorkStealingQueue::WorkStealingQueue()
    : m_tasks()
    , m_mutex()
    , m_bottom(0u)
    , m_top(0u)
{
}

// ------------------------------------------------------------------------------

void WorkStealingQueue::Push(Task* _task)
{
  std::lock_guard<std::mutex> lock(m_mutex);

  m_tasks[m_bottom & c_mask] = _task;
  ++m_bottom;
}

// ------------------------------------------------------------------------------

Task* WorkStealingQueue::Pop()
{
  std::lock_guard<std::mutex> lock(m_mutex);

  const int taskCount = m_bottom - m_top;

  if (taskCount <= 0)
  {
    // No tasks in queue
    return nullptr;
  }

  --m_bottom;
  return m_tasks[m_bottom & c_mask];
}

// ------------------------------------------------------------------------------

Task* WorkStealingQueue::Steal()
{
  std::lock_guard<std::mutex> lock(m_mutex);

  const int taskCount = m_bottom - m_top;

  if (taskCount <= 0)
  {
    // No tasks in queue
    return nullptr;
  }

  Task* task = m_tasks[m_top & c_mask];
  ++m_top;
  return task;
}

// ------------------------------------------------------------------------------

} // namespace scheduler
} // namespace mage