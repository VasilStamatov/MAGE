#pragma once

#include "Task.h"

#include <array>
#include <mutex>

namespace mage
{
namespace scheduler
{

// ------------------------------------------------------------------------------

constexpr std::uint32_t c_numberOfTasks = 1024u;
constexpr std::uint32_t c_mask = c_numberOfTasks - 1;

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// A work stealing queue/dequeue is responsible for storing tasks for a
/// specific thread in a ring buffer, and allowing that thread to pop and push
/// tasks from the back of the queue and also enable the ability to steal tasks
/// from the front of the queue so other threads can take on some work if
/// they're empty. These operations must be threadsafe.
/////////////////////////////////////////////////
class WorkStealingQueue
{
public:
  WorkStealingQueue();

  void Push(Task* _task); ///< push a task to the back
  Task* Pop();            ///< pop a task from the back
  Task* Steal();          ///< steal a task from the front

private:
  Task* m_tasks[c_numberOfTasks]; ///< ring buffer of tasks
  std::mutex m_mutex;             ///< mutex to keep the operation threadsafe
  std::uint32_t m_bottom;         ///< "index" to the back task
  std::uint32_t m_top;            ///< "index" to the front task
};

// ------------------------------------------------------------------------------

} // namespace scheduler
} // namespace mage