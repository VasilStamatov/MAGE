#pragma once

#include "ParallelForSplitters.h"
#include "Scheduler.h"

#include <cstdint>

namespace mage
{
namespace scheduler
{

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// Data that the parralel for task uses
/////////////////////////////////////////////////
template <typename T, typename S> struct ParralelForTaskData
{
  using DataType = T;
  using SplitterType = S;

  ParralelForTaskData(DataType* _data, std::uint32_t _count,
                      void (*_function)(DataType*, std::uint32_t),
                      const SplitterType& _splitter)
      : m_function(_function)
      , m_data(_data)
      , m_count(_count)
      , m_splitter(_splitter)
  {
  }

  void (*m_function)(DataType*, std::uint32_t);
  DataType* m_data;
  std::uint32_t m_count;
  SplitterType m_splitter;
};

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// The parralel for task function, which splits the passed data until it
/// doesn't meet the split requirements and  then executes all the leaves
/// example of splitting 5 elements into loops of 2 (or lower)
///       *  - 5 elements
///      / \
///     *   * - 3/2 elements (execute 2)
///    / \  
///   *   *    - 2/1 (execute 2 and 1)
/////////////////////////////////////////////////
template <typename TaskData>
void ParallelForTask(Task* _task, const void* _taskData)
{
  const TaskData* data = static_cast<const TaskData*>(_taskData);
  const TaskData::SplitterType& splitter = data->m_splitter;

  if (splitter.Split<TaskData::DataType>(data->m_count))
  {
    // Left side
    const std::uint32_t leftCount = data->m_count / 2u;
    const TaskData leftData(data->m_data, leftCount, data->m_function,
                            splitter);

    Task* left = scheduler::CreateChildTask(_task, ParallelForTask<TaskData>,
                                            &leftData, sizeof(leftData));
    scheduler::Run(left);

    // Right side
    const std::uint32_t rightCount = data->m_count - leftCount;
    const TaskData rightData(data->m_data + leftCount, rightCount,
                             data->m_function, splitter);
    Task* right = scheduler::CreateChildTask(_task, ParallelForTask<TaskData>,
                                             &rightData, sizeof(rightData));
    scheduler::Run(right);
  }
  else
  {
    (data->m_function)(data->m_data, data->m_count);
  }
}

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// Executes a task which splits the passed data based on the splitter and once
/// it reaches the maximum amount of splits it can, it executes the leaves
/////////////////////////////////////////////////
template <typename DataType, typename SplitterType>
Task* ParralelFor(DataType* _data, std::uint32_t _count,
                  void (*_function)(DataType*, std::uint32_t),
                  const SplitterType& _splitter)
{
  using TaskData = ParralelForTaskData<DataType, SplitterType>;

  const TaskData taskData(_data, _count, _function, _splitter);

  Task* task = scheduler::CreateTask(ParallelForTask<TaskData>, &taskData,
                                     sizeof(taskData));
  return task;
}

// ------------------------------------------------------------------------------

} // namespace scheduler
} // namespace mage