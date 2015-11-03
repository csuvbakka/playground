SET(gui_SRCS
    window.cpp
    window.hpp
    point.hpp
    screen.cpp
    screen.hpp
    )

add_library(gui ${gui_SRCS})
