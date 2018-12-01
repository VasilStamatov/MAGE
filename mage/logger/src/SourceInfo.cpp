#include "logger/SourceInfo.h"

namespace mage
{
namespace log
{

// ------------------------------------------------------------------------------

SourceInfo::SourceInfo(std::string _fileName, std::uint32_t _line)
    : m_fileName(std::move(_fileName))
    , m_line(std::move(_line))
{
}

// ------------------------------------------------------------------------------

} // namespace log
} // namespace mage
