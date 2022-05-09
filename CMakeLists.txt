cmake_minimum_required(VERSION 3.5)
project(Multithreading)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++14 -save-temps")

add_executable(runApp src/Main.cpp)