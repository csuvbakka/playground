#pragma once

namespace gui
{
class Screen
{
public:
    Screen();
    ~Screen();

    static int height();
    static int width();

    static void erase();
};
}
