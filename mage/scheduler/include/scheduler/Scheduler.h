#pragma once

#include "Task.h"

namespace mage
{
namespace scheduler
{

// ------------------------------------------------------------------------------

void Initialize();
void Shutdown();

// ------------------------------------------------------------------------------

Task* CreateTask(TaskFunction _function);
Task* CreateTask(TaskFunction _function, const void* _taskData,
                 size_t _taskDataSize);

Task* CreateChildTask(Task* _parent, TaskFunction _function);
Task* CreateChildTask(Task* _parent, TaskFunction _function,
                      const void* _taskData, size_t _taskDataSize);

// ------------------------------------------------------------------------------

void Run(Task* _task);
void Wait(const Task* _task);

// ------------------------------------------------------------------------------

} // namespace scheduler
} // namespace mage