#pragma once

#include <string>

namespace mage
{
namespace log
{

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// Metadata that cna be used for logging more info.
/////////////////////////////////////////////////
struct SourceInfo
{
  SourceInfo(std::string _fileName, std::uint32_t _line);

  std::string m_fileName;
  std::uint32_t m_line;
};

// ------------------------------------------------------------------------------

} // namespace log
} // namespace mage
