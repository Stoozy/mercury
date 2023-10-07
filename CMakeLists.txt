cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(mercury VERSION 1.0)
include_directories(include)
file(GLOB sources src/*.cc src/strategies/*.cc)
add_executable(mercury ${sources})