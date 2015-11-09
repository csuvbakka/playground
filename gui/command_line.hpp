#pragma once

#include "window.hpp"

#include <memory>
#include <string>

class CommandLine
{
public:
    CommandLine();

    std::string read_user_input();

private:
    std::unique_ptr<gui::Window> window_;
};
