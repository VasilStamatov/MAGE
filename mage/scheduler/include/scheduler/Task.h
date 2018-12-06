#pragma once

#include <future>

namespace mage
{
namespace scheduler
{

// ------------------------------------------------------------------------------

class Task
{
public:
  virtual ~Task() {}

  virtual void Execute() = 0;
};

// ------------------------------------------------------------------------------

class TrackedTask : public Task
{
public:
  TrackedTask(std::unique_ptr<Task> _internalTask);
  virtual ~TrackedTask() {}

  virtual void Execute() override;

  std::future<bool> GetFuture();

private:
  std::unique_ptr<Task> m_internalTask;
  std::promise<bool> m_isComplete;
};

// ------------------------------------------------------------------------------

} // namespace scheduler
} // namespace mage