#include "logger/LogData.h"

namespace mage
{
namespace log
{

// ------------------------------------------------------------------------------

LogData::LogData(std::string _logChannel, LogType _type, SourceInfo _sourceInfo,
                 std::string _message)
    : m_sourceInfo(std::move(_sourceInfo))
    , m_logChannel(std::move(_logChannel))
    , m_message(std::move(_message))
    , m_type(_type)
{
}

// ------------------------------------------------------------------------------

} // namespace log
} // namespace mage
