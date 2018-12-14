#pragma once

#include "LogData.h"

namespace mage
{
namespace log
{

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// Doesn't do any filtering
/////////////////////////////////////////////////
struct NoFilterPolicy
{
  inline bool Filter(const LogData& _data) { return true; }
};

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// Logs anything thats equal or more verbose than the stored
/////////////////////////////////////////////////
struct VerbosityFilterPolicy
{
  VerbosityFilterPolicy(LogType _verbosity)
      : m_verbosity(_verbosity)
  {
  }

  inline bool Filter(const LogData& _data)
  {
    return _data.m_type >= m_verbosity;
  }

private:
  LogType m_verbosity;
};

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// Only logs from a specific channel
/////////////////////////////////////////////////
struct ChannelFilterPolicy
{
  ChannelFilterPolicy(std::string _acceptedChannel)
      : m_acceptedChannel(std::move(_acceptedChannel))
  {
  }

  inline bool Filter(const LogData& _data)
  {
    return _data.m_logChannel == m_acceptedChannel;
  }

private:
  std::string m_acceptedChannel;
};

// ------------------------------------------------------------------------------

} // namespace log
} // namespace mage