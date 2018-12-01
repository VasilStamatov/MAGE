#pragma once

#include "LogData.h"
#include "filesystem/Filesystem.h"

#include <iostream>

namespace mage
{
namespace log
{

// ------------------------------------------------------------------------------

struct ConsoleWriterPolicy
{
  inline void Write(const std::string& _formattedMessage)
  {
    std::cout << _formattedMessage;
  }
};

// ------------------------------------------------------------------------------

struct FileWriterPolicy
{
  FileWriterPolicy(std::string _outputFilepath)
      : m_outputFilepath(std::move(_outputFilepath))
  {
  }

  inline void Write(const std::string& _formattedMessage)
  {
    filesystem::WriteBufferToFile(_formattedMessage, m_outputFilepath);
  }

private:
  std::string m_outputFilepath;
};

// ------------------------------------------------------------------------------

} // namespace log
} // namespace mage