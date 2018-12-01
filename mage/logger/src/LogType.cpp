#include "logger/LogType.h"

namespace mage
{
namespace log
{

// ------------------------------------------------------------------------------

std::string LogTypeToString(LogType _type)
{
  switch (_type)
  {
    case LogType::Info:
      return "Debug";
    case LogType::Warning:
      return "Warning";
    case LogType::Error:
      return "Error";
    case LogType::Fatal:
      return "Fatal";
    case LogType::Assert:
      return "Assert";
  }
  return "Null";
}

// ------------------------------------------------------------------------------

} // namespace log
} // namespace mage
