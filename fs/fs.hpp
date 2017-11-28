#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace fs
{
std::vector<std::string> read_file(const std::string& filename);
}
