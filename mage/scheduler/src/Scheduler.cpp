#include "scheduler/Scheduler.h"

#include "scheduler/WorkStealingQueue.h"
#include "util/RandomNumberGenerator.h"

#include <cassert>
#include <thread>
#include <unordered_map>
#include <vector>

namespace mage
{
namespace scheduler
{

// ------------------------------------------------------------------------------

static constexpr std::int32_t c_maxTaskCount = 1024;

static thread_local Task
    s_taskAllocator[c_maxTaskCount]; ///< ring buffer of tasks for each thread

static thread_local std::uint32_t s_allocatedTasksCount =
    0u; ///< counter to keep count of the number of total allocated tasks

static std::vector<std::unique_ptr<std::thread>> s_threads;
static std::vector<std::unique_ptr<WorkStealingQueue>> s_taskQueues;
static std::unordered_map<std::thread::id, std::uint32_t> s_threadIdToIndex;

static std::atomic_bool s_isShuttingDown;
static std::uint32_t s_workerThreadCount = 0u;
static util::RandomNumberGenerator s_rng;

// ------------------------------------------------------------------------------

WorkStealingQueue* GetWorkerThreadQueue()
{
  auto threadId = std::this_thread::get_id();
  auto index = s_threadIdToIndex[threadId];
  return s_taskQueues[index].get();
}

// ------------------------------------------------------------------------------

Task* AllocateTask()
{
  // Get a task specific for a thread (uses only thread-local vars)
  const std::uint32_t index = s_allocatedTasksCount++;

  // Warning: if more than c_maxTaskCount tasks are allocated in 1 frame, then
  // it's possible that the first task may not have finished and will be
  // overwritten.
  return &s_taskAllocator[index & (c_maxTaskCount - 1)];
}

// ------------------------------------------------------------------------------

bool HasTaskCompleted(const Task* _task)
{
  return _task->m_unfinishedTasks == 0;
}

// ------------------------------------------------------------------------------

Task* GetTask()
{
  WorkStealingQueue* queue = GetWorkerThreadQueue();

  if (queue == nullptr)
  {
    return nullptr;
  }

  Task* task = queue->Pop();

  // Check to see if a task was found
  if (task == nullptr)
  {
    // Task queue empty, try stealing from some other queue

    // Get a task queue index [0; threadCount]. 0 to threadCount includes the
    // main thread, because the max number is included (eg 0 to 7 for 8 threads)
    std::uint32_t randomIndex =
        s_rng.GenRandInt<std::uint32_t>(0, s_taskQueues.size() - 1);

    WorkStealingQueue* stealQueue = s_taskQueues[randomIndex].get();

    if (stealQueue == queue)
    {
      // don't try to steal from ourselves
      std::this_thread::yield();
      return nullptr;
    }

    // Try to steal a job from the random queue
    Task* stolenTask = stealQueue->Steal();

    if (stolenTask == nullptr)
    {
      // we couldn't steal a job from the other queue either, so we just yield
      // our time slice for now
      std::this_thread::yield();
      return nullptr;
    }

    return stolenTask;
  }

  return task;
}

// ------------------------------------------------------------------------------

void Finish(Task* _task)
{
  --_task->m_unfinishedTasks;

  if ((_task->m_unfinishedTasks == 0) && (_task->m_parent))
  {
    Finish(_task->m_parent);
  }
}

// ------------------------------------------------------------------------------

void Execute(Task* _task)
{
  (_task->m_function)(_task, _task->m_data);
  Finish(_task);
}

// ------------------------------------------------------------------------------

void WorkerThreadMain()
{
  while (!s_isShuttingDown)
  {
    Task* task = GetTask();
    if (task)
    {
      Execute(task);
    }
  }
}

// ------------------------------------------------------------------------------

void Initialize()
{
  s_isShuttingDown.store(false);

  // Fetch the number of supported threads and subtract 1, which is the main
  // thread.
  s_workerThreadCount = std::thread::hardware_concurrency() - 1;
  s_threads.reserve(s_workerThreadCount);
  s_taskQueues.reserve(s_workerThreadCount + 1);
  s_threadIdToIndex.reserve(s_workerThreadCount + 1);

  // Add the worker queue for the main thread
  s_taskQueues.emplace_back(std::make_unique<WorkStealingQueue>());
  s_threadIdToIndex[std::this_thread::get_id()] = 0;

  // Instantiate threads count - 1, because the main thread is already running
  for (size_t i = 0; i < s_workerThreadCount; i++)
  {
    s_threads.emplace_back(std::make_unique<std::thread>(WorkerThreadMain));
    s_taskQueues.emplace_back(std::make_unique<WorkStealingQueue>());
    s_threadIdToIndex[s_threads.back()->get_id()] = i + 1;
  }
}

// ------------------------------------------------------------------------------

void Shutdown()
{
  // set shutdown to true
  s_isShuttingDown.store(true);

  // // notify all sleeping threads so they can break out of processing
  // s_conditionToAwake.notify_all();

  // join the threads to not crash
  for (auto&& thread : s_threads)
  {
    thread->join();
  }
}

// ------------------------------------------------------------------------------

Task* CreateTask(TaskFunction _function)
{
  Task* task = AllocateTask();

  task->m_function = _function;
  task->m_parent = nullptr;
  task->m_unfinishedTasks = 1;

  return task;
}

// ------------------------------------------------------------------------------

Task* CreateTask(TaskFunction _function, const void* _taskData,
                 size_t _taskDataSize)
{
  assert(_taskDataSize <= c_spaceForTaskData);

  Task* task = AllocateTask();

  task->m_function = _function;
  task->m_parent = nullptr;
  task->m_unfinishedTasks = 1;

  std::memcpy(task->m_data, _taskData, _taskDataSize);

  return task;
}

// ------------------------------------------------------------------------------

Task* CreateChildTask(Task* _parent, TaskFunction _function)
{
  ++_parent->m_unfinishedTasks;

  Task* task = AllocateTask();

  task->m_function = _function;
  task->m_parent = _parent;
  task->m_unfinishedTasks = 1;

  return task;
}

// ------------------------------------------------------------------------------

Task* CreateChildTask(Task* _parent, TaskFunction _function,
                      const void* _taskData, size_t _taskDataSize)
{
  assert(_taskDataSize <= c_spaceForTaskData);

  ++_parent->m_unfinishedTasks;

  Task* task = AllocateTask();

  task->m_function = _function;
  task->m_parent = _parent;
  task->m_unfinishedTasks = 1;

  std::memcpy(task->m_data, _taskData, _taskDataSize);

  return task;
}

// ------------------------------------------------------------------------------

void Run(Task* _task)
{
  if (WorkStealingQueue* queue = GetWorkerThreadQueue())
  {
    queue->Push(_task);
  }
}

// ------------------------------------------------------------------------------

void Wait(const Task* _task)
{
  // wait until the job has completed. in the meantime, work on any other job.
  while (!HasTaskCompleted(_task))
  {
    Task* nextTask = GetTask();
    if (nextTask)
    {
      Execute(nextTask);
    }
  }
}

// ------------------------------------------------------------------------------

} // namespace scheduler
} // namespace mage