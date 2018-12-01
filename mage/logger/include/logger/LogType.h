#pragma once

#include <string>

namespace mage
{
namespace log
{

// ------------------------------------------------------------------------------

enum class LogType
{
  Info,
  Warning,
  Error,
  Fatal,
  Assert
};

// ------------------------------------------------------------------------------

std::string LogTypeToString(LogType _type);

// ------------------------------------------------------------------------------

} // namespace log
} // namespace mage