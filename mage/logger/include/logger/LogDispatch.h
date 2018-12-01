#pragma once

#include "Logger.h"

namespace mage
{
namespace log
{
namespace dispatch
{

// ------------------------------------------------------------------------------

void RegisterLogger(std::unique_ptr<Logger> _logger);

// ------------------------------------------------------------------------------

void LogInfo(std::string _logChannel, SourceInfo _sourceInfo,
             std::string _message);

// ------------------------------------------------------------------------------

void LogWarning(std::string _logChannel, SourceInfo _sourceInfo,
                std::string _message);

// ------------------------------------------------------------------------------

void LogError(std::string _logChannel, SourceInfo _sourceInfo,
              std::string _message);

// ------------------------------------------------------------------------------

void LogFatal(std::string _logChannel, SourceInfo _sourceInfo,
              std::string _message);

// ------------------------------------------------------------------------------

void LogAssert(std::string _logChannel, SourceInfo _sourceInfo,
               std::string _message);

// ------------------------------------------------------------------------------

} // namespace dispatch
} // namespace log
} // namespace mage

#ifdef NDEBUG
#define LOG_INFO(channel, message)
#define LOG_WARNING(channel, message)
#define LOG_ERROR(channel, message)
#define LOG_FATAL(channel, message)
#define LOG_ASSERT(channel, message)
#else
#define LOG_INFO(channel, message)                                             \
  mage::log::dispatch::LogInfo(                                                \
      channel, mage::log::SourceInfo(__FILE__, __LINE__), message)
#define LOG_WARNING(channel, message)                                          \
  mage::log::dispatch::LogWarning(                                             \
      channel, mage::log::SourceInfo(__FILE__, __LINE__), message)
#define LOG_ERROR(channel, message)                                            \
  mage::log::dispatch::LogError(                                               \
      channel, mage::log::SourceInfo(__FILE__, __LINE__), message)
#define LOG_FATAL(channel, message)                                            \
  mage::log::dispatch::LogFatal(                                               \
      channel, mage::log::SourceInfo(__FILE__, __LINE__), message)
#define LOG_ASSERT(channel, message)                                           \
  mage::log::dispatch::LogAssert(                                              \
      channel, mage::log::SourceInfo(__FILE__, __LINE__), message)
#endif