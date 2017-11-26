cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++1z")
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

add_subdirectory(gui)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(myeditor main.cpp)
target_link_libraries(myeditor gui)
target_link_libraries(myeditor ncurses)
