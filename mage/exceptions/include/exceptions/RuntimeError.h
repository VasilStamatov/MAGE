#pragma once

#include <stdexcept>
#include <string>

namespace mage
{
namespace exceptions
{

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// Describes a runtime error that can happen
/////////////////////////////////////////////////
class RuntimeError : public std::runtime_error
{
public:
  RuntimeError(std::string _message, std::string _file, std::uint32_t _line);
  virtual ~RuntimeError() throw() {}

  // ------------------------------------------------------------------------------

  inline const std::string& GetNote() const { return m_note; }
  inline const std::string& GetFile() const { return m_file; }
  inline std::uint32_t GetLine() const { return m_line; }

  // ------------------------------------------------------------------------------

  std::string GetLocation() const;
  virtual std::string GetFullMessage() const;
  virtual std::string GetExceptionType() const;

  // ------------------------------------------------------------------------------

private:
  std::string m_note;
  std::string m_file;
  std::uint32_t m_line;
};

// ------------------------------------------------------------------------------

} // namespace exceptions

// ------------------------------------------------------------------------------

#define RUNTIME_ERROR(message)                                                 \
  exceptions::RuntimeError(message, __FILE__, __LINE__)

// ------------------------------------------------------------------------------

} // namespace mage
