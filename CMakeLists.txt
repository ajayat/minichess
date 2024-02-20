cmake_minimum_required(VERSION 3.19)
project(ChessBoard)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(ChessBoard ${SOURCES})