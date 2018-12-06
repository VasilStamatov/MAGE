#pragma once

#include "Task.h"

#include <memory>

namespace mage
{
namespace scheduler
{

// ------------------------------------------------------------------------------

void Initialize();
void Shutdown();

// ------------------------------------------------------------------------------

void AddTask(std::unique_ptr<Task> _task);
std::future<bool> AddTrackedTask(std::unique_ptr<Task> _task);

// ------------------------------------------------------------------------------

} // namespace scheduler
} // namespace mage