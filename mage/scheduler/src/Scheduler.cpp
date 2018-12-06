#include "scheduler/Scheduler.h"

#include <condition_variable>
#include <functional>
#include <queue>
#include <thread>
#include <vector>

namespace mage
{
namespace scheduler
{

// ------------------------------------------------------------------------------

static std::queue<std::unique_ptr<Task>> s_tasks;
static std::vector<std::unique_ptr<std::thread>> s_threads;
static std::condition_variable s_conditionToAwake;
static std::mutex s_mutex;
static std::atomic_bool s_isShuttingDown;

// ------------------------------------------------------------------------------

void Initialize()
{
  auto numberOfSupportedThreadsHint = std::thread::hardware_concurrency();
  s_threads.reserve(numberOfSupportedThreadsHint);

  for (size_t i = 0; i < numberOfSupportedThreadsHint; i++)
  {
    s_threads.emplace_back(Processor);
  }
}

// ------------------------------------------------------------------------------

void Shutdown()
{
  // set shutdown to true
  s_isShuttingDown.store(true);

  // notify all sleeping threads so they can break out of processing
  s_conditionToAwake.notify_all();

  // join the threads to not crash
  for (auto&& thread : s_threads)
  {
    thread->join();
  }
}

// ------------------------------------------------------------------------------

void Processor()
{
  while (true)
  {
    std::unique_ptr<Task> task = nullptr;

    {
      std::unique_lock<std::mutex> lock(s_mutex);

      s_conditionToAwake.wait(
          lock, [=] { return s_isShuttingDown || !s_tasks.empty(); });

      if (s_isShuttingDown && s_tasks.empty())
      {
        break;
      }

      task = std::move(s_tasks.front());
      s_tasks.pop();
    }

    if (task)
    {
      task->Execute();
    }
  }
}

// ------------------------------------------------------------------------------

void AddTask(std::unique_ptr<Task> _task)
{
  {
    std::lock_guard<std::mutex> lock(s_mutex);

    s_tasks.push(std::move(_task));
  }

  s_conditionToAwake.notify_one();
}

// ------------------------------------------------------------------------------

std::future<bool> AddTrackedTask(std::unique_ptr<Task> _task)
{
  std::unique_ptr<TrackedTask> wrapper =
      std::make_unique<TrackedTask>(std::move(_task));

  std::future<bool> status = wrapper->GetFuture();

  {
    std::lock_guard<std::mutex> lock(s_mutex);

    s_tasks.push(std::move(wrapper));
  }

  s_conditionToAwake.notify_one();

  return status;
}

// ------------------------------------------------------------------------------

} // namespace scheduler
} // namespace mage