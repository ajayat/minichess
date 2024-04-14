cmake_minimum_required(VERSION 3.19)
project(MiniChess)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

include_directories(include)
file(GLOB_RECURSE SOURCES src/*.cpp)

add_custom_target(docs
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_SOURCE_DIR}/docs
    COMMAND doxygen Doxyfile
)

add_executable(echecs ${SOURCES})
