cmake_minimum_required(VERSION 3.19)
project(MiniChess)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 20)

include_directories(include)
file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(MiniChess ${SOURCES})
