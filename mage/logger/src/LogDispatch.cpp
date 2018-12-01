#include "logger/LogDispatch.h"

#include <assert.h>
#include <vector>

namespace mage
{
namespace log
{
namespace dispatch
{

// ------------------------------------------------------------------------------

static std::vector<std::unique_ptr<Logger>> s_registeredLoggers;

// ------------------------------------------------------------------------------

void RegisterLogger(std::unique_ptr<Logger> _logger)
{
  s_registeredLoggers.push_back(std::move(_logger));
}

// ------------------------------------------------------------------------------

void LogInfo(std::string _logChannel, SourceInfo _sourceInfo,
             std::string _message)
{

  for (auto&& logger : s_registeredLoggers)
  {
    logger->Log(LogData(std::move(_logChannel), LogType::Info,
                        std::move(_sourceInfo), std::move(_message)));
  }
}

// ------------------------------------------------------------------------------

void LogWarning(std::string _logChannel, SourceInfo _sourceInfo,
                std::string _message)
{
  for (auto&& logger : s_registeredLoggers)
  {
    logger->Log(LogData(std::move(_logChannel), LogType::Warning,
                        std::move(_sourceInfo), std::move(_message)));
  }
}

// ------------------------------------------------------------------------------

void LogError(std::string _logChannel, SourceInfo _sourceInfo,
              std::string _message)
{
  for (auto&& logger : s_registeredLoggers)
  {
    logger->Log(LogData(std::move(_logChannel), LogType::Error,
                        std::move(_sourceInfo), std::move(_message)));
  }
}

// ------------------------------------------------------------------------------

void LogFatal(std::string _logChannel, SourceInfo _sourceInfo,
              std::string _message)
{
  for (auto&& logger : s_registeredLoggers)
  {
    logger->Log(LogData(std::move(_logChannel), LogType::Fatal,
                        std::move(_sourceInfo), std::move(_message)));
  }
}

// ------------------------------------------------------------------------------

void LogAssert(std::string _logChannel, SourceInfo _sourceInfo,
               std::string _message)
{
  for (auto&& logger : s_registeredLoggers)
  {
    logger->Log(LogData(std::move(_logChannel), LogType::Assert,
                        std::move(_sourceInfo), std::move(_message)));
  }
  assert(false);
}

// ------------------------------------------------------------------------------

} // namespace dispatch
} // namespace log
} // namespace mage