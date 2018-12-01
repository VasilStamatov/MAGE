#pragma once

#include "LogData.h"

namespace mage
{
namespace log
{

// ------------------------------------------------------------------------------

struct NoFilterPolicy
{
  inline bool Filter(const LogData& _data) { return true; }
};

// ------------------------------------------------------------------------------

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