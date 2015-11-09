SET(gui_SRCS
    window.cpp
    window.hpp
    point.hpp
    screen.cpp
    screen.hpp
    window_handler.cpp
    window_handler.hpp
    command_line.cpp
    command_line.hpp
    )

add_library(gui ${gui_SRCS})
