cmake_minimum_required(VERSION 3.16)

add_subdirectory("external/Raylib")

project(SimplePhy)

set(CMAKE_CXX_STANDARD 17)

add_executable(SimplePhy source.cpp)

target_link_libraries(SimplePhy PRIVATE Raylib)
