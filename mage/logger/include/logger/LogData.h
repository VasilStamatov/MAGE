#pragma once

#include "LogType.h"
#include "SourceInfo.h"

namespace mage
{
namespace log
{

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// struct to contain the data that's needed to make a log call
/////////////////////////////////////////////////
struct LogData
{
  /////////////////////////////////////////////////
  /// _logChannel : Modile from which it's fired (ex. "Renderer", "Audio"..)
  /// _type : the type of the log
  /// _verbosity : verbosity of the log (potentially used for filers)
  /// _sourceInfo : information about the source (file and function name, line)
  /// _message : the output message
  /////////////////////////////////////////////////
  LogData(std::string _logChannel, LogType _type, SourceInfo _sourceInfo,
          std::string _message);

  SourceInfo m_sourceInfo;
  std::string m_logChannel;
  std::string m_message;
  LogType m_type;
};

// ------------------------------------------------------------------------------

} // namespace log
} // namespace mage