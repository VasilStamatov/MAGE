#include "filesystem/Filesystem.h"

#include "exceptions/RuntimeError.h"

#include <filesystem>
#include <fstream>
#include <iomanip>

namespace mage
{
namespace filesystem
{

// ------------------------------------------------------------------------------

// example: https://en.cppreference.com/w/cpp/filesystem/absolute
std::string ResolveAbsolutePathForFile(const std::string& _file)
{
  namespace fs = std::experimental::filesystem;
  fs::path path(_file);
  if (path.is_absolute())
  {
    return path.string();
  }

  return fs::absolute(path).string();
}

// ------------------------------------------------------------------------------

void ReadFileToBuffer(const std::string& _filePath, std::string& _buffer)
{
  std::ifstream file(_filePath, std::ios::binary);
  if (file.fail())
  {
    throw RUNTIME_ERROR("Unable to find/open FILEPATH: " + _filePath);
  }

  // seek to the end
  file.seekg(0, std::ios::end);

  // Get the file size
  std::uint32_t fileSize = (std::uint32_t)file.tellg();
  file.seekg(0, std::ios::beg);

  // Reduce the file size by any header bytes that might be present
  fileSize -= (std::uint32_t)file.tellg();

  // resize the buffer to the exact size we need it
  _buffer.resize(fileSize);

  // read the file to the buffer
  file.read(&_buffer.front(), fileSize);

  // close the file
  file.close();
}

// ------------------------------------------------------------------------------

void WriteBufferToFile(const std::string& _buffer, const std::string& _filePath)
{
  std::ofstream file(_filePath, std::ios::out | std::ios::app);
  if (file.fail())
  {
    CreateFilepath(_filePath.c_str());

    file = std::ofstream(_filePath, std::ios::out | std::ios::app);

    if (file.fail())
    {
      throw RUNTIME_ERROR("Unable to find nor create file");
    }
  }

  file << _buffer;

  file.close();
}

// ------------------------------------------------------------------------------

void CreateFilepath(const std::string& _filepath)
{
  namespace fs = std::experimental::filesystem;

  auto countToNextSlash = _filepath.find_first_of('/');

  while (countToNextSlash != std::string::npos)
  {
    std::string directory = _filepath.substr(0, countToNextSlash);

    if (!fs::exists(directory))
    {
      fs::create_directory(directory);
    }

    countToNextSlash = _filepath.find('/', countToNextSlash + 1);
  }
}

// ------------------------------------------------------------------------------

} // namespace filesystem
} // namespace mage