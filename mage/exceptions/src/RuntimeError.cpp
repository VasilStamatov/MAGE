#include "exceptions/RuntimeError.h"

namespace mage
{
namespace exceptions
{

// ------------------------------------------------------------------------------

RuntimeError::RuntimeError(std::string _message, std::string _file,
                           std::uint32_t _line)
    : std::runtime_error(_message.c_str())
    , m_note(std::move(_message))
    , m_file(std::move(_file))
    , m_line(std::move(_line))
{
}

// ------------------------------------------------------------------------------

std::string RuntimeError::GetLocation() const
{
  return "Line [" + std::to_string(m_line) + "] in " + m_file;
}

// ------------------------------------------------------------------------------

std::string RuntimeError::GetFullMessage() const
{
  return "Location: " + GetLocation() + "\n\tMessage: " + m_note + "\n";
}

// ------------------------------------------------------------------------------

std::string RuntimeError::GetExceptionType() const
{
  return "Mage Runtime Error";
}

// ------------------------------------------------------------------------------

} // namespace exceptions
} // namespace mage