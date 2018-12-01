#pragma once

#include "LogData.h"

#include <sstream>

namespace mage
{
namespace log
{

// ------------------------------------------------------------------------------

struct SimpleFormatPolicy
{
  inline std::string Format(const LogData& _data)
  {
    std::stringstream stream;
    stream << "[" << _data.m_logChannel << "] " << _data.m_message;
    return stream.str();
  }
};

// ------------------------------------------------------------------------------

struct ExtendedFormatPolicy
{
  inline std::string Format(const LogData& _data)
  {
    std::stringstream stream;
    stream << _data.m_sourceInfo.m_fileName << "(" << _data.m_sourceInfo.m_line
           << "): "
           << "[" << _data.m_logChannel << "] ("
           << LogTypeToString(_data.m_type) << ") " << _data.m_message;
    return stream.str();
  }
};

// ------------------------------------------------------------------------------

} // namespace log
} // namespace mage