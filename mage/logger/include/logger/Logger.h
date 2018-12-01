#pragma once

#include "FilterPolicies.h"
#include "FormatPolicies.h"
#include "WriterPolicies.h"

namespace mage
{
namespace log
{

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// Base logger class for loggers
/////////////////////////////////////////////////
class Logger
{
public:
  virtual ~Logger() {}

  /////////////////////////////////////////////////
  /// virtual Log function for derived implementation.
  /////////////////////////////////////////////////
  virtual void Log(const LogData& _data) = 0;
};

// ------------------------------------------------------------------------------

template <class FilterPolicy, class FormatPolicy, class WritePolicy>
class GenericLogger : public Logger
{
public:
  GenericLogger(FilterPolicy _filter, FormatPolicy _formatter,
                WritePolicy _writer)
      : m_filter(std::move(_filter))
      , m_formatter(std::move(_formatter))
      , m_writer(std::move(_writer))
  {
  }

  virtual void Log(const LogData& _data) override
  {
    if (m_filter.Filter(_data))
    {
      std::string formattedMessage = m_formatter.Format(_data);
      m_writer.Write(formattedMessage);
    }
  }

private:
  FilterPolicy m_filter;
  FormatPolicy m_formatter;
  WritePolicy m_writer;
};

// ------------------------------------------------------------------------------

using ConsoleLogger = GenericLogger<VerbosityFilterPolicy, SimpleFormatPolicy,
                                    ConsoleWriterPolicy>;
using FileLogger =
    GenericLogger<NoFilterPolicy, ExtendedFormatPolicy, FileWriterPolicy>;

} // namespace log
} // namespace mage