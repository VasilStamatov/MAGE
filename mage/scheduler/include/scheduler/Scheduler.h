#pragma once

#include "Task.h"

namespace mage
{
namespace scheduler
{

// ------------------------------------------------------------------------------

void Initialize(); ///< Initialize the scheduler, called once on startup
void Shutdown(); ///< Shutdown the scheduler, called on app exit

// ------------------------------------------------------------------------------

Task* CreateTask(TaskFunction _function); ///< create a task which takes on data
Task* CreateTask(TaskFunction _function, const void* _taskData,
                 size_t _taskDataSize); ///< create a task which takes in input data

Task* CreateChildTask(Task* _parent, TaskFunction _function); ///< create a child task with no data
Task* CreateChildTask(Task* _parent, TaskFunction _function,
                      const void* _taskData, size_t _taskDataSize); ///< create a child task with data

// ------------------------------------------------------------------------------

void Run(Task* _task); ///< Run a task, which adds it to the task queue, enabling other workers to steal it
void Wait(const Task* _task); ///< wait for a task to finish, and while waiting, help with executing tasks

// ------------------------------------------------------------------------------

void EmptyTask(scheduler::Task* _task, const void* _taskData); ///< task function which does nothing (useful for empty root tasks)

// ------------------------------------------------------------------------------

} // namespace scheduler
} // namespace mage