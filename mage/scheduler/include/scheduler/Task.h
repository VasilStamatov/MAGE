#pragma once

#include <atomic>

namespace mage
{
namespace scheduler
{

struct Task;

typedef void (*TaskFunction)(Task*, const void*);

constexpr int c_spaceForTaskData =
    64 - (sizeof(TaskFunction) + sizeof(Task*) + sizeof(std::atomic_int32_t));

// ------------------------------------------------------------------------------

struct Task
{
  Task* m_parent;
  TaskFunction m_function;
  std::atomic_int32_t m_unfinishedTasks;
  char m_data[c_spaceForTaskData]; ///< bytes to pad the struct to 64 bytes;
                                   ///< This is also used to store data for the
                                   ///< task. If it's under c_spaceForTaskData
                                   ///< bytes then it can be stored in place,
                                   ///< otherwise it can contain pointers to the
                                   ///< data on the heap.
};

// ------------------------------------------------------------------------------

} // namespace scheduler
} // namespace mage