#pragma once

#include <string>

namespace mage
{
namespace filesystem
{

// ------------------------------------------------------------------------------

std::string ResolveAbsolutePathForFile(const std::string& _file);

// ------------------------------------------------------------------------------

bool ReadFileToBuffer(const std::string& _filePath, std::string& _buffer);

// ------------------------------------------------------------------------------

bool WriteBufferToFile(const std::string& _buffer,
                       const std::string& _filePath);

// ------------------------------------------------------------------------------

void CreateFilepath(const std::string& _filepath);

// ------------------------------------------------------------------------------

} // namespace filesystem
} // namespace mage
