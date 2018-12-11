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

class WorkStealingQueue
{
public:
  WorkStealingQueue();

  void Push(Task* _task);
  Task* Pop();
  Task* Steal();

private:
  Task* m_tasks[c_numberOfTasks];
  std::mutex m_mutex;
  std::uint32_t m_bottom;
  std::uint32_t m_top;
};

// ------------------------------------------------------------------------------

} // namespace scheduler
} // namespace mage