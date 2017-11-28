#include "fs.hpp"

#include <fstream>
#include <string>
#include <vector>

namespace fs
{
std::vector<std::string> read_file(const std::string& filename)
{
    std::ifstream input(filename);
    std::vector<std::string> lines;

    for (std::string line; std::getline(input, line);)
        lines.push_back(line);

    return lines;
}
}
